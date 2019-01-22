# -*- coding: utf-8 -*-
import numpy as np
import pandas as pd
from pandas import Series,DataFrame
import Mytest
# 前38000条数据训练,其余数据测试
ClassWeight = {'no':1,'yes':5}
def KnnClassifier(TrainX,TrainY,TargetX,K):
    '''
        knn分类器:(输入输出类型均为numpy.array)
        输入:
            TrainX:训练数据集特征向量集合
            TrainY:训练数据集标签集合,与特征向量集合顺序相同
            TargetX:预测数据集特征向量集合
            K:考虑最邻近的K个点
        输出:
            TargetY:预测数据集标签集合,与特征向量集合顺序相同
    '''
    if(TrainX.shape[0] != TrainY.shape[0]):
        raise TypeError("TrainX should have same size with TrainY.")
    TargetY = []
    for i in range(TargetX.shape[0]):
        DifferentMatrix = np.tile(TargetX[i],(TrainX.shape[0],1)) - TrainX
        DiffSquarMatrix = DifferentMatrix ** 2
        Distance = DiffSquarMatrix.sum(axis = 1) ** 0.5
        DistanceSortedOrder = Distance.argsort()
        NeighLabelCount = {}
        for i in range(1,K + 1):
            NeighLabel = TrainY[DistanceSortedOrder[i]]
            NeighLabelCount[NeighLabel] = NeighLabelCount.get(NeighLabel,0) + ClassWeight[NeighLabel] / ( 1 + Distance[DistanceSortedOrder[i]] )
        SortedClassCount = sorted(NeighLabelCount.items(),key = lambda x:x[1],reverse = True)
        TargetY.append(SortedClassCount[0][0])
    return TargetY

InputData = pd.read_csv("../data/data_transfer.csv")
#InputData = InputData.sample(frac=1)
#InputData = InputData.sample(frac=1)
#InputData = InputData.sample(frac=1)
DataX = []
for line in InputData.index:
    strList = InputData.iloc[line].featurevector.replace('[','').replace(']','').split(',')
    strList = [float(i) for i in strList]
    DataX.append(strList)

ResultFile = open("../data/knn_predicteva.txt",'w')
for i in range(1,15):
    Result = KnnClassifier( np.array(DataX)[:38000],
                            np.array(InputData.y)[:38000],
                            np.array(DataX)[38000:],
                            i )
    Precision, Recall, F1, Accuracy = Mytest.PRFTest(np.array(Result),np.array(InputData.y)[38000:])
    ResultFile.write("K = " + str(i) + ", Precision = " + str(Precision) + ", Recall = " + str(Recall) + ", F1-score = " + str(F1) + ", Accuracy = " + str(Accuracy) + "\n")
    print("K = " + str(i) + ", Precision = " + str(Precision) + ", Recall = " + str(Recall) + ", F1-score = " + str(F1) + ", Accuracy = " + str(Accuracy) + "\n",end = '')
ResultFile.close()