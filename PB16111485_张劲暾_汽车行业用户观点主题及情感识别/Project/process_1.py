#Author:OrdinaryCrazy
#Platform:Ubuntu17.10
#################################################################################################
import numpy as np
from pandas import Series, DataFrame
import pandas as pd
#import jieba
#from sklearn.naive_bayes    import BernoulliNB
import thulac
from sklearn                import cross_validation,metrics
from sklearn.neural_network import MLPClassifier
from sklearn.preprocessing  import label_binarize
Divider = thulac.thulac(seg_only = True)
train_file = pd.read_csv("./train.csv")
LengthOfTrainSet = len(train_file)

SentimentWord = train_file.sentiment_word.unique().tolist()

LengthOfSentimentWord = len(SentimentWord)
SentimentWordIn = {}
for i,word in enumerate(SentimentWord):
    SentimentWordIn[word] = i

ContentInformation = Series.from_csv('./content_word_thulac.csv')
CommentWord = ContentInformation.to_dict()

WordInformation = Series.from_csv('./key_word_for_sentiment_value_thulac.csv')
CommentDictionary = WordInformation.to_dict()

for key in list(CommentDictionary.keys()):
    if CommentDictionary[key] < 0.5:
        CommentDictionary.pop(key)
        
LengthOfFeature = len(CommentDictionary)
ChooseWord = {}
for i,word in enumerate(CommentDictionary.keys()):
    ChooseWord[word] = i

#train classier for prediction
bench_size = 1516
train_times = 6

NeuralNetwork = MLPClassifier(hidden_layer_sizes=(800,300),activation='relu', solver='adam', alpha=0.0001, batch_size='auto',\
learning_rate='adaptive', learning_rate_init=0.001, power_t=0.5, max_iter=200, shuffle=True, random_state=None, tol=0.0001,\
verbose=False, warm_start=True, momentum=0.9, nesterovs_momentum=True, validation_fraction=0.20, beta_1=0.9, beta_2=0.999,\
epsilon=1e-08)


for time in range(train_times):
    train_target = train_file.sentiment_value[time * bench_size:(time + 1) * bench_size]
    train_data = []
    for index in train_file.index[time * bench_size:(time + 1) * bench_size]:
        tmp = [0] * (LengthOfFeature + LengthOfSentimentWord)
        for word in ChooseWord.keys():
            if word in CommentWord[train_file.content_id[index]]:
                tmp[ChooseWord[word]] = 1
                    
        for word in SentimentWordIn.keys():
            if str(word) in train_file.content[index]:
                #print(str(word) + ' : ' + train_file.content[index])
                #input()
                tmp[LengthOfFeature + SentimentWordIn[word]] = 1

        train_data.append(tmp)
	    
    train_x,test_x,train_y,test_y = cross_validation.train_test_split(train_data, train_target,test_size = 0.01,random_state = 83)
        
    #y_one_hot = label_binarize(test_y,classes=[-1, 0, 1])
        
    NeuralNetwork.partial_fit(train_x,train_y,[-1,0,1])
    #predict_prob_y = NeuralNetwork.predict_proba(test_x)
    predict_prob_y = NeuralNetwork.predict(test_x)
    #test_auc = metrics.roc_auc_score(y_one_hot,predict_prob_y)
    test_auc = metrics.accuracy_score(test_y,predict_prob_y)
    print('time:%s\t'%time + "test_auc:\t" + str(test_auc))
    
NeuralNetworkForWord = MLPClassifier(hidden_layer_sizes=(800,300),activation='relu', solver='adam', alpha=0.0001,\
batch_size='auto', learning_rate='adaptive', learning_rate_init=0.001, power_t=0.5, max_iter=200, shuffle=True, \
random_state=None, tol=0.0001, verbose=False, warm_start=True, momentum=0.9, nesterovs_momentum=True, validation_fraction=0.20,\
beta_1=0.9, beta_2=0.999, epsilon=1e-08)

for time in range(train_times):
    train_target = train_file.subject[time * bench_size:(time + 1) * bench_size]
    train_data = []
    for index in train_file.index[time * bench_size:(time + 1) * bench_size]:
        tmp = [0] * (LengthOfFeature + LengthOfSentimentWord)
        for word in ChooseWord.keys():
            if word in CommentWord[train_file.content_id[index]]:
                tmp[ChooseWord[word]] = 1

        for word in SentimentWordIn.keys():
            if str(word) in train_file.content[index]:
                tmp[LengthOfFeature + SentimentWordIn[word]] = 1

        train_data.append(tmp)
	    
    train_x,test_x,train_y,test_y = cross_validation.train_test_split(train_data, train_target,test_size = 0.01,random_state = 83)
        
    #y_one_hot = label_binarize(test_y,classes=["动力","价格","油耗","操控","舒适性","配置","安全性","内饰","外观","空间"])
        
    NeuralNetworkForWord.partial_fit(train_x,train_y,["动力","价格","油耗","操控","舒适性","配置","安全性","内饰","外观","空间"])
    predict_prob_y = NeuralNetworkForWord.predict(test_x)
    #test_auc = metrics.roc_auc_score(y_one_hot,predict_prob_y)
    test_auc = metrics.accuracy_score(test_y,predict_prob_y)
    print('time:%s\t'%time + "test_auc:\t" + str(test_auc))
    

TestFile = pd.read_csv("./test_public.csv")    
Result = DataFrame(index=TestFile.content_id, columns=["subject","sentiment_value","sentiment_word"])
Result["sentiment_word"] = ''
Result["sentiment_value"] = 0

#print(Result)
#input()

for index in TestFile.index:
    raw_word = TestFile.content[index].replace('，','').replace('。','').replace('！','').replace('\[a-z]*','')\
    .replace('\[A-Z]*','').replace('\[0-9]*','').replace('?','').replace(' ','').replace('？','').replace('(','')\
    .replace(r"\w",'').replace(')','').replace('.','').replace('a','').replace('b','').replace('c','').replace('d','')\
    .replace('e','').replace('f','').replace('g','').replace('h','').replace('i','').replace('j','').replace('k','')\
    .replace('l','').replace('m','').replace('n','').replace('o','').replace('p','').replace('q','').replace('r','')\
    .replace('s','').replace('v','').replace('u','').replace('v','').replace('w','').replace('x','').replace('y','')\
    .replace('z','').replace('t','').replace('A','').replace('B','').replace('F','').replace('J','').replace('C','')\
    .replace('G','').replace('K','').replace('D','').replace('H','').replace('L','').replace('E','').replace('I','')\
    .replace('M','').replace('N','').replace('O','').replace('P','').replace('Q','').replace('R','').replace('S','')\
    .replace('T','').replace('U','').replace('V','').replace('W','').replace('X','').replace('Y','').replace('Z','')\
    .replace('0','').replace('1','').replace('2','').replace('3','').replace('4','').replace('5','').replace('6','')\
    .replace('7','').replace('8','').replace('9','').replace('-','').replace('\xa0','').replace('·','').replace('（','')\
    .replace('）','')
    word_set = Divider.cut(raw_word,text=True).split()
    TrainVector = [0] * (LengthOfFeature + LengthOfSentimentWord)
    for word in ChooseWord.keys():
        if word in word_set:
            TrainVector[ChooseWord[word]] = 1
    for word in SentimentWordIn.keys(): 
        if str(word) in TestFile.content[index]:
            tmp[LengthOfFeature + SentimentWordIn[word]] = 1
    
    Result.sentiment_value[index] = NeuralNetwork.predict(np.array(TrainVector).reshape(1,-1))
    Result.subject[index] = NeuralNetworkForWord.predict(np.array(TrainVector).reshape(1,-1))[0]
    #print(Result)
    #input()
    #print(index)
    
Result.to_csv("./result_NB.csv")



































