import numpy as np
import pandas as pd
from snownlp import SnowNLP
from sklearn import cross_validation,metrics
TrainFile = pd.read_csv("./train.csv")
result = []
for line in TrainFile.content:
    S = SnowNLP(line)
    a = S.sentiments
    if a > 0.7:
        result.append(1)
    else:
        if a < 0.2:
            result.append(-1)
        else:
            result.append(0)
Fs = metrics.f1_score(list(TrainFile.sentiment_value),result,average='micro')
print(Fs)