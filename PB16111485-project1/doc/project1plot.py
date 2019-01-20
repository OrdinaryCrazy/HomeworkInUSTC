import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import spline
import math 

Size = np.array( [pow(2,2), pow(2,5), pow(2,8), pow(2,11), pow(2,14), pow(2,17)] )
X = np.array([i * 10000 for i in range(int(pow(2,17) / 10000))])

#InsertionSort = np.array( [1, 3, 84, 4071, 194284, 12283691] )
#N_1_42 = np.array([pow(i * 10000,1.42) for i in range(int(pow(2,17) / 10000))])
#N_1_37 = np.array([pow(i * 10000,1.37) for i in range(int(pow(2,17) / 10000))])


MergeSort = np.array( [2, 4, 32, 300, 2967, 26827] )
QuickSort = np.array( [1, 3, 24, 254, 2329, 24263] )
HeapSort = np.array( [1, 4, 38, 399, 4166, 41015] )
NlgN3 = np.array([i * 10000 * math.log(i * 10000 + 1) * 0.03 for i in range(int(pow(2,17) / 10000))])
NlgN1 = np.array([i * 10000 * math.log(i * 10000 + 1) * 0.01 for i in range(int(pow(2,17) / 10000))])

#CountingSort = np.array( [331, 316, 317, 420, 440, 1620] )
#RadixSort = np.array( [19, 18, 140, 1161, 8996, 71721] )
#N15 = np.array([i * 10000 * 0.6 for i in range(int(pow(2,17) / 10000))])
#N09 = np.array([i * 10000 * 0.5 for i in range(int(pow(2,17) / 10000))])

#Sizenew = np.linspace(Size.min(),Size.max(),30) #300 represents number of points to make between T.min and T.max
Xnew = np.linspace(X.min(),X.max(),30)

#InsertionSort_smooth = spline(Size,InsertionSort,Sizenew)
#N_1_42_smooth = spline(X,N_1_42,Xnew)
#N_1_37_smooth = spline(X,N_1_37,Xnew)

#MergeSort_smooth = spline(Size,MergeSort,Sizenew)
#QuickSort_smooth = spline(Size,QuickSort,Sizenew)
NlgN3_smooth = spline(X,NlgN3,Xnew)
NlgN1_smooth = spline(X,NlgN1,Xnew)

#CountingSort_smooth = spline(Size,CountingSort,Sizenew)
#RadixSort_smooth = spline(Size,RadixSort,Sizenew)
#N15_smooth = spline(X,N15,Xnew)
#N09_smooth = spline(X,N09,Xnew)
#plt.figure(figsize=(25,50))

#plt.plot(Sizenew,InsertionSort_smooth,label='$InsertionSort$',color="red",linewidth=2.0,linestyle='--')
#plt.plot(Xnew,N_1_42_smooth,label='$N^{1.45}$',color="blue",linewidth=2.0,linestyle='--')
#plt.plot(Xnew,N_1_37_smooth,label='$N^{1.35}$',color="green",linewidth=2.0,linestyle='--')

plt.plot(Size,MergeSort,label='$MergeSort$',color="red",linewidth=2.0,linestyle='--')
plt.plot(Size,QuickSort,label='$QuickSort$',color="blue",linewidth=2.0,linestyle='--')
plt.plot(Size,HeapSort,label='$HeapSort$',color="black",linewidth=2.0,linestyle='--')
plt.plot(Xnew,NlgN3_smooth,label='$0.3NlgN$',color="green",linewidth=2.0,linestyle='--')
plt.plot(Xnew,NlgN1_smooth,label='$0.1NlgN$',color="green",linewidth=2.0,linestyle='-.')

#plt.plot(Size,CountingSort,label='$CountingSort$',color="red",linewidth=2.0,linestyle='--')
#plt.plot(Size,RadixSort,label='$RadixSort$',color="blue",linewidth=2.0,linestyle='--')
#plt.plot(Xnew,N15_smooth,label='$0.6N$',color="green",linewidth=2.0,linestyle='--')
#plt.plot(Xnew,N09_smooth,label='$0.5N$',color="green",linewidth=2.0,linestyle='-.')


#plt.plot(Size,InsertionSort,label='$InsertionSort$',color="red",linewidth=1.0,linestyle='--')
#plt.plot(Size,MergeSort,label='$MergeSort$',color="black",linewidth=1.0,linestyle='-.')

plt.legend(loc='best')
plt.xlabel("Size of Input Set")
plt.ylabel("Time")
plt.savefig("./NlgN.jpg")
plt.show()
