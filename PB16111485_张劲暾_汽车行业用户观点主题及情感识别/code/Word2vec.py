import numpy as np
import jieba
from pandas import Series, DataFrame
import pandas as pd
from gensim.models import Word2Vec

TrainFile = pd.read_csv("./train.csv")
TestFile  = pd.read_csv("./test_public.csv")
DivideWord = []
StopWord = open("./stopwords.txt")
StopWord = [term.replace('\n','') for term in StopWord]
#print(StopWord)
maxlen = 0
for content in TrainFile.content:
    raw_word = content.replace('，','').replace('。','').replace('！','').replace('\[a-z]*','')\
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
    word_set = list(jieba.cut(raw_word))

    for word in StopWord:
        
        if word in word_set:
            #print(word_set)
            word_set.remove(word)
            #print(word_set)
            #input()    
    if len(word_set) > maxlen:
        maxlen = len(word_set)
    DivideWord.append(word_set)

for index in TestFile.index:
    RawWordInThisLine = TestFile.content[index].replace('，','').replace('。','').replace('！','').replace('\[a-z]*','')\
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
    if len(word_set) > maxlen:
        maxlen = len(word_set)
    DivideWord.append(WordInThisLine)

TrainFIleWordVec = Word2Vec(DivideWord,size = 500,window=15,min_count=8,workers=4)
print(TrainFIleWordVec.most_similar("优惠"))
print(maxlen)
#print(TrainFIleWordVec["车"])
