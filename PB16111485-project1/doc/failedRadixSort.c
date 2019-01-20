void RadixSort(int* A,int d,int length){
    int i;
    for(i = 1;i <= d;i++){
        MergeSortForRadixSort(A,0,length - 1,i);
    }
    return;
}
void MergeForRadixSort(int* A,int p,int q,int r,int d){
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
    Left[LeftLength] = 999999;
    Right[RightLength] = 999999;
    for(i = 0,j = 0,k = p;k <= r;k++){
        if( ( (Left[i]/((int)pow(10,d-1))) % 10 ) <= ( (Right[j]/((int)pow(10,d-1))) % 10 ) ){
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
void MergeSortForRadixSort(int* A,int p,int r,int d){
    if(p < r){
        int q = (p + r) / 2;
        MergeSortForRadixSort(A,p,q,d);
        MergeSortForRadixSort(A,q + 1,r,d);
        //now A[p..q] and A[q+1..r] are both sorted array
        MergeForRadixSort(A,p,q,r,d);
    }
    return;
}
