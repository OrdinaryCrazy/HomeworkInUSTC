import numpy as np
import pandas as pd
from pandas import Series,DataFrame

def PRFTest(PredictY,TargetY):
    '''
        Precision, Recall, F1计算函数
    '''
    if(PredictY.shape[0] != TargetY.shape[0]):
        raise TypeError("PredictY should have same size with TargetY.")
    #print(PredictY)
    #print(TargetY)
    PP = 1
    PN = 1
    NP = 1
    NN = 1
    for i in range(PredictY.shape[0]):
        if(PredictY[i] == 'yes' and TargetY[i] == 'yes'):
            PP = PP + 1
        if(PredictY[i] == 'yes' and TargetY[i] == 'no' ):
            PN = PN + 1
        if(PredictY[i] == 'no'  and TargetY[i] == 'yes'):
            NP = NP + 1
        if(PredictY[i] == 'no'  and TargetY[i] == 'no' ):
            NN = NN + 1
    print(str(PP) + ',' + str(PN) + ',' + str(NP) + ',' + str(NN))
    #print("Accuracy: " + str( (PP + NN) / (PP + PN + NP + NN) ))
    Precision = PP / (PP + PN)
    Recall = PP / (PP + NP)
    F1 = (2 * Precision * Recall) / (Precision + Recall)
    Accuracy = (PP + NN) / (PP + PN + NP + NN)
    return Precision, Recall, F1, Accuracy