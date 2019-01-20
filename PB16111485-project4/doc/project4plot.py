import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import spline
import math 

Size = np.array( [pow(2,5), pow(2,8), pow(2,11), pow(2,14), pow(2,17)] )

#InsertionSort = np.array( [1, 3, 84, 4071, 194284, 12283691] )
#N_1_42 = np.array([pow(i * 10000,1.42) for i in range(int(pow(2,17) / 10000))])
#N_1_37 = np.array([pow(i * 10000,1.37) for i in range(int(pow(2,17) / 10000))])

RabinKarp = np.array( [35, 43, 173,  898, 8943] )
KMPalg    = np.array( [20, 41,  91,  641, 4179] )
BMHalg    = np.array( [20, 29,  67,  333, 1903] )
ONtime1    = 0.1 * Size
ONtime2    = 0.01 * Size
#NlgN1 = np.array([i * 10000 * math.log(i * 10000 + 1) * 0.01 for i in range(int(pow(2,17) / 10000))])
#Sizenew = np.linspace(Size.min(),Size.max(),30) #300 represents number of points to make between T.min and T.max
#Xnew = np.linspace(X.min(),X.max(),30)

#InsertionSort_smooth = spline(Size,InsertionSort,Sizenew)
#N_1_42_smooth = spline(X,N_1_42,Xnew)
#N_1_37_smooth = spline(X,N_1_37,Xnew)

#MergeSort_smooth = spline(Size,MergeSort,Sizenew)
#QuickSort_smooth = spline(Size,QuickSort,Sizenew)
#NlgN3_smooth = spline(Size,NlgN3,Sizenew)
#CountingSort_smooth = spline(Size,CountingSort,Sizenew)
#RadixSort_smooth = spline(Size,RadixSort,Sizenew)
#N15_smooth = spline(X,N15,Xnew)
#N09_smooth = spline(X,N09,Xnew)
#plt.figure(figsize=(25,50))

#plt.plot(Sizenew,InsertionSort_smooth,label='$InsertionSort$',color="red",linewidth=2.0,linestyle='--')
#plt.plot(Xnew,N_1_42_smooth,label='$N^{1.45}$',color="blue",linewidth=2.0,linestyle='--')
#plt.plot(Xnew,N_1_37_smooth,label='$N^{1.35}$',color="green",linewidth=2.0,linestyle='--')

plt.plot(Size,RabinKarp,label='$RabinKarp$',color="red",linewidth=2.0,linestyle='--')
plt.plot(Size,KMPalg,label='$KMP$',color="blue",linewidth=2.0,linestyle='--')
plt.plot(Size,BMHalg,label='$BMH$',color="black",linewidth=2.0,linestyle='--')
plt.plot(Size,ONtime1,label='$0.1N$',color="green",linewidth=2.0,linestyle='--')
plt.plot(Size,ONtime2,label='$0.01N$',color="purple",linewidth=2.0,linestyle='--')
#plt.plot(Xnew,NlgN1_smooth,label='$0.1NlgN$',color="green",linewidth=2.0,linestyle='-.')

#plt.plot(Size,CountingSort,label='$CountingSort$',color="red",linewidth=2.0,linestyle='--')
#plt.plot(Size,RadixSort,label='$RadixSort$',color="blue",linewidth=2.0,linestyle='--')
#plt.plot(Xnew,N15_smooth,label='$0.6N$',color="green",linewidth=2.0,linestyle='--')
#plt.plot(Xnew,N09_smooth,label='$0.5N$',color="green",linewidth=2.0,linestyle='-.')


#plt.plot(Size,InsertionSort,label='$InsertionSort$',color="red",linewidth=1.0,linestyle='--')
#plt.plot(Size,MergeSort,label='$MergeSort$',color="black",linewidth=1.0,linestyle='-.')

plt.legend(loc='best')
plt.xlabel("Length of Text:n(With Length of Pattern: m = O(n))")
plt.ylabel("Time(unit:us)")
plt.title("String Matching Algorithm Performence")
plt.savefig("./NlgN.jpg")
plt.show()
