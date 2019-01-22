import numpy as np
import pandas as pd
from pandas import Series,DataFrame
import math
###################################################################################################
# 数据预处理:整理得到一个适合分析的DataFrame
# 每个feature的预处理思路:(直接转换成独热码)(缺失值填充:众数)
# 1, age: 
#   [17,25]:[0,0,0,0,1], 
#   [25,35]:[0,0,0,1,0], 
#   [35,45]:[0,0,1,0,0], 
#   [45,60]:[0,1,0,0,0], 
#   [60,98]:[1,0,0,0,0],
# 2, job: 
Job =   {   'admin.'        :[0,0,0,0,0,0,0,0,0,0,1],
            'blue-collar'   :[0,0,0,0,0,0,0,0,0,1,0],
            'entrepreneur'  :[0,0,0,0,0,0,0,0,1,0,0],
            'housemaid'     :[0,0,0,0,0,0,0,1,0,0,0],
            'management'    :[0,0,0,0,0,0,1,0,0,0,0],
            'retired'       :[0,0,0,0,0,1,0,0,0,0,0],
            'self-employed' :[0,0,0,0,1,0,0,0,0,0,0],
            'services'      :[0,0,0,1,0,0,0,0,0,0,0],
            'student'       :[0,0,1,0,0,0,0,0,0,0,0],
            'technician'    :[0,1,0,0,0,0,0,0,0,0,0],
            'unemployed'    :[1,0,0,0,0,0,0,0,0,0,0],
            'unknown'       :[0,0,0,0,0,0,0,0,0,0,1]
        }
# 3, marital:
Matiral =   {   'divorced'  :[0,0,1],
                'married'   :[0,1,0],
                'single'    :[1,0,0],
                'unknown'   :[0,1,0]
            }
# 4, education:
Edu =   {   'basic.4y'              :[0,0,0,0,0,0,1],
            'basic.6y'              :[0,0,0,0,0,1,0],
            'basic.9y'              :[0,0,0,0,1,0,0],
            'high.school'           :[0,0,0,1,0,0,0],
            'illiterate'            :[0,0,1,0,0,0,0],
            'professional.course'   :[0,1,0,0,0,0,0],
            'university.degree'     :[1,0,0,0,0,0,0],
            'unknown'               :[1,0,0,0,0,0,0]
        }   
# 5, default:   这一项表示的是用户是否默认信用,绝大多数都是没有或未知,直接放弃
# 6, housing:
Hou = {'no':[0],'unknown':[1],'yes':[1]}
# 7, loan:
Loa = {'no':[0],'unknown':[0],'yes':[1]}
# 8, contact:
Con = {'cellular':[1],'telephone':[0]}
# 9, month:
Mon =   {   'mar' :[0,0,0,0,0,0,0,0,0,1],
            'apr' :[0,0,0,0,0,0,0,0,1,0],
            'may' :[0,0,0,0,0,0,0,1,0,0],
            'jun' :[0,0,0,0,0,0,1,0,0,0],
            'jul' :[0,0,0,0,0,1,0,0,0,0],
            'aug' :[0,0,0,0,1,0,0,0,0,0],
            'sep' :[0,0,0,1,0,0,0,0,0,0],
            'oct' :[0,0,1,0,0,0,0,0,0,0],
            'nov' :[0,1,0,0,0,0,0,0,0,0],
            'dec' :[1,0,0,0,0,0,0,0,0,0]
        }
# 10, day_of_week:
Dow =   {   'mon':[0,0,0,0,1],
            'tue':[0,0,0,1,0],
            'wed':[0,0,1,0,0],
            'thu':[0,1,0,0,0],
            'fri':[1,0,0,0,0]
        }
# 11, campaign:这一项不做离散化处理,但观察到分布为长尾趋势,所以特征值取为log2(1 + n)
# 12, pdays:这一项绝大多数是无意义的999,直接放弃
# 13, previous:log2(1 + n)
# 14, poutcome:
Pot = {'failure':[-1],'nonexistent':[0],'success':[1]}
# 15, emp.var.rate:实值直接作为特征值
# 16, cons.price.idx:正则化,
CPI_mean = 93.575664
CPI_var = 0.578840
# 17, cons.conf.idx:正则化,
CFI_mean = -40.502600
CFI_var = 4.628198
# 18, euribor3m:区间离散化:
#   [0,1)	:[0,0,0,0,1]
#   [1,2)	:[0,0,0,1,0]
#   [2,3)	:[0,0,1,0,0]
#   [3,4)	:[0,1,0,0,0]
#   [4,...)	:[1,0,0,0,0]
E3_mean = 3.621291
E3_var = 1.734447
# 19, nr.employed:正则化:
NE_mean = 5167.035911
NE_var = 72.251528
# y的比例:
# no     36548
# yes     4640
###################################################################################################
def FeatureGain(line):
    '''
        Gain featurevector from a record
    '''
    feature = []
    if line.age < 25:
        feature.extend([0,0,0,0,1])
    else:
        if line.age < 35:
            feature.extend([0,0,0,1,0])
        else:
            if line.age < 45:
                feature.extend([0,0,1,0,0])
            else:
                if line.age < 60:
                    feature.extend([0,1,0,0,0])
                else:
                    feature.extend([1,0,0,0,0])
    feature.extend(Job[line.job])
    feature.extend(Matiral[line.marital])
    feature.extend(Edu[line.education])
    feature.extend(Hou[line.housing])
    feature.extend(Loa[line.loan])
    feature.extend(Con[line.contact])
    # 放弃两个意义不大的特征
    #feature.extend(Mon[line.month])
    #feature.extend(Dow[line.day_of_week])
    feature.append(math.log2(1 + line.campaign))
    feature.append(math.log2(1 + line.previous))
    feature.extend(Pot[line.poutcome])
    feature.append(line['emp.var.rate'])
    feature.append((line['cons.price.idx'] - CPI_mean) / CPI_var)
    feature.append((line['cons.conf.idx']  - CFI_mean) / CFI_var)
    feature.append((line['nr.employed']    - NE_mean ) / NE_var )
    feature.append((line['euribor3m']      - E3_mean ) / E3_var )
    ####################################################################################
    #if line.euribor3m < 1:
    #    feature.extend([0,0,0,0,1])
    #else:
    #    if line.euribor3m < 2:
    #        feature.extend([0,0,0,1,0])
    #    else:
    #        if line.euribor3m < 3:
    #            feature.extend([0,0,1,0,0])
    #        else:
    #            if line.euribor3m < 3:
    #                feature.extend([0,1,0,0,0])
    #            else:
    #                feature.extend([1,0,0,0,0])
    ####################################################################################
    return feature

DataOrigin = pd.read_csv("../data/bank-additional-full.csv",sep=';')
DataTranse = DataFrame(index=DataOrigin.index,columns=['featurevector','y'])
DataTranse.y = DataOrigin.y
for i in DataOrigin.index:
    DataTranse.iloc[i].featurevector = FeatureGain(DataOrigin.iloc[i])
DataTranse = DataTranse.sample(frac=1)
DataTranse = DataTranse.sample(frac=1)
DataTranse = DataTranse.sample(frac=1)
DataTranse = DataTranse.sample(frac=1)
DataTranse = DataTranse.sample(frac=1)
DataTranse.to_csv("../data/data_transfer.csv",index=False)