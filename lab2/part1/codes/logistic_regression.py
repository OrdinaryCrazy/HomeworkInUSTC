import numpy as np
import pandas as pd
from pandas import Series,DataFrame
import Mytest
# 前35000条数据训练(validation size:10%),其余数据测试
class LogisticRegressionClassifier():
    '''
        简单的逻辑回归分类器
    '''
    def __init__(self, LearningtRate = 0.0001, RegulizationCoef = 0, StopThreshold = 0.000001, MaxIterTimes = 100, JudgeThreshold = 0.5):
        '''
            默认不打开正则化项
        '''
        self.LearningtRate = LearningtRate
        self.RegulizationCoef = RegulizationCoef
        self.StopThreshold = StopThreshold
        self.MaxIterTimes = MaxIterTimes
        self.JudgeThreshold = JudgeThreshold

    def fit(self,X,Y):
        '''
            拟合训练数据X,Y
        '''
        if(X.shape[0] != Y.shape[0]):
            raise TypeError("X should have same size with Y.")
        self.FeatureNum = X.shape[1]
        self.InstanceNum = X.shape[0]
        self.PredictProba = np.zeros(self.InstanceNum)
        self.FeatureWeight = np.zeros(self.FeatureNum)
        for i in range(self.MaxIterTimes):
            self.PredictProba = self.get_proba(X)
            WeightAveDiff = (1.0 / self.InstanceNum) * np.dot(X.T, (self.PredictProba - Y))
            WeightAveDiff += ( (self.RegulizationCoef * self.FeatureWeight) / self.InstanceNum )
            self.FeatureWeight -= self.LearningtRate * WeightAveDiff
            loss = np.linalg.norm(WeightAveDiff)
            if loss < self.StopThreshold:
                break
            if i % 2500 == 0:
                print("Iteration " + str(i) + " , loss = " + str(loss))

    def get_proba(self,X):
        '''
            判断给定特征向量预测值为1的概率,
        '''
        if(X.shape[1] != self.FeatureNum):
            raise TypeError("X should have same size with FeatureWeight of the model.")
        return 1.0 / ( 1.0 + np.exp( - np.dot( X, self.FeatureWeight ) ) )

    def predict(self,X):
        '''
            对输入数据进行预测,
        '''
        PredictRes = []
        for proba in self.get_proba(X):
            if proba > self.JudgeThreshold :
                PredictRes.append('yes')
            else:
                PredictRes.append('no')
        return np.array(PredictRes)

LRClassifier = LogisticRegressionClassifier(LearningtRate=0.05,JudgeThreshold=0.25,MaxIterTimes=20000)

InputData = pd.read_csv("../data/data_transfer.csv")
#InputData = InputData.sample(frac=1)
#InputData = InputData.sample(frac=1)
#InputData = InputData.sample(frac=1)
DataX = []
DataY = []
Y = {'no':0,'yes':1}
for line in InputData.index:
    strList = InputData.iloc[line].featurevector.replace('[','').replace(']','').split(',')
    strList = [float(i) for i in strList]
    DataX.append(strList)
    DataY.append(Y[InputData.iloc[line].y])

ResultFile = open("../data/lr_predicteva.txt",'w')

LRClassifier.fit( np.array(DataX)[:38000], np.array(DataY)[:38000] )
PredictY = LRClassifier.predict( np.array(DataX)[38000:] )
Precision, Recall, F1, Accuracy = Mytest.PRFTest( PredictY, np.array(InputData.y)[38000:] )

ResultFile.write("Precision = " + str(Precision) + ", Recall = " + str(Recall) + ", F1-score = " + str(F1) + ", Accuracy = " + str(Accuracy) + "\n")
print("Precision = " + str(Precision) + ", Recall = " + str(Recall) + ", F1-score = " + str(F1) + ", Accuracy = " + str(Accuracy) + "\n",end = '')

ResultFile.close()