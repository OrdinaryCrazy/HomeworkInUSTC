import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import spline
import math 

#Size = np.array( [5, 10, 20, 30] )
Size = np.array( [10,20,30,40,50,60,70,80,90,100] )
#MatrixCM = np.array( [4,16, 64, 168] )
LongestCS = np.array( [0,0,1,1,1,1,1,0,0,1] )
#N_2 = np.array( [pow(5,3),pow(10,3),pow(20,3),pow(30,3)] )
#N_2_01 = N_2 * 0.003
#N_2_03 = N_2 * 0.01
max_theory_time = np.log(Size)
perop_time = LongestCS * 0.1
 
#Sizenew = np.linspace(Size.min(),Size.max(),300) #300 represents number of points to make between T.min and T.max
#max_theory_time_smooth = spline(Size, max_theory_time, Sizenew)
#N_2_01_smooth = spline(Size,N_2_01,Sizenew)
#N_2_03_smooth = spline(Size,N_2_03,Sizenew)
#LongestCS_smooth = spline(Size,LongestCS,Sizenew)
#mn_01_smooth = spline(Size,mn_01,Sizenew)
#mn_02_smooth = spline(Size,mn_02,Sizenew)

#plt.plot(Sizenew,MatrixCM_smooth,label='$MatrixChainMultiply$',color="red",linewidth=2.0,linestyle='--')
#plt.plot(Sizenew,N_2_01_smooth,label='$0.03N^3$',color="green",linewidth=2.0,linestyle='--')
#plt.plot(Sizenew,N_2_03_smooth,label='$0.1N^3$',color="blue",linewidth=2.0,linestyle='--')
plt.plot(Size,max_theory_time,label='$log(n)$',color="red",linewidth=2.0,linestyle='--')
plt.plot(Size,perop_time,label='$time cost for one delete operation$',color="blue",linewidth=2.0,linestyle='--')
#plt.plot(Size,mn_02,label='$0.1 * m * n$',color="green",linewidth=2.0,linestyle='--')

plt.legend(loc='best')
#plt.xlabel("Size of Matrix Sequence")
plt.xlabel("Size of Problem n")
plt.ylabel("Time(unit: us)")
#plt.title("Time Curve of Matrix Chain Multiply Algorithm")
#plt.savefig("./MatrixCM.jpg")
plt.title("Delete time cost for RedBlackTree")
plt.savefig("./20D.jpg")
plt.show()
