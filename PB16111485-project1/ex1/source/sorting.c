/**
 * Name:soting.c
 * Author:ZhangJingtun PB16111485
 * Platform:Ubuntu17.10
 * CompileInstruction:gcc sorting.c -o sorting -lm
 * LastModified:20181021
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define RANGE 65540
#define DIMENSION 5

void InsertionSort(int* A,int length){
    int j;
    for(j = 1;j < length;j++){
        int key = A[j];
        //insert A[j] into the sorted sequence A[1..j-1]
        int i = j - 1;
        while(i >= 0 && A[i] > key){
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = key;
    }
    return;
}
void Merge(int* A,int p,int q,int r){
    int LeftLength = q - p + 1;
    int RightLength = r - q;
    int Left[LeftLength + 1],Right[RightLength + 1];
    int i,j,k;
    for(i = 0;i < LeftLength;i++){
        Left[i] = A[p + i];
    }
    for(i = 0;i < RightLength;i++){
        Right[i] = A[q + i + 1];
    }
    Left[LeftLength] = __INT_MAX__;
    Right[RightLength] = __INT_MAX__;
    for(i = 0,j = 0,k = p;k <= r;k++){
        if(Left[i] <= Right[j]){
            A[k] = Left[i];
            i++;
        }
        else{
            A[k] = Right[j];
            j++;
        }
    }
    return;
}
void MergeSort(int* A,int p,int r){
    if(p < r){
        int q = (p + r) / 2;
        MergeSort(A,p,q);
        MergeSort(A,q + 1,r);
        //now A[p..q] and A[q+1..r] are both sorted array
        Merge(A,p,q,r);
    }
    return;
}
void CountingSortForRadix(int* A,int* B,int lengthofA,int d){
    //offer stable sort method to RadixSort
    int CountAndPosition[10];
    int i;
    for(i = 0;i < 10;i++){
        CountAndPosition[i] = 0;
    }
    for(i = 0;i < lengthofA;i++){
        CountAndPosition[ (A[i]/(int)pow(10,d-1))%10 ]++;
    }
    //now CountAndPosition[i] contains the number of elements equals to i
    for(i = 1;i < 10;i++){
        CountAndPosition[i] = CountAndPosition[i] + CountAndPosition[i - 1];
    }
    //now CountAndPosition[i] contains the position of elements equals to i to be insert into B
    for(i = lengthofA - 1;i >= 0;i--){
        B[ CountAndPosition[ (A[i]/(int)pow(10,d-1))%10 ] - 1 ] = A[i];
        CountAndPosition[ (A[i]/(int)pow(10,d-1))%10 ]--;
    }
    return;
}
void Swap(int* a,int* b){
    int c = *a;
    *a = *b;
    *b = c;
    return;
}
int Partition(int* A,int p,int r){
    int key = A[r];
    int i = p - 1,j;
    for(j = p;j < r;j++){
        if(A[j] <= key){
            i++;
            Swap(&A[i],&A[j]);
        }
    }
    Swap(&A[i + 1],&A[r]);
    return i + 1;
}
void QuickSort(int* A,int p,int r){
    if(p < r){
        int q = Partition(A,p,r);
        QuickSort(A,p,q - 1);
        QuickSort(A,q + 1,r);
    }
    return;
}
void CountingSort(int* A,int* B,int lengthofA){
    int CountAndPosition[RANGE];
    int i;
    for(i = 0;i < RANGE;i++){
        CountAndPosition[i] = 0;
    }
    for(i = 0;i < lengthofA;i++){
        CountAndPosition[A[i]]++;
    }
    //now CountAndPosition[i] contains the number of elements equals to i
    for(i = 1;i < RANGE;i++){
        CountAndPosition[i] = CountAndPosition[i] + CountAndPosition[i - 1];
    }
    //now CountAndPosition[i] contains the position of elements equals to i to be insert into B
    for(i = lengthofA - 1;i >= 0;i--){
        B[ CountAndPosition[ A[i] ] - 1 ] = A[i];
        CountAndPosition[ A[i] ]--;
    }
    return;
}
void RadixSort(int* A,int d,int length){
    int i,j;
    int* B = malloc(length * sizeof(int));
    for(i = 1;i <= d;i++){
        CountingSortForRadix(A,B,length,i);
        for(j = 0;j < length;j++){
            A[j] = B[j];
        }
    }
    free(B);B = NULL;
    return;
}
void MaxHeapIfy(int* A,int i,int length){
    int LeftChild = 2 * i + 1;
    int RightChild = 2 * i + 2;
    int Largest = i;
    if(LeftChild < length && A[LeftChild] > A[Largest]){
        Largest = LeftChild;
    }
    if(RightChild < length && A[RightChild] > A[Largest]){
        Largest = RightChild;
    }
    if(Largest != i){
        Swap(&A[Largest],&A[i]);
        MaxHeapIfy(A,Largest,length);
    }
    return;
}
void BuildMaxHeap(int* A,int length){
    int i;
    for(i = (length - 1)/2;i >= 0;i--){
        MaxHeapIfy(A,i,length);
    }
    return;
}
void HeapSort(int* A,int length){
    BuildMaxHeap(A,length);
    int i;
    for(i = length - 1;i > 0;i--){
        Swap(&A[i],&A[0]);
        int InOrder = length - i;
        MaxHeapIfy(A,0,length - InOrder);
    }
    return;
}
int main(int argc,char* argv){
    FILE* inputfile = fopen("../input/input_integer.txt","r");
    if(inputfile == NULL){
        printf("FILE OPEN ERROR.\n");
        exit(0);
    }
    int Length1 = (int)pow(2,2);
    int Length2 = (int)pow(2,5);
    int Length3 = (int)pow(2,8);
    int Length4 = (int)pow(2,11);
    int Length5 = (int)pow(2,14);
    int Length6 = (int)pow(2,17);
    int BeginTime,EndTime;
    int i;
    int Origin[Length6];
    for(i = 0;i < Length6;i++){
        fscanf(inputfile,"%d\n",&Origin[i]);
    }
    fclose(inputfile);
    //data input finished
    int* A = NULL;
    //InsertionSort test
    FILE* InsertionSortFileTime = fopen("../output/InsertionSort/time.txt","w");
    FILE* InsertionSortFileResult = NULL;
    //------------------------------------2^2-----------------------------------------------------------
    A = (int*)malloc(Length1 * sizeof(int));
    for(i = 0;i < Length1;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    InsertionSort(A,Length1);
    EndTime = clock();
    InsertionSortFileResult = fopen("../output/InsertionSort/result_2.txt","w");
    for(i = 0;i < Length1;i++){ fprintf(InsertionSortFileResult,"%d\n",A[i]); }
    fclose(InsertionSortFileResult);
    fprintf(InsertionSortFileTime,"n = 2,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^5-----------------------------------------------------------
    A = (int*)malloc(Length2 * sizeof(int));
    for(i = 0;i < Length2;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    InsertionSort(A,Length2);
    EndTime = clock();
    InsertionSortFileResult = fopen("../output/InsertionSort/result_5.txt","w");
    for(i = 0;i < Length2;i++){ fprintf(InsertionSortFileResult,"%d\n",A[i]); }
    fclose(InsertionSortFileResult);
    fprintf(InsertionSortFileTime,"n = 5,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^8-----------------------------------------------------------
    A = (int*)malloc(Length3 * sizeof(int));
    for(i = 0;i < Length3;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    InsertionSort(A,Length3);
    EndTime = clock();
    InsertionSortFileResult = fopen("../output/InsertionSort/result_8.txt","w");
    for(i = 0;i < Length3;i++){ fprintf(InsertionSortFileResult,"%d\n",A[i]); }
    fclose(InsertionSortFileResult);
    fprintf(InsertionSortFileTime,"n = 8,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^11-----------------------------------------------------------
    A = (int*)malloc(Length4 * sizeof(int));
    for(i = 0;i < Length4;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    InsertionSort(A,Length4);
    EndTime = clock();
    InsertionSortFileResult = fopen("../output/InsertionSort/result_11.txt","w");
    for(i = 0;i < Length4;i++){ fprintf(InsertionSortFileResult,"%d\n",A[i]); }
    fclose(InsertionSortFileResult);
    fprintf(InsertionSortFileTime,"n = 11,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^14-----------------------------------------------------------
    A = (int*)malloc(Length5 * sizeof(int));
    for(i = 0;i < Length5;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    InsertionSort(A,Length5);
    EndTime = clock();
    InsertionSortFileResult = fopen("../output/InsertionSort/result_14.txt","w");
    for(i = 0;i < Length5;i++){ fprintf(InsertionSortFileResult,"%d\n",A[i]); }
    fclose(InsertionSortFileResult);
    fprintf(InsertionSortFileTime,"n = 14,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^17-----------------------------------------------------------
    A = (int*)malloc(Length6 * sizeof(int));
    for(i = 0;i < Length6;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    InsertionSort(A,Length6);
    EndTime = clock();
    InsertionSortFileResult = fopen("../output/InsertionSort/result_17.txt","w");
    for(i = 0;i < Length6;i++){ fprintf(InsertionSortFileResult,"%d\n",A[i]); }
    fclose(InsertionSortFileResult);
    fprintf(InsertionSortFileTime,"n = 17,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //-----------------------------------------------------------------------------------------------
    fclose(InsertionSortFileTime);
    //MergeSort test
    FILE* MergeSortFileTime = fopen("../output/MergeSort/time.txt","w");
    FILE* MergeSortFileResult = NULL;
    //------------------------------------2^2-----------------------------------------------------------
    A = (int*)malloc(Length1 * sizeof(int));
    for(i = 0;i < Length1;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    MergeSort(A,0,Length1 - 1);
    EndTime = clock();
    MergeSortFileResult = fopen("../output/MergeSort/result_2.txt","w");
    for(i = 0;i < Length1;i++){ fprintf(MergeSortFileResult,"%d\n",A[i]); }
    fclose(MergeSortFileResult);
    fprintf(MergeSortFileTime,"n = 2,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^5-----------------------------------------------------------
    A = (int*)malloc(Length2 * sizeof(int));
    for(i = 0;i < Length2;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    MergeSort(A,0,Length2 - 1);
    EndTime = clock();
    MergeSortFileResult = fopen("../output/MergeSort/result_5.txt","w");
    for(i = 0;i < Length2;i++){ fprintf(MergeSortFileResult,"%d\n",A[i]); }
    fclose(MergeSortFileResult);
    fprintf(MergeSortFileTime,"n = 5,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^8-----------------------------------------------------------
    A = (int*)malloc(Length3 * sizeof(int));
    for(i = 0;i < Length3;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    MergeSort(A,0,Length3 - 1);
    EndTime = clock();
    MergeSortFileResult = fopen("../output/MergeSort/result_8.txt","w");
    for(i = 0;i < Length3;i++){ fprintf(MergeSortFileResult,"%d\n",A[i]); }
    fclose(MergeSortFileResult);
    fprintf(MergeSortFileTime,"n = 8,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^11-----------------------------------------------------------
    A = (int*)malloc(Length4 * sizeof(int));
    for(i = 0;i < Length4;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    MergeSort(A,0,Length4 - 1);
    EndTime = clock();
    MergeSortFileResult = fopen("../output/MergeSort/result_11.txt","w");
    for(i = 0;i < Length4;i++){ fprintf(MergeSortFileResult,"%d\n",A[i]); }
    fclose(MergeSortFileResult);
    fprintf(MergeSortFileTime,"n = 11,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^14-----------------------------------------------------------
    A = (int*)malloc(Length5 * sizeof(int));
    for(i = 0;i < Length5;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    MergeSort(A,0,Length5 - 1);
    EndTime = clock();
    MergeSortFileResult = fopen("../output/MergeSort/result_14.txt","w");
    for(i = 0;i < Length5;i++){ fprintf(MergeSortFileResult,"%d\n",A[i]); }
    fclose(MergeSortFileResult);
    fprintf(MergeSortFileTime,"n = 14,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^17-----------------------------------------------------------
    A = (int*)malloc(Length6 * sizeof(int));
    for(i = 0;i < Length6;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    MergeSort(A,0,Length6 - 1);
    EndTime = clock();
    MergeSortFileResult = fopen("../output/MergeSort/result_17.txt","w");
    for(i = 0;i < Length6;i++){ fprintf(MergeSortFileResult,"%d\n",A[i]); }
    fclose(MergeSortFileResult);
    fprintf(MergeSortFileTime,"n = 17,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //-----------------------------------------------------------------------------------------------
    fclose(MergeSortFileTime);
    //QuickSort test
    FILE* QuickSortFileTime = fopen("../output/QuickSort/time.txt","w");
    FILE* QuickSortFileResult = NULL;
    //------------------------------------2^2-----------------------------------------------------------
    A = (int*)malloc(Length1 * sizeof(int));
    for(i = 0;i < Length1;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    QuickSort(A,0,Length1 - 1);
    EndTime = clock();
    QuickSortFileResult = fopen("../output/QuickSort/result_2.txt","w");
    for(i = 0;i < Length1;i++){ fprintf(QuickSortFileResult,"%d\n",A[i]); }
    fclose(QuickSortFileResult);
    fprintf(QuickSortFileTime,"n = 2,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^5-----------------------------------------------------------
    A = (int*)malloc(Length2 * sizeof(int));
    for(i = 0;i < Length2;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    QuickSort(A,0,Length2 - 1);
    EndTime = clock();
    QuickSortFileResult = fopen("../output/QuickSort/result_5.txt","w");
    for(i = 0;i < Length2;i++){ fprintf(QuickSortFileResult,"%d\n",A[i]); }
    fclose(QuickSortFileResult);
    fprintf(QuickSortFileTime,"n = 5,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^8-----------------------------------------------------------
    A = (int*)malloc(Length3 * sizeof(int));
    for(i = 0;i < Length3;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    QuickSort(A,0,Length3 - 1);
    EndTime = clock();
    QuickSortFileResult = fopen("../output/QuickSort/result_8.txt","w");
    for(i = 0;i < Length3;i++){ fprintf(QuickSortFileResult,"%d\n",A[i]); }
    fclose(QuickSortFileResult);
    fprintf(QuickSortFileTime,"n = 8,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^11-----------------------------------------------------------
    A = (int*)malloc(Length4 * sizeof(int));
    for(i = 0;i < Length4;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    QuickSort(A,0,Length4 - 1);
    EndTime = clock();
    QuickSortFileResult = fopen("../output/QuickSort/result_11.txt","w");
    for(i = 0;i < Length4;i++){ fprintf(QuickSortFileResult,"%d\n",A[i]); }
    fclose(QuickSortFileResult);
    fprintf(QuickSortFileTime,"n = 11,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^14-----------------------------------------------------------
    A = (int*)malloc(Length5 * sizeof(int));
    for(i = 0;i < Length5;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    QuickSort(A,0,Length5 - 1);
    EndTime = clock();
    QuickSortFileResult = fopen("../output/QuickSort/result_14.txt","w");
    for(i = 0;i < Length5;i++){ fprintf(QuickSortFileResult,"%d\n",A[i]); }
    fclose(QuickSortFileResult);
    fprintf(QuickSortFileTime,"n = 14,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^17-----------------------------------------------------------
    A = (int*)malloc(Length6 * sizeof(int));
    for(i = 0;i < Length6;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    QuickSort(A,0,Length6 - 1);
    EndTime = clock();
    QuickSortFileResult = fopen("../output/QuickSort/result_17.txt","w");
    for(i = 0;i < Length6;i++){ fprintf(QuickSortFileResult,"%d\n",A[i]); }
    fclose(QuickSortFileResult);
    fprintf(QuickSortFileTime,"n = 17,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //-----------------------------------------------------------------------------------------------
    fclose(QuickSortFileTime);
    //CountingSort test
    int* B = NULL;
    FILE* CountingSortFileTime = fopen("../output/CountingSort/time.txt","w");
    FILE* CountingSortFileResult = NULL;
    //------------------------------------2^2-----------------------------------------------------------
    A = (int*)malloc(Length1 * sizeof(int));
    B = (int*)malloc(Length1 * sizeof(int));
    for(i = 0;i < Length1;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    CountingSort(A,B,Length1);
    EndTime = clock();
    CountingSortFileResult = fopen("../output/CountingSort/result_2.txt","w");
    for(i = 0;i < Length1;i++){ fprintf(CountingSortFileResult,"%d\n",B[i]); }
    fclose(CountingSortFileResult);
    fprintf(CountingSortFileTime,"n = 2,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;free(B);B = NULL;
    //------------------------------------2^5-----------------------------------------------------------
    A = (int*)malloc(Length2 * sizeof(int));
    B = (int*)malloc(Length2 * sizeof(int));
    for(i = 0;i < Length2;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    CountingSort(A,B,Length2);
    EndTime = clock();
    CountingSortFileResult = fopen("../output/CountingSort/result_5.txt","w");
    for(i = 0;i < Length2;i++){ fprintf(CountingSortFileResult,"%d\n",B[i]); }
    fclose(CountingSortFileResult);
    fprintf(CountingSortFileTime,"n = 5,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;free(B);B = NULL;
    //------------------------------------2^8-----------------------------------------------------------
    A = (int*)malloc(Length3 * sizeof(int));
    B = (int*)malloc(Length3 * sizeof(int));
    for(i = 0;i < Length3;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    CountingSort(A,B,Length3);
    EndTime = clock();
    CountingSortFileResult = fopen("../output/CountingSort/result_8.txt","w");
    for(i = 0;i < Length3;i++){ fprintf(CountingSortFileResult,"%d\n",B[i]); }
    fclose(CountingSortFileResult);
    fprintf(CountingSortFileTime,"n = 8,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;free(B);B = NULL;
    //------------------------------------2^11-----------------------------------------------------------
    A = (int*)malloc(Length4 * sizeof(int));
    B = (int*)malloc(Length4 * sizeof(int));
    for(i = 0;i < Length4;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    CountingSort(A,B,Length4);
    EndTime = clock();
    CountingSortFileResult = fopen("../output/CountingSort/result_11.txt","w");
    for(i = 0;i < Length4;i++){ fprintf(CountingSortFileResult,"%d\n",B[i]); }
    fclose(CountingSortFileResult);
    fprintf(CountingSortFileTime,"n = 11,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;free(B);B = NULL;
    //------------------------------------2^14-----------------------------------------------------------
    A = (int*)malloc(Length5 * sizeof(int));
    B = (int*)malloc(Length5 * sizeof(int));
    for(i = 0;i < Length5;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    CountingSort(A,B,Length5);
    EndTime = clock();
    CountingSortFileResult = fopen("../output/CountingSort/result_14.txt","w");
    for(i = 0;i < Length5;i++){ fprintf(CountingSortFileResult,"%d\n",B[i]); }
    fclose(CountingSortFileResult);
    fprintf(CountingSortFileTime,"n = 14,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;free(B);B = NULL;
    //------------------------------------2^17-----------------------------------------------------------
    A = (int*)malloc(Length6 * sizeof(int));
    B = (int*)malloc(Length6 * sizeof(int));
    for(i = 0;i < Length6;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    CountingSort(A,B,Length6);
    EndTime = clock();
    CountingSortFileResult = fopen("../output/CountingSort/result_17.txt","w");
    for(i = 0;i < Length6;i++){ fprintf(CountingSortFileResult,"%d\n",B[i]); }
    fclose(CountingSortFileResult);
    fprintf(CountingSortFileTime,"n = 17,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;free(B);B = NULL;
    //-----------------------------------------------------------------------------------------------
    fclose(CountingSortFileTime);
    //RadixSort test
    FILE* RadixSortFileTime = fopen("../output/RadixSort/time.txt","w");
    FILE* RadixSortFileResult = NULL;
    //------------------------------------2^2-----------------------------------------------------------
    A = (int*)malloc(Length1 * sizeof(int));
    for(i = 0;i < Length1;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    RadixSort(A,DIMENSION,Length1);
    EndTime = clock();
    RadixSortFileResult = fopen("../output/RadixSort/result_2.txt","w");
    for(i = 0;i < Length1;i++){ fprintf(RadixSortFileResult,"%d\n",A[i]); }
    fclose(RadixSortFileResult);
    fprintf(RadixSortFileTime,"n = 2,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^5-----------------------------------------------------------
    A = (int*)malloc(Length2 * sizeof(int));
    for(i = 0;i < Length2;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    RadixSort(A,DIMENSION,Length2);
    EndTime = clock();
    RadixSortFileResult = fopen("../output/RadixSort/result_5.txt","w");
    for(i = 0;i < Length2;i++){ fprintf(RadixSortFileResult,"%d\n",A[i]); }
    fclose(RadixSortFileResult);
    fprintf(RadixSortFileTime,"n = 5,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^8-----------------------------------------------------------
    A = (int*)malloc(Length3 * sizeof(int));
    for(i = 0;i < Length3;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    RadixSort(A,DIMENSION,Length3);
    EndTime = clock();
    RadixSortFileResult = fopen("../output/RadixSort/result_8.txt","w");
    for(i = 0;i < Length3;i++){ fprintf(RadixSortFileResult,"%d\n",A[i]); }
    fclose(RadixSortFileResult);
    fprintf(RadixSortFileTime,"n = 8,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^11-----------------------------------------------------------
    A = (int*)malloc(Length4 * sizeof(int));
    for(i = 0;i < Length4;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    RadixSort(A,DIMENSION,Length4);
    EndTime = clock();
    RadixSortFileResult = fopen("../output/RadixSort/result_11.txt","w");
    for(i = 0;i < Length4;i++){ fprintf(RadixSortFileResult,"%d\n",A[i]); }
    fclose(RadixSortFileResult);
    fprintf(RadixSortFileTime,"n = 11,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^14-----------------------------------------------------------
    A = (int*)malloc(Length5 * sizeof(int));
    for(i = 0;i < Length5;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    RadixSort(A,DIMENSION,Length5);
    EndTime = clock();
    RadixSortFileResult = fopen("../output/RadixSort/result_14.txt","w");
    for(i = 0;i < Length5;i++){ fprintf(RadixSortFileResult,"%d\n",A[i]); }
    fclose(RadixSortFileResult);
    fprintf(RadixSortFileTime,"n = 14,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^17-----------------------------------------------------------
    A = (int*)malloc(Length6 * sizeof(int));
    for(i = 0;i < Length6;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    RadixSort(A,DIMENSION,Length6);
    EndTime = clock();
    RadixSortFileResult = fopen("../output/RadixSort/result_17.txt","w");
    for(i = 0;i < Length6;i++){ fprintf(RadixSortFileResult,"%d\n",A[i]); }
    fclose(RadixSortFileResult);
    fprintf(RadixSortFileTime,"n = 17,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //-----------------------------------------------------------------------------------------------
    fclose(RadixSortFileTime);
    //HeapSort test
    FILE* HeapSortFileTime = fopen("../output/HeapSort/time.txt","w");
    FILE* HeapSortFileResult = NULL;
    //------------------------------------2^2-----------------------------------------------------------
    A = (int*)malloc(Length1 * sizeof(int));
    for(i = 0;i < Length1;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    HeapSort(A,Length1);
    EndTime = clock();
    HeapSortFileResult = fopen("../output/HeapSort/result_2.txt","w");
    for(i = 0;i < Length1;i++){ fprintf(HeapSortFileResult,"%d\n",A[i]); }
    fclose(HeapSortFileResult);
    fprintf(HeapSortFileTime,"n = 2,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^5-----------------------------------------------------------
    A = (int*)malloc(Length2 * sizeof(int));
    for(i = 0;i < Length2;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    HeapSort(A,Length2);
    EndTime = clock();
    HeapSortFileResult = fopen("../output/HeapSort/result_5.txt","w");
    for(i = 0;i < Length2;i++){ fprintf(HeapSortFileResult,"%d\n",A[i]); }
    fclose(HeapSortFileResult);
    fprintf(HeapSortFileTime,"n = 5,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^8-----------------------------------------------------------
    A = (int*)malloc(Length3 * sizeof(int));
    for(i = 0;i < Length3;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    HeapSort(A,Length3);
    EndTime = clock();
    HeapSortFileResult = fopen("../output/HeapSort/result_8.txt","w");
    for(i = 0;i < Length3;i++){ fprintf(HeapSortFileResult,"%d\n",A[i]); }
    fclose(HeapSortFileResult);
    fprintf(HeapSortFileTime,"n = 8,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^11-----------------------------------------------------------
    A = (int*)malloc(Length4 * sizeof(int));
    for(i = 0;i < Length4;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    HeapSort(A,Length4);
    EndTime = clock();
    HeapSortFileResult = fopen("../output/HeapSort/result_11.txt","w");
    for(i = 0;i < Length4;i++){ fprintf(HeapSortFileResult,"%d\n",A[i]); }
    fclose(HeapSortFileResult);
    fprintf(HeapSortFileTime,"n = 11,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^14-----------------------------------------------------------
    A = (int*)malloc(Length5 * sizeof(int));
    for(i = 0;i < Length5;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    HeapSort(A,Length5);
    EndTime = clock();
    HeapSortFileResult = fopen("../output/HeapSort/result_14.txt","w");
    for(i = 0;i < Length5;i++){ fprintf(HeapSortFileResult,"%d\n",A[i]); }
    fclose(HeapSortFileResult);
    fprintf(HeapSortFileTime,"n = 14,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //------------------------------------2^17-----------------------------------------------------------
    A = (int*)malloc(Length6 * sizeof(int));
    for(i = 0;i < Length6;i++){ A[i] = Origin[i]; }
    BeginTime = clock();
    HeapSort(A,Length6);
    EndTime = clock();
    HeapSortFileResult = fopen("../output/HeapSort/result_17.txt","w");
    for(i = 0;i < Length6;i++){ fprintf(HeapSortFileResult,"%d\n",A[i]); }
    fclose(HeapSortFileResult);
    fprintf(HeapSortFileTime,"n = 17,\ttime = %d ms\n",EndTime - BeginTime);
    free(A);A = NULL;
    //-----------------------------------------------------------------------------------------------
    fclose(HeapSortFileTime);
    //end
    return 0;
}
