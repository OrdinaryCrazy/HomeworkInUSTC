import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import spline
import math 

#Size = np.array( [5, 10, 20, 30] )
Size = np.array( [15*10, 15*20, 15*25, 15*30, 15*40, 15*50,30*25, 15*60,   45*25, 60*25, 75*25, 90*25] )
#MatrixCM = np.array( [4, 16, 64, 168] )
LongestCS = np.array( [19, 24, 26, 29, 36, 46, 52, 53,   74, 99, 119, 149] )
#N_2 = np.array( [pow(5,3),pow(10,3),pow(20,3),pow(30,3)] )
#N_2_01 = N_2 * 0.003
#N_2_03 = N_2 * 0.01
mn_01 = Size * 0.05
mn_02 = Size * 0.1


#Sizenew = np.linspace(Size.min(),Size.max(),300) #300 represents number of points to make between T.min and T.max
#MatrixCM_smooth = spline(Size,MatrixCM,Sizenew)
#N_2_01_smooth = spline(Size,N_2_01,Sizenew)
#N_2_03_smooth = spline(Size,N_2_03,Sizenew)
#LongestCS_smooth = spline(Size,LongestCS,Sizenew)
#mn_01_smooth = spline(Size,mn_01,Sizenew)
#mn_02_smooth = spline(Size,mn_02,Sizenew)

#plt.plot(Sizenew,MatrixCM_smooth,label='$MatrixChainMultiply$',color="red",linewidth=2.0,linestyle='--')
#plt.plot(Sizenew,N_2_01_smooth,label='$0.03N^3$',color="green",linewidth=2.0,linestyle='--')
#plt.plot(Sizenew,N_2_03_smooth,label='$0.1N^3$',color="blue",linewidth=2.0,linestyle='--')
plt.plot(Size,LongestCS,label='$LongestCommonSubstring$',color="red",linewidth=2.0,linestyle='--')
plt.plot(Size,mn_01,label='$0.05 * m * n$',color="blue",linewidth=2.0,linestyle='--')
plt.plot(Size,mn_02,label='$0.1 * m * n$',color="green",linewidth=2.0,linestyle='--')

plt.legend(loc='best')
#plt.xlabel("Size of Matrix Sequence")
plt.xlabel("Size of Problem M(X.size) * N(Y.size)")
plt.ylabel("Time(unit: us)")
#plt.title("Time Curve of Matrix Chain Multiply Algorithm")
#plt.savefig("./MatrixCM.jpg")
plt.title("Time Curve of Longest Common Substring Algorithm")
plt.savefig("./LongestCS.jpg")
plt.show()
