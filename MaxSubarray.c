#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define SIZE 5000
#define RANDOM_LIMIT 50
#define THRESHOLD 22
#define TESTTIMES 3

double Myrandom(void){
    int Sign = rand() % 2;
    return (rand() % RANDOM_LIMIT) / (100 * pow(-1,Sign + 2)); 
}

struct SubArray{
    int Left,Right;
    double Sum;
};
typedef struct SubArray SubArray;
SubArray BruteForceAlgorithm(double A[],int low,int high){
    SubArray result;
    result.Left = result.Right = 0;
    result.Sum = (-1) * __DBL_MAX__;
    int i,j;
    for(i = low;i <= high;i++){
        double CurrentSum = 0.0;
        for(j = i;j <= high;j++){
            CurrentSum += A[j];
            if(CurrentSum > result.Sum){
                result.Sum = CurrentSum;
                result.Left = i;
                result.Right = j;
            }
        }
    }
    return result;
}

SubArray FindMaxCrossingSubarray(double A[],int low,int high,int mid){
    SubArray result;
    double LeftSum = (-1)*__DBL_MAX__, RightSum = (-1)*__DBL_MAX__ ;
    int i;
    double CurrentSum;
    for(i = mid,CurrentSum = 0;i >= low;i--){
        CurrentSum += A[i];
        if(CurrentSum > LeftSum){
            LeftSum = CurrentSum;
            result.Left = i;
        }
    }
    for(i = mid + 1,CurrentSum = 0;i <= high;i++){
        CurrentSum += A[i];
        if(CurrentSum > RightSum){
            RightSum = CurrentSum;
            result.Right = i;
        }
    }
    result.Sum = LeftSum + RightSum;
    return result;
}

SubArray RecurrenceAlgorithm(double A[],int low,int high){
    if(low == high){
        SubArray result = {low,high,A[low]};
        return result;
    }
    else{
        int mid = (low + high) / 2;
        SubArray LeftMax = RecurrenceAlgorithm(A,low,mid);
        SubArray RightMax = RecurrenceAlgorithm(A,mid + 1,high);
        SubArray CrossMax = FindMaxCrossingSubarray(A,low,high,mid);
        if(LeftMax.Sum >= RightMax.Sum && LeftMax.Sum >= CrossMax.Sum) return LeftMax;
        else if(RightMax.Sum >= LeftMax.Sum && RightMax.Sum >= CrossMax.Sum) return RightMax;
        else return CrossMax;
    }
}

SubArray MixAlgorithm(double A[],int low,int high){
    if(high - low <= THRESHOLD)
        return BruteForceAlgorithm(A,low,high);
    else{
        int mid = (low + high) / 2;
        SubArray LeftMax = RecurrenceAlgorithm(A,low,mid);
        SubArray RightMax = RecurrenceAlgorithm(A,mid + 1,high);
        SubArray CrossMax = FindMaxCrossingSubarray(A,low,high,mid);
        if(LeftMax.Sum >= RightMax.Sum && LeftMax.Sum >= CrossMax.Sum) return LeftMax;
        else if(RightMax.Sum >= LeftMax.Sum && RightMax.Sum >= CrossMax.Sum) return RightMax;
        else return CrossMax;
    }
}

SubArray DynamicAlgorithm(double A[],int low,int high){
    SubArray result;
    result.Sum = A[high];
    result.Left = result.Right = high;
    double BestSumFromHere = A[high];
    int BestSumEnd = high,i;
    for(i = high - 1;i >= low;i--){
        if(BestSumFromHere >= 0)
            BestSumFromHere += A[i];
        else{
            BestSumFromHere = A[i];
            BestSumEnd = i;
        }
        if(BestSumFromHere > result.Sum){
            result.Sum = BestSumFromHere;
            result.Right = BestSumEnd;
            result.Left = i;
        }
    }
    return result;
}

int main(void){
    int j;
    int BruteTime = 0,RecurrTime = 0,DynamicTime = 0,MixTime = 0;
    for(j = 0;j < TESTTIMES;j++){
        srand((unsigned int)time(NULL));
        double TestData[SIZE];
        SubArray BruteResult,RecurrResult,DynamicResult,MixResult;
        int i;
        for(i = 0;i < SIZE;i++)
            TestData[i] = Myrandom();
        int BeginTime,EndTime;

        BeginTime = clock();
        BruteResult = BruteForceAlgorithm(TestData,0,SIZE-1);
        EndTime = clock();
        BruteTime += (EndTime - BeginTime);
        //printf("BruteForce time is: %dms\tResult is %d to %d, sum = %lf\n",EndTime - BeginTime,BruteResult.Left,BruteResult.Right,BruteResult.Sum);
        
        BeginTime = clock();
        RecurrResult = RecurrenceAlgorithm(TestData,0,SIZE-1);
        EndTime = clock();
        RecurrTime += (EndTime - BeginTime);
        //printf("Recurrence time is: %dms\tResult is %d to %d, sum = %lf\n",EndTime - BeginTime,RecurrResult.Left,RecurrResult.Right,RecurrResult.Sum);

        BeginTime = clock();
        DynamicResult = DynamicAlgorithm(TestData,0,SIZE-1);
        EndTime = clock();
        DynamicTime += (EndTime - BeginTime);
        //printf("Dynamicalg time is: %dms\tResult is %d to %d, sum = %lf\n",EndTime - BeginTime,DynamicResult.Left,DynamicResult.Right,DynamicResult.Sum);
        
        BeginTime = clock();
        MixResult = MixAlgorithm(TestData,0,SIZE-1);
        EndTime = clock();
        MixTime += (EndTime - BeginTime);
    }
    printf("BruteTimeAverage:\t %lf\n",BruteTime / (double)TESTTIMES);
    printf("RecurrTimeAverage:\t %lf\n",RecurrTime / (double)TESTTIMES);
    printf("DynamicTimeAverage:\t %lf\n",DynamicTime / (double)TESTTIMES);
    printf("MixTimeAverage:\t\t %lf\n",MixTime / (double)TESTTIMES);
    return 0;
}