#Author:OrdinaryCrazy
#Platform:Ubuntu17.10
#################################################################################################
import numpy as np
from pandas import Series, DataFrame
import pandas as pd
import jieba
import thulac
from sklearn.naive_bayes    import BernoulliNB
from sklearn                import cross_validation,metrics
from sklearn.neural_network import MLPClassifier
from sklearn.preprocessing  import label_binarize
#import pickle

train_file = pd.read_csv("./train.csv")
LengthOfTrainSet = len(train_file)
CommentDictionary = {}
CommentWord = {}

Divider = thulac.thulac(seg_only = True)

#Chinese word dividing and count
for index in train_file.index:
    raw_word = train_file.content[index].replace('，','').replace('。','').replace('！','').replace('\[a-z]*','').replace('\[A-Z]*','').replace('\[0-9]*','').replace('?','').replace(' ','').replace('？','').replace('(','').replace(r"\w",'').replace(')','').replace('.','').replace('a','').replace('b','').replace('c','').replace('d','').replace('e','').replace('f','').replace('g','').replace('h','').replace('i','').replace('j','').replace('k','').replace('l','').replace('m','').replace('n','').replace('o','').replace('p','').replace('q','').replace('r','').replace('s','').replace('v','').replace('u','').replace('v','').replace('w','').replace('x','').replace('y','').replace('z','').replace('t','').replace('A','').replace('B','').replace('F','').replace('J','').replace('C','').replace('G','').replace('K','').replace('D','').replace('H','').replace('L','').replace('E','').replace('I','').replace('M','').replace('N','').replace('O','').replace('P','').replace('Q','').replace('R','').replace('S','').replace('T','').replace('U','').replace('V','').replace('W','').replace('X','').replace('Y','').replace('Z','').replace('0','').replace('1','').replace('2','').replace('3','').replace('4','').replace('5','').replace('6','').replace('7','').replace('8','').replace('9','').replace('-','').replace('\xa0','').replace('·','').replace('（','').replace('）','')

    #word_set = list(jieba.cut(raw_word))
    word_set = Divider.cut(raw_word,text=True).split()
    CommentWord[train_file.content_id[index]] = word_set
    for word in word_set:
        if word in CommentDictionary:
            CommentDictionary[word] += 1
        else:
            CommentDictionary[word] = 1
            
#######################################################################################################
#CommentDictionaryFile = open("./Dictionary","w")	
#Dictionary = sorted(Dictionary.items(), key=lambda d: d[1],reverse=True)
#for word, count in Dictionary:                                                    
    #DictionaryFile.write(word + ',' + str(count) + '\n')
#DictionaryFile = open("./Dictionary","wb")
#pickle.dump(Dictionary,DictionaryFile, 0 )
#with open('./Dictionary', 'w') as f:
#	pickle.dump(Dictionary, f)

#CommentWordDataframe = Dataframe(CommentDictionary,index = ["keyword","num_count"])
######################################################################################################
#key word finding under Bayesrules
for key_word in CommentDictionary.keys():
    train_data = []
    train_target = train_file.sentiment_value[:9000]
    for i in range(9000):
        if key_word in CommentWord[train_file.content_id[i]]:
            train_data.append(1)
        else:
            train_data.append(0)
				
    BayesClassifer = BernoulliNB()
    
    train_x,test_x,train_y,test_y = cross_validation.train_test_split(train_data, train_target,test_size = 0.1,random_state = 13)
    
    y_one_hot = label_binarize(test_y,classes=[-1, 0, 1])
    
    BayesClassifer.fit(np.array(train_x).reshape(-1,1),train_y)
    PredictProbability = BayesClassifer.predict_proba(np.array(test_x).reshape(-1,1))
    test_auc = test_auc = metrics.roc_auc_score(y_one_hot,PredictProbability)
    CommentDictionary[key_word] = test_auc
    print(key_word + '\t\ttest_auc\t' + str(test_auc))
	
#CommentDictionary = dict(sorted(CommentDictionary.items(), key=lambda d: d[1],reverse=True))

OutputInformation = Series(CommentDictionary)
ContentInformation = Series(CommentWord)
OutputInformation.sort_values(ascending=False).to_csv('./key_word_for_sentiment_value_thulac.csv')
ContentInformation.to_csv('./content_word_thulac.csv')
input()














