import numpy as np
import matplotlib.pyplot as plt
 
labels = 'admin.', 'blue-collar', 'entrepreneur', 'housemaid', 'management','retired','self-employed','services','student','technician','unemployed','unknown'
fracs = [10422,9254,1456,1060,2924,1720,1421,3969,875,6743,1014,330]
explode = [0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0] # 0.1 凸出这部分，
plt.axes(aspect=1)  # set this , Figure is round, otherwise it is an ellipse
#autopct ，show percet
plt.pie(x=fracs, labels=labels, explode=explode,autopct='%3.1f %%',
        shadow=True, labeldistance=1.1, startangle = 90,pctdistance = 0.6
 
        )
'''
labeldistance，文本的位置离远点有多远，1.1指1.1倍半径的位置
autopct，圆里面的文本格式，%3.1f%%表示小数有三位，整数有一位的浮点数
shadow，饼是否有阴影
startangle，起始角度，0，表示从0开始逆时针转，为第一块。一般选择从90度开始比较好看
pctdistance，百分比的text离圆心的距离
patches, l_texts, p_texts，为了得到饼图的返回值，p_texts饼图内部文本的，l_texts饼图外label的文本
'''
#plt.legend(loc='best')

plt.title("Distribution of Users Job")

plt.savefig("./job.jpg")
plt.show()