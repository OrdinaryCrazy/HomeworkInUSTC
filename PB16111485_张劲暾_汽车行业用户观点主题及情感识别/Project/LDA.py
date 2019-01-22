import numpy as np
from pandas import Series, DataFrame
import pandas as pd
import jieba
import random
import thulac
Divider = thulac.thulac(seg_only = True)

RawFile = pd.read_csv("./train.csv")
WordSet = set()
WordCount = {}
IdWords = {}
Topics = RawFile.subject.unique()

for index in RawFile.index:

    RawWordInThisLine = RawFile.content[index].replace('，','').replace('。','').replace('！','').replace('\[a-z]*','')\
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
    
    #WordInThisLine = list(jieba.cut(RawWordInThisLine,HMM=True))
    WordInThisLine = Divider.cut(RawWordInThisLine,text=True).split()
    #print(WordInThisLine)
    #input()
    if RawFile.content_id[index] not in IdWords:
        IdWords[RawFile.content_id[index]] = []
    IdWords[RawFile.content_id[index]].append(WordInThisLine)
    for word in WordInThisLine:
        WordSet.add(word)
        if word in WordCount:
            WordCount[word] += 1
        else:
            WordCount[word] = 1

# 无关词语清洗
#for word in WordSet:
#    if WordCount[word] < 10:
#        WordSet.remove(word)
RemoveWord = []
for word in WordSet:
    if WordCount[word] < 3:
        RemoveWord.append(word)
for word in RemoveWord:
    WordSet.remove(word)

for Id in IdWords:
    for line in IdWords[Id]:
        if word not in line:
            #print(IdWords[line])
            line.remove(word)
            #print(IdWords[line])
            #input()
#print(WordSet)

NumberOfFiles = len(RawFile)
NumberOfWords = len(WordSet)
NumberOfTopics = len(Topics)

#每篇文章中每个词语的主题假设
WordsTopics = {}
for Id in IdWords:
    if Id not in WordsTopics:
        WordsTopics[Id] = []
    for line in IdWords[Id]:
        WordsTopics[Id].append(Series(np.zeros(len(line)),index=line))

#主题的词语计数
WordsDistributionOnTopics = DataFrame(np.zeros((NumberOfTopics,NumberOfWords)),index=Topics,columns=WordSet)
#print(WordsDistributionOnTopics.loc['外观'])
#input()
#文章的主题计数
TopicDistributionOnFiles  = DataFrame(np.zeros((NumberOfFiles,NumberOfTopics)),index=RawFile.content_id,columns=Topics)
#print(TopicDistributionOnFiles)
#input()
#主题的总词频
NumberOfAllWordsOnATopic  = Series(np.zeros(NumberOfTopics),index=Topics)

for Id in IdWords:
    for word in IdWords[Id]:
        try:
            RandomTopic = Topics[random.randint(0,NumberOfTopics -1)]
            WordsTopics[Id][word] = RandomTopic
            #print(WordsDistributionOnTopics.loc[RandomTopic]['坟'])
            #input()
            WordsDistributionOnTopics.loc[RandomTopic][word] += 1
            NumberOfAllWordsOnATopic.loc[RandomTopic] += 1
            TopicDistributionOnFiles.loc[Id][RandomTopic] += 1
        except:
            print(word)
            print(word not in WordSet)

TopicProbabilityOnFiles = DataFrame(np.zeros(NumberOfFiles,NumberOfTopics),index=RawFile.content_id,columns=Topics)
WordProbabilityOnTopics = DataFrame(np.zeros(NumberOfTopics,NumberOfWords),index=Topics,columns=WordSet)

#先验概率分布
PriorTopicProbabilityOnFiles = DataFrame(np.zeros(NumberOfFiles,NumberOfTopics),index=RawFile.content_id,columns=Topics)
for file in PriorTopicProbabilityOnFiles:
    for topic in file:
        PriorTopicProbabilityOnFiles[file][topic] = 1 / NumberOfTopics

PriorWordProbabilityOnTopics = DataFrame(np.zeros(NumberOfTopics,NumberOfWords),index=Topics,columns=WordSet)
for topic in PriorWordProbabilityOnTopics:
    for word in topic:
        PriorWordProbabilityOnTopics[topic][word] = 1 / NumberOfWords

IterationTimes = 10
#  Gibbs Sampling
for x in range(IterationTimes):
    for Id in IdWords:
        for word in IdWords[Id]:
            TopicOfSamplingWord = WordsTopics[Id][word]
            WordsDistributionOnTopics.loc[TopicOfSamplingWord][word] -= 1
            TopicDistributionOnFiles.loc[Id][TopicOfSamplingWord] -= 1
            NumberOfAllWordsOnATopic[TopicOfSamplingWord] -= 1

            NewProbabilityOnThisPosition = []
            for topic in Topics:
                NewProbabilityOnThisPosition.append( \
                        ( ( TopicDistributionOnFiles[Id][topic]    + PriorTopicProbabilityOnFiles[Id][topic] )\
                         /( TopicDistributionOnFiles[Id]           + PriorTopicProbabilityOnFiles[Id] ).sum())\
                        *(( WordsDistributionOnTopics[topic][word] + PriorWordProbabilityOnTopics[topic][word] )\
                         /( WordsDistributionOnTopics[topic]       + PriorWordProbabilityOnTopics[topic] ).sum() ) )
            NewProbabilityOnThisPosition = np.array(NewProbabilityOnThisPosition)
            NewProbabilityOnThisPosition = NewProbabilityOnThisPosition / NewProbabilityOnThisPosition.sum()

            NewTopic = Topics[np.argmax(np.random.multinomial(1,NewProbabilityOnThisPosition))]
            WordsTopics[Id][word] = NewTopic
            WordsDistributionOnTopics[NewTopic][word] += 1
            TopicDistributionOnFiles[Id][NewTopic] += 1
            NumberOfAllWordsOnATopic[NewTopic] += 1

print("GibbsSampling Finished...")
TestFile = pd.read_csv("./test_public.csv")
Result = DataFrame(index=TestFile.content_id, columns=["subject","sentiment_value","sentiment_word"])
for index in TestFile.index:
    RawWordInThisLine = TestFile.content[index].replace('，','').replace('。','').replace('！','').replace('\[a-z]*','')\
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

    #WordInThisLine = list(jieba.cut(RawWordInThisLine,HMM=True))
    WordInThisLine = Divider.cut(RawWordInThisLine,text=True).split()
    for word in WordInThisLine:
        if word not in WordSet:
            WordInThisLine.remove(word)

    if(len(WordInThisLine) == 0):
        Result[index].sentiment_value = 0
        Result[index].sentiment_word  = Topics[random.randint(0,NumberOfTopics -1)]
        continue

    TopicOfTestLine = Series(np.zeros(len(WordInThisLine)),index=WordInThisLine)
    TopicDistributionOnFilesOfTestLine = Series(np.zeros(NumberOfTopics),index=Topics)

    for word in WordInThisLine:
        RandomTopicTestLine = Topics[random.randint(0,NumberOfTopics - 1)]
        TopicOfTestLine[word] = RandomTopicTestLine
        TopicDistributionOnFilesOfTestLine[RandomTopicTestLine] += 1
    
    for x in range(IterationTimes):

        for word in WordInThisLine:
            TopicOfTestingWord = TopicOfTestLine[word]
            TopicDistributionOnFilesOfTestLine[TopicOfSamplingWord] -= 1
            NewProbabilityOnThisPosition = []
            for topic in Topics:
                NewProbabilityOnThisPosition.append(\
                 ((TopicDistributionOnFilesOfTestLine[topic] + 1/NumberOfWords )\
                /(TopicDistributionOnFilesOfTestLine         + 1/NumberOfWords ).sum()) \
                *((WordsDistributionOnTopics[topic][word] + PriorWordProbabilityOnTopics[topic][word])\
                /(WordsDistributionOnTopics[topic]        + PriorWordProbabilityOnTopics[topic]).sum()))

            NewProbabilityOnThisPosition = np.array(NewProbabilityOnThisPosition)
            NewProbabilityOnThisPosition = NewProbabilityOnThisPosition / NewProbabilityOnThisPosition.sum()

            NewTopic = Topics[np.argmax(np.random.multinomial(1,NewProbabilityOnThisPosition))]
            TopicOfTestLine[word] = NewTopic
            TopicDistributionOnFilesOfTestLine[NewTopic] += 1
        
    Result[index].sentiment_value = 0
    Result[index].sentiment_word  = Topics[TopicOfTestLine.describe().top]
    
Result.to_csv("./result.csv")