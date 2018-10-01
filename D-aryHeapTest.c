#include <stdio.h>
#include <stdlib.h>
// children number for one node
#define D 4
int Parent(int i){
    return i / D;
}
int Child(int i,int k){
    return i * D + k - 1;
}
struct DaryHeap{
    int* Data;
    int HeapSize,Length;
};
typedef struct DaryHeap DaryHeap;
void MaxDaryHeapIfy(DaryHeap* A,int i){
    int Largest = i;
    int j;
    for(j = 1;j <= D;j++){
        int Child_j = Child(i,j);
        if(Child_j <= A->HeapSize && A->Data[Child_j] > A->Data[Largest]){
            Largest = Child_j;
        }
    }
    if(Largest != i){
        int tmp = A->Data[i];
        A->Data[i] = A->Data[Largest];
        A->Data[Largest] = tmp;
        MaxDaryHeapIfy(A,Largest);
    }
}
int ExtractMaxDary(DaryHeap* A){
    if(A->HeapSize < 1){
        printf(" heap underflow ");
        exit(0);
    }
    int Max = A->Data[1];
    A->Data[1] = A->Data[A->HeapSize];
    A->HeapSize--;
    MaxDaryHeapIfy(A,1);
    return Max;
}
void HeapIncreaseKey(DaryHeap* A,int i,int key){
    if( key < A->Data[i]){
        printf(" new key is smaller than current key ");
        exit(0);
    }
    while(i > 1 && A->Data[Parent(i)] < key){
        A->Data[i] = A->Data[Parent(i)];
        i = Parent(i);
    }
    A->Data[i] = key;
}
void InsertDary(DaryHeap* A,int key){
    A->HeapSize++;
    A->Data[A->HeapSize] = (-1)*(((unsigned)-1)>>1);
    HeapIncreaseKey(A,A->HeapSize,key);
}

int main(void){
    int i;
    int array[24] = {0,5,0,0,\
                     2,9,56,8,    0,0,0,0,  0,0,0,0,\
                     23,59,61,13, 4,7,15};
    DaryHeap Test;
    Test.Data = array;
    Test.HeapSize = Test.Length = 22;
    for(i = 0;i <= Test.HeapSize;i++){printf("%d ",Test.Data[i]);}printf("\n");
    MaxDaryHeapIfy(&Test,4);
    for(i = 0;i <= Test.HeapSize;i++){printf("%d ",Test.Data[i]);}printf("\n");
    MaxDaryHeapIfy(&Test,5);
    for(i = 0;i <= Test.HeapSize;i++){printf("%d ",Test.Data[i]);}printf("\n");
    MaxDaryHeapIfy(&Test,6);
    for(i = 0;i <= Test.HeapSize;i++){printf("%d ",Test.Data[i]);}printf("\n");
    MaxDaryHeapIfy(&Test,7);
    for(i = 0;i <= Test.HeapSize;i++){printf("%d ",Test.Data[i]);}printf("\n");

    MaxDaryHeapIfy(&Test,1);
    
    for(i = 0;i <= Test.HeapSize;i++){printf("%d ",Test.Data[i]);}printf("\n");
    printf("%d\n",ExtractMaxDary(&Test));
    for(i = 0;i <= Test.HeapSize;i++){printf("%d ",Test.Data[i]);}printf("\n");
    HeapIncreaseKey(&Test,6,159);
    for(i = 0;i <= Test.HeapSize;i++){printf("%d ",Test.Data[i]);}printf("\n");
    InsertDary(&Test,599);
    for(i = 0;i <= Test.HeapSize;i++){printf("%d ",Test.Data[i]);}printf("\n");
    return 0;
}