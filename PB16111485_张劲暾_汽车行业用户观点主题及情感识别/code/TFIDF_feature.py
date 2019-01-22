import numpy    as np
import pandas   as pd
import jieba
from pandas                             import Series, DataFrame
from gensim.corpora.dictionary          import Dictionary
from gensim.models.ldamodel             import LdaModel
from sklearn.feature_extraction.text    import TfidfVectorizer
from sklearn.neural_network             import MLPClassifier
from sklearn.naive_bayes                import BernoulliNB, MultinomialNB
from sklearn                            import cross_validation,metrics
from sklearn.ensemble                   import VotingClassifier,RandomForestClassifier
from sklearn.linear_model               import LogisticRegression,SGDClassifier
#SVMforTopic = SGDClassifier(max_iter=1000)
#SVMforSenti = SGDClassifier(max_iter=1000)
#MLPforTopic
MLPforTopic = MLPClassifier(hidden_layer_sizes=(1000,800),activation='relu', solver='adam', alpha=0.0001, batch_size='auto',\
learning_rate='adaptive', learning_rate_init=0.001, power_t=0.5, max_iter=200, shuffle=True, random_state=None, tol=0.0001,\
verbose=False, warm_start=True, momentum=0.9, nesterovs_momentum=True, validation_fraction=0.20, beta_1=0.9, beta_2=0.999,\
epsilon=1e-08)
#MLPforSenti
MLPforSenti = MLPClassifier(hidden_layer_sizes=(1000,800),activation='relu', solver='adam', alpha=0.0001, batch_size='auto',\
learning_rate='adaptive', learning_rate_init=0.001, power_t=0.5, max_iter=200, shuffle=True, random_state=None, tol=0.0001,\
verbose=False, warm_start=True, momentum=0.9, nesterovs_momentum=True, validation_fraction=0.20, beta_1=0.9, beta_2=0.999,\
epsilon=1e-08)
BNBforTopic = BernoulliNB()
BNBforSenti = BernoulliNB()
#MLBforTopic = MultinomialNB()
#MLBforSenti = MultinomialNB()
RFforTopic = RandomForestClassifier(n_estimators=500, random_state=1080)
RFforSenti = RandomForestClassifier(n_estimators=500, random_state=1080)
LRCforTopic = LogisticRegression(random_state=0, solver='lbfgs',multi_class='multinomial')
LRCforSenti = LogisticRegression(random_state=0, solver='lbfgs',multi_class='multinomial')
#NeuralNetwork = RandomForestClassifier(n_estimators=500, random_state=1080)
#NeuralNetForSenti = RandomForestClassifier(n_estimators=500, random_state=1080)
NeuralNetwork = VotingClassifier(estimators=[\
                                #('MLB', MLBforTopic),\
                                #('SVM', SVMforTopic),\
                                ('RF' , RFforTopic),  \
                                ('MLP', MLPforTopic), \
                                ('BNB', BNBforTopic), \
                                ('LRC', LRCforTopic)],voting='soft')
NeuralNetForSenti = VotingClassifier(estimators=[\
                                #('MLB', MLBforSenti),\
                                #('SVM', SVMforSenti),\
                                ('RF' , RFforSenti),  \
                                ('MLP', MLPforSenti), \
                                ('BNB', BNBforSenti), \
                                ('LRC', LRCforSenti)],voting='soft')

NumOfTopics = 900
TrainFile = pd.read_csv("./train.csv")
TestFile  = pd.read_csv("./test_public.csv")
StopWord = open("./stopwords.txt")
StopWord = [term.replace('\n','') for term in StopWord]
Comment = []
CommentPlus = []
CommentTest = []
for index in TrainFile.index:
    RawWordInThisLine = TrainFile.content[index].replace('，','').replace('。','').replace('！','')\
    .replace('\[0-9]*','').replace('?','').replace(' ','').replace('？','').replace('(','')\
    .replace("\w",'').replace(')','').replace('.','').replace('a','').replace('b','').replace('c','').replace('d','')\
    .replace('e','').replace('f','').replace('g','').replace('h','').replace('i','').replace('j','').replace('k','')\
    .replace('l','').replace('m','').replace('n','').replace('o','').replace('p','').replace('q','').replace('r','')\
    .replace('s','').replace('v','').replace('u','').replace('v','').replace('w','').replace('x','').replace('y','')\
    .replace('z','').replace('t','').replace('A','').replace('B','').replace('F','').replace('J','').replace('C','')\
    .replace('G','').replace('K','').replace('D','').replace('H','').replace('L','').replace('E','').replace('I','')\
    .replace('M','').replace('N','').replace('O','').replace('P','').replace('Q','').replace('R','').replace('S','')\
    .replace('T','').replace('U','').replace('V','').replace('W','').replace('X','').replace('Y','').replace('Z','')\
    .replace('0','').replace('1','').replace('2','').replace('3','').replace('4','').replace('5','').replace('6','')\
    .replace('7','').replace('8','').replace('9','').replace('-','').replace('\xa0','').replace('·','').replace('（','').replace('）','')
    WordInThisLine = list(jieba.cut(RawWordInThisLine))
    for word in StopWord:
        if word in WordInThisLine:
            WordInThisLine.remove(word)

    Comment.append(WordInThisLine)
    CommentPlus.append(WordInThisLine)

for index in TestFile.index:
    RawWordInThisLine = TestFile.content[index].replace('，','').replace('。','').replace('！','')\
    .replace('\[0-9]*','').replace('?','').replace(' ','').replace('？','').replace('(','')\
    .replace("\w",'').replace(')','').replace('.','').replace('a','').replace('b','').replace('c','').replace('d','')\
    .replace('e','').replace('f','').replace('g','').replace('h','').replace('i','').replace('j','').replace('k','')\
    .replace('l','').replace('m','').replace('n','').replace('o','').replace('p','').replace('q','').replace('r','')\
    .replace('s','').replace('v','').replace('u','').replace('v','').replace('w','').replace('x','').replace('y','')\
    .replace('z','').replace('t','').replace('A','').replace('B','').replace('F','').replace('J','').replace('C','')\
    .replace('G','').replace('K','').replace('D','').replace('H','').replace('L','').replace('E','').replace('I','')\
    .replace('M','').replace('N','').replace('O','').replace('P','').replace('Q','').replace('R','').replace('S','')\
    .replace('T','').replace('U','').replace('V','').replace('W','').replace('X','').replace('Y','').replace('Z','')\
    .replace('0','').replace('1','').replace('2','').replace('3','').replace('4','').replace('5','').replace('6','')\
    .replace('7','').replace('8','').replace('9','').replace('-','').replace('\xa0','').replace('·','').replace('（','').replace('）','')
    WordInThisLine = list(jieba.cut(RawWordInThisLine))
    for word in StopWord:
        if word in WordInThisLine:
            WordInThisLine.remove(word)

    CommentTest.append(WordInThisLine)
    CommentPlus.append(WordInThisLine)
print("Text Preprocessing Finished......")

#common_dictionary = Dictionary(CommentPlus)
#Series(common_dictionary).to_csv("./dictionary_LDA.csv")
#common_corpus = [common_dictionary.doc2bow(comment) for comment in CommentPlus]
#Series(common_corpus).to_csv("./common_corpus_LDA.csv")
#Lda = LdaModel(common_corpus, num_topics=NumOfTopics,iterations=300,id2word=common_dictionary,passes=60)
#print("LDA finished...")
#Vector = [Lda[common_dictionary.doc2bow(comment)] for comment in Comment]
#Series(Vector).to_csv("./LDA_Vector.csv")

Y  = list(TrainFile.subject)
Ys = list(TrainFile.sentiment_value)
#X = []
#for vec in Vector:
#    VectorForComment = [0] * NumOfTopics
#    for tup in vec:
#        VectorForComment[tup[0] - 1] = tup[1]
#    X.append(VectorForComment)

TransFormer = TfidfVectorizer(min_df=1e-5)
#print(CommentPlus)
#input()
CommentText = [' '.join(comment) for comment in CommentPlus]
#print(CommentText)
#print(len(CommentText))
#input()
Xp = TransFormer.fit_transform(CommentText)
X = Xp[:len(Comment)]

train_x,test_x,train_y,test_y = cross_validation.train_test_split(X, Y,test_size = 0.05,random_state = 66)
train_xs,test_xs,train_ys,test_ys = cross_validation.train_test_split(X, Ys,test_size = 0.05,random_state = 66)

NeuralNetwork.fit(train_x,train_y)
NeuralNetForSenti.fit(train_xs,train_ys)

predict_prob_y  = NeuralNetwork.predict(test_x)
predict_prob_ys = NeuralNetForSenti.predict(test_xs)
show = NeuralNetwork.predict_proba(test_x)

F  = metrics.f1_score(test_y,predict_prob_y,average='micro')
Fs = metrics.f1_score(test_ys,predict_prob_ys,average='micro')

print("F1:\t" + str((F + Fs) / 2) + " : " + str(F) + " + " + str(Fs))

Result = DataFrame(index=TestFile.content_id, columns=["subject","sentiment_value","sentiment_word"])
#VectorTest = [Lda[common_dictionary.doc2bow(comment)] for comment in CommentTest]
#XTest = []
#for vec in VectorTest:
#    VectorForComment = [0] * NumOfTopics
#    for tup in vec:
#        VectorForComment[tup[0] - 1] = tup[1]
#    XTest.append(VectorForComment)
Xt = Xp[len(Comment):]
Result.subject = NeuralNetwork.predict(Xt)
Result.sentiment_value = NeuralNetForSenti.predict(Xt)
Result["sentiment_word"] = ''

Result.to_csv("./result_TF_last.csv")
#F1:	0.6736947791164659 : 0.6204819277108434 + 0.7269076305220884
