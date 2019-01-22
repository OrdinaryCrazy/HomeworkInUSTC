import numpy as np
import pandas as pd
import jieba
from keras.models import Sequential
from keras.layers import Dense, Activation, Dropout
from keras.layers.recurrent import LSTM
from keras.layers.embeddings import Embedding
from keras.preprocessing import sequence
from keras.utils import to_categorical
from gensim.models.word2vec import Word2Vec
from gensim.corpora.dictionary import Dictionary
from sklearn import cross_validation, metrics

WordVectorLength = 500
ForgetRate = 0.5
MaxLength = 80
Batch = 1500
Epoch = 15

TrainFile = pd.read_csv("./train.csv")
TestFile  = pd.read_csv("./test_public.csv")

POS = TrainFile[TrainFile.sentiment_value == 1]
NEG = TrainFile[TrainFile.sentiment_value == -1]
NEU = TrainFile[TrainFile.sentiment_value == 0]
COM = pd.concat((POS,NEG,NEU),axis=0)
TrainFile = COM.set_index("content_id")

DivideWord = []
TrainWord = []
TestWord = []

StopWord = open("./stopwords.txt")
StopWord = [term.replace('\n','') for term in StopWord]
for content in TrainFile.content:
    RawWordInThisLine = content.replace('，','').replace('。','').replace('！','').replace('\[a-z]*','')\
    .replace('\[A-Z]*','').replace('\[0-9]*','').replace('?','').replace(' ','').replace('？','')\
    .replace('(','').replace(r"\w",'').replace(')','').replace('.','').replace('a','').replace('b','')\
    .replace('c','').replace('d','').replace('e','').replace('f','').replace('g','').replace('h','')\
    .replace('i','').replace('j','').replace('k','').replace('l','').replace('m','').replace('n','')\
    .replace('o','').replace('p','').replace('q','').replace('r','').replace('s','').replace('v','')\
    .replace('u','').replace('v','').replace('w','').replace('x','').replace('y','').replace('z','')\
    .replace('t','').replace('A','').replace('B','').replace('F','').replace('J','').replace('C','')\
    .replace('G','').replace('K','').replace('D','').replace('H','').replace('L','').replace('E','')\
    .replace('I','').replace('M','').replace('N','').replace('O','').replace('P','').replace('Q','')\
    .replace('R','').replace('S','').replace('T','').replace('U','').replace('V','').replace('W','')\
    .replace('X','').replace('Y','').replace('Z','').replace('0','').replace('1','').replace('2','')\
    .replace('3','').replace('4','').replace('5','').replace('6','').replace('7','').replace('8','')\
    .replace('9','').replace('-','').replace('\xa0','').replace('·','').replace('（','').replace('）','')
    WordInThisLine = list(jieba.cut(RawWordInThisLine))
    for word in StopWord:
        if word in WordInThisLine:
            WordInThisLine.remove(word)    
    TrainWord.append(WordInThisLine)
    DivideWord.append(WordInThisLine)

for content in TestFile.content:
    RawWordInThisLine = content.replace('，','').replace('。','').replace('！','').replace('\[a-z]*','')\
    .replace('\[A-Z]*','').replace('\[0-9]*','').replace('?','').replace(' ','').replace('？','').replace('(','')\
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
    TestWord.append(WordInThisLine)
    DivideWord.append(WordInThisLine)

TrainFileWordVec = Word2Vec(size = WordVectorLength,window=15,min_count=3,workers=4,iter=15)
TrainFileWordVec.build_vocab(DivideWord)
TrainFileWordVec.train(DivideWord,total_examples=TrainFileWordVec.corpus_count,epochs=TrainFileWordVec.epochs)

WordDictionary = Dictionary()
WordDictionary.doc2bow(TrainFileWordVec.wv.vocab.keys(),allow_update=True)
WordIndex = {w:i + 1 for i,w in WordDictionary.items()}
WordVector = {word:TrainFileWordVec[word] for word in WordIndex.keys()}

TrainIndexVector = []
for line in TrainWord:
    IndexLine = []
    for word in line:
        try:
            IndexLine.append(WordIndex[word])
        except:
            IndexLine.append(0)
    TrainIndexVector.append(IndexLine)
TrainIndexVector = sequence.pad_sequences(TrainIndexVector, maxlen=MaxLength)

TrainEmbeddingList = np.zeros((len(WordIndex) + 1,WordVectorLength))
for word,index in WordIndex.items():
    TrainEmbeddingList[index,:] = WordVector[word]

#TrainSubject = TrainFile.subject
#subject = TrainFile.subject.unique()
#Subject = {}
#for i in range(10):
#    Subject[subject[i]] = i
#Y = list(TrainFile.subject)
#for i in range(len(Y)):
#    Y[i] = Subject[Y[i]]
#

train_x,test_x,train_y,test_y = cross_validation.train_test_split(TrainIndexVector, list(TrainFile.sentiment_value),\
                                                                    test_size = 0.1,random_state = 66)
#train_x,test_x,train_y,test_y = cross_validation.train_test_split(TrainIndexVector, Y,test_size = 0.3,random_state = 66)

train_y = to_categorical(train_y,num_classes=3)
test_y  = to_categorical(test_y, num_classes=3)
#train_y = to_categorical(train_y,num_classes=10)
#test_y  = to_categorical(test_y, num_classes=10)
#print(test_y[50:])
#input()

from keras import backend as K
def f1(y_true, y_pred):
    def recall(y_true, y_pred):
        """Recall metric.

        Only computes a batch-wise average of recall.

        Computes the recall, a metric for multi-label classification of
        how many relevant items are selected.
        """
        true_positives = K.sum(K.round(K.clip(y_true * y_pred, 0, 1)))
        possible_positives = K.sum(K.round(K.clip(y_true, 0, 1)))
        recall = true_positives / (possible_positives + K.epsilon())
        return recall

    def precision(y_true, y_pred):
        """Precision metric.

        Only computes a batch-wise average of precision.

        Computes the precision, a metric for multi-label classification of
        how many selected items are relevant.
        """
        true_positives = K.sum(K.round(K.clip(y_true * y_pred, 0, 1)))
        predicted_positives = K.sum(K.round(K.clip(y_pred, 0, 1)))
        precision = true_positives / (predicted_positives + K.epsilon())
        return precision
    precision = precision(y_true, y_pred)
    recall = recall(y_true, y_pred)
    return 2*((precision*recall)/(precision+recall+K.epsilon()))

LSTMModel = Sequential()
LSTMModel.add(Embedding(
    output_dim = WordVectorLength,
    input_dim = len(WordIndex) + 1,
    mask_zero = True,
    weights = [TrainEmbeddingList],
    input_length = MaxLength
))

LSTMModel.add(LSTM(output_dim=200, activation='relu'))
LSTMModel.add(Dropout(ForgetRate))
LSTMModel.add(Dense(200,activation='relu'))
LSTMModel.add(Dropout(ForgetRate))
LSTMModel.add(Dense(200,activation='relu'))
LSTMModel.add(Dropout(ForgetRate))
LSTMModel.add(Dense(3,activation='softmax'))
LSTMModel.add(Activation('softmax'))

LSTMModel.compile(loss='categorical_crossentropy',optimizer='adam',metrics=[f1])
LSTMModel.fit(train_x, train_y, batch_size=Batch, epochs=Epoch, verbose=1)
Score = LSTMModel.evaluate(test_x,test_y)
print(Score)

TestIndexVector = []
for line in TestWord:
    IndexLine = []
    for word in line:
        try:
            IndexLine.append(WordIndex[word])
        except:
            IndexLine.append(0)
    TestIndexVector.append(IndexLine)
TestIndexVector = sequence.pad_sequences(TestIndexVector, maxlen=MaxLength)

Result = pd.read_csv("./submit.csv",index_col="content_id")
Senti = LSTMModel.predict_classes(TestIndexVector)
Result.sentiment_value[:(len(Senti))] = Senti
Result.to_csv("./resultCON.csv")