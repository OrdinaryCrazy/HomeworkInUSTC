#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct result{
    int** m;
    int** s;
};
typedef struct result Result;
Result* MatrixChainOrder(int* p,int n){
    /**
     * function：确定矩阵相乘顺序
     * input: p:矩阵规模向量
     *        n:矩阵个数
     * output:Result->m:链乘代价矩阵
     *        Result->s:链乘划分点矩阵
     **/
    int i,j,l,k;
    Result* FinalResult = (Result*)malloc(sizeof(Result));
    FinalResult->m = (int**)malloc((n + 1) * sizeof(int*));
    FinalResult->s = (int**)malloc((n + 1) * sizeof(int*));
    for(i = 0;i <= n;i++){
        FinalResult->m[i] = (int*)malloc((n + 1) * sizeof(int));
        FinalResult->s[i] = (int*)malloc((n + 1) * sizeof(int));
    }
    for(i = 1;i <= n;i++){
        FinalResult->m[i][i] = 0;
    }
    for(l = 2;l <= n;l++){
        for(i = 1;i <= n-l+1;i++){
            j = i + l -1;
            FinalResult->m[i][j] = __INT_MAX__;
            for(k = i;k < j;k++){
                int q = FinalResult->m[i][k] + FinalResult->m[k+1][j] + p[i-1] * p[k] * p[j];
                if(q < FinalResult->m[i][j]){
                    FinalResult->m[i][j] = q;
                    FinalResult->s[i][j] = k;
                }
            }
        }
    }
    return FinalResult;
}
void PrintOptimalParens(int** s,int i,int j,FILE* OutputFile){
    /**
     * function:打印矩阵括号方案
     * input: s:链乘划分点矩阵
     *        i,j:链乘起止位置编号
     *        OutputFile:输出文件指针
     * output:打印输出Ai到Aj的链乘括号化方案
     **/
    if(i == j){
        fprintf(OutputFile,"A[%d]",i);
    }
    else{
        fprintf(OutputFile,"(");
        PrintOptimalParens(s,i,s[i][j],OutputFile);
        PrintOptimalParens(s,s[i][j]+1,j,OutputFile);
        fprintf(OutputFile,")");
    }
    return;
}
int main(int argc,char* argv[]){
    FILE* InputFile = fopen("../input/input.txt","r");
    if(InputFile == NULL){
        printf("FILE INPUT ERROR!\n");
        exit(0);
    }
    FILE* ResultFile = fopen("../output/result.txt","w");
    FILE* TimeFile  =  fopen("../output/time.txt","w");
    int p[31],i;
    long t;
    for(i = 0;i < 31;i++){
        fscanf(InputFile,"%d\n",&p[i]);
    }
    fclose(InputFile);
    struct timeval start,end;
    Result* TempResult = NULL;
    /**********************n = 5  test**************************/
    gettimeofday(&start,NULL);
    TempResult = MatrixChainOrder(p,5);
    gettimeofday(&end,NULL);
    PrintOptimalParens(TempResult->s,1,5,ResultFile);
    fprintf(ResultFile,"\n");
    t = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    fprintf(TimeFile,"n = %d\t,time cost is %ld \tus.\n",5,t);
    free(TempResult->m);
    free(TempResult->s);
    free(TempResult);
    TempResult = NULL;
    /**********************n = 10 test**************************/
    gettimeofday(&start,NULL);
    TempResult = MatrixChainOrder(p,10);
    gettimeofday(&end,NULL);
    PrintOptimalParens(TempResult->s,1,10,ResultFile);
    fprintf(ResultFile,"\n");
    t = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    fprintf(TimeFile,"n = %d\t,time cost is %ld \tus.\n",10,t);
    free(TempResult->m);
    free(TempResult->s);
    free(TempResult);
    TempResult = NULL;
    /**********************n = 20 test**************************/
    gettimeofday(&start,NULL);
    TempResult = MatrixChainOrder(p,20);
    gettimeofday(&end,NULL);
    PrintOptimalParens(TempResult->s,1,20,ResultFile);
    fprintf(ResultFile,"\n");
    t = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    fprintf(TimeFile,"n = %d\t,time cost is %ld \tus.\n",20,t);
    free(TempResult->m);
    free(TempResult->s);
    free(TempResult);
    TempResult = NULL;
    /**********************n = 30 test**************************/
    gettimeofday(&start,NULL);
    TempResult = MatrixChainOrder(p,30);
    gettimeofday(&end,NULL);
    PrintOptimalParens(TempResult->s,1,30,ResultFile);
    fprintf(ResultFile,"\n");
    t = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    fprintf(TimeFile,"n = %d\t,time cost is %ld \tus.\n",30,t);
    free(TempResult->m);
    free(TempResult->s);
    free(TempResult);
    TempResult = NULL;
    fclose(ResultFile);
    fclose(TimeFile);
    return 0;
}