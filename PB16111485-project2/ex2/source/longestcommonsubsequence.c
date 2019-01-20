#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
struct result{
    int** cost;
    int** dirc;
};
typedef struct result Result;
Result* FindLCS(char* X,char* Y,int XLength,int YLength){
    /**
     * function:查找出一个最长公共子序列并记录对应的子序列长度矩阵和子序列构造辅助矩阵
     * input: X，Y：求解的两个字符串
     *        XLength，YLength：字符串对应长度
     * output:FinalResult->cost：子序列长度矩阵
     *        FinalResult->dirc：子序列构造辅助矩阵，3代表对角线，2代表向上，1代表向左
     **/
    int i,j;
    Result* FinalResult = (Result*)malloc(sizeof(Result));
    FinalResult->cost = (int**)malloc((XLength + 1) * sizeof(int*));
    FinalResult->dirc = (int**)malloc((XLength + 1) * sizeof(int*));
    for(i = 0;i <= XLength;i++){
        FinalResult->cost[i] = (int*)malloc((YLength + 1) * sizeof(int));
        FinalResult->dirc[i] = (int*)malloc((YLength + 1) * sizeof(int));
    }
    for(i = 0;i <= XLength;i++){
        FinalResult->cost[i][0] = 0;
    }
    for(i = 0;i <= YLength;i++){
        FinalResult->cost[0][i] = 0;
    }
    for(i = 1;i <= XLength;i++){
        for(j = 1;j <= YLength;j++){
            if(X[i] == Y[j]){
                FinalResult->cost[i][j] = FinalResult->cost[i-1][j-1] + 1;
                FinalResult->dirc[i][j] = 3;
            }
            else{
                if(FinalResult->cost[i-1][j] >= FinalResult->cost[i][j-1]){
                    FinalResult->cost[i][j] = FinalResult->cost[i-1][j];
                    FinalResult->dirc[i][j] = 2;
                }
                else{
                    FinalResult->cost[i][j] = FinalResult->cost[i][j-1];
                    FinalResult->dirc[i][j] = 1;
                }
            }
        }
    }
    return FinalResult;
}
void PrintLCS(int** b,char* X,int i,int j,FILE* OutputFile){
    /**
     * function:打印 X[1,...,i] 与 Y[1,...,j] 的最长公共子序列
     * input:b:子序列构造辅助矩阵，3代表对角线，2代表向上，1代表向左
     *       i,j:所求公共子序列的长度
     *       OutputFile：输出文件指针
     * output:打印 X[1,...,i] 与 Y[1,...,j] 的最长公共子序列
     **/
    if(i == 0 || j == 0){
        return;
    }
    if(b[i][j] == 3){
        PrintLCS(b,X,i-1,j-1,OutputFile);
        fprintf(OutputFile,"%c",X[i]);
    }
    else{
        if(b[i][j] == 2){
            PrintLCS(b,X,i-1,j,OutputFile);
        }
        else{
            PrintLCS(b,X,i,j-1,OutputFile);
        }
    }
}
int main(int argc,char* argv[]){
    FILE* InputFileA = fopen("../input/inputA.txt","r");
    FILE* InputFileB = fopen("../input/inputB.txt","r");
    if(InputFileA == NULL || InputFileB == NULL){
        printf("FILE INPUT ERROR!\n");
        exit(0);
    }
    FILE* ResultFile = fopen("../output/result.txt","w");
    FILE* TimeFile  =  fopen("../output/time.txt","w");
    struct timeval start,end;
    Result* TempResult = NULL;
    char X[100],Y[100];
    long t;
    /***************************** (15,10) test ********************************************/
    fscanf(InputFileA,"%s\n",&X[1]);
    fscanf(InputFileA,"%s\n",&Y[1]);
    gettimeofday(&start,NULL);
    TempResult = FindLCS(X,Y,15,10);
    gettimeofday(&end,NULL);
    PrintLCS(TempResult->dirc,X,15,10,ResultFile);
    fprintf(ResultFile,"\n");
    t = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    fprintf(TimeFile,"size = (15,10),time cost is %ld \tus.\n",t);
    free(TempResult->cost);
    free(TempResult->dirc);
    free(TempResult);
    TempResult = NULL;
    /***************************** (15,20) test ********************************************/
    fscanf(InputFileA,"%s\n",&X[1]);
    fscanf(InputFileA,"%s\n",&Y[1]);
    gettimeofday(&start,NULL);
    TempResult = FindLCS(X,Y,15,20);
    gettimeofday(&end,NULL);
    PrintLCS(TempResult->dirc,X,15,20,ResultFile);
    fprintf(ResultFile,"\n");
    t = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    fprintf(TimeFile,"size = (15,20),time cost is %ld \tus.\n",t);
    free(TempResult->cost);
    free(TempResult->dirc);
    free(TempResult);
    TempResult = NULL;
    /***************************** (15,30) test ********************************************/
    fscanf(InputFileA,"%s\n",&X[1]);
    fscanf(InputFileA,"%s\n",&Y[1]);
    gettimeofday(&start,NULL);
    TempResult = FindLCS(X,Y,15,30);
    gettimeofday(&end,NULL);
    PrintLCS(TempResult->dirc,X,15,30,ResultFile);
    fprintf(ResultFile,"\n");
    t = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    fprintf(TimeFile,"size = (15,30),time cost is %ld \tus.\n",t);
    free(TempResult->cost);
    free(TempResult->dirc);
    free(TempResult);
    TempResult = NULL;
    /***************************** (15,40) test ********************************************/
    fscanf(InputFileA,"%s\n",&X[1]);
    fscanf(InputFileA,"%s\n",&Y[1]);
    gettimeofday(&start,NULL);
    TempResult = FindLCS(X,Y,15,40);
    gettimeofday(&end,NULL);
    PrintLCS(TempResult->dirc,X,15,40,ResultFile);
    fprintf(ResultFile,"\n");
    t = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    fprintf(TimeFile,"size = (15,40),time cost is %ld \tus.\n",t);
    free(TempResult->cost);
    free(TempResult->dirc);
    free(TempResult);
    TempResult = NULL;
    /***************************** (15,50) test ********************************************/
    fscanf(InputFileA,"%s\n",&X[1]);
    fscanf(InputFileA,"%s\n",&Y[1]);
    gettimeofday(&start,NULL);
    TempResult = FindLCS(X,Y,15,50);
    gettimeofday(&end,NULL);
    PrintLCS(TempResult->dirc,X,15,50,ResultFile);
    fprintf(ResultFile,"\n");
    t = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    fprintf(TimeFile,"size = (15,50),time cost is %ld \tus.\n",t);
    free(TempResult->cost);
    free(TempResult->dirc);
    free(TempResult);
    TempResult = NULL;
    /***************************** (15,60) test ********************************************/
    fscanf(InputFileA,"%s\n",&X[1]);
    fscanf(InputFileA,"%s\n",&Y[1]);
    gettimeofday(&start,NULL);
    TempResult = FindLCS(X,Y,15,60);
    gettimeofday(&end,NULL);
    PrintLCS(TempResult->dirc,X,15,60,ResultFile);
    fprintf(ResultFile,"\n");
    t = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    fprintf(TimeFile,"size = (15,60),time cost is %ld \tus.\n",t);
    free(TempResult->cost);
    free(TempResult->dirc);
    free(TempResult);
    TempResult = NULL;
    /***************************** (15,25) test ********************************************/
    fscanf(InputFileB,"%s\n",&X[1]);
    fscanf(InputFileB,"%s\n",&Y[1]);
    gettimeofday(&start,NULL);
    TempResult = FindLCS(X,Y,15,25);
    gettimeofday(&end,NULL);
    PrintLCS(TempResult->dirc,X,15,25,ResultFile);
    fprintf(ResultFile,"\n");
    t = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    fprintf(TimeFile,"size = (15,25),time cost is %ld \tus.\n",t);
    free(TempResult->cost);
    free(TempResult->dirc);
    free(TempResult);
    TempResult = NULL;
    /***************************** (30,25) test ********************************************/
    fscanf(InputFileB,"%s\n",&X[1]);
    fscanf(InputFileB,"%s\n",&Y[1]);
    gettimeofday(&start,NULL);
    TempResult = FindLCS(X,Y,30,25);
    gettimeofday(&end,NULL);
    PrintLCS(TempResult->dirc,X,30,25,ResultFile);
    fprintf(ResultFile,"\n");
    t = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    fprintf(TimeFile,"size = (30,25),time cost is %ld \tus.\n",t);
    free(TempResult->cost);
    free(TempResult->dirc);
    free(TempResult);
    TempResult = NULL;
    /***************************** (45,25) test ********************************************/
    fscanf(InputFileB,"%s\n",&X[1]);
    fscanf(InputFileB,"%s\n",&Y[1]);
    gettimeofday(&start,NULL);
    TempResult = FindLCS(X,Y,45,25);
    gettimeofday(&end,NULL);
    PrintLCS(TempResult->dirc,X,45,25,ResultFile);
    fprintf(ResultFile,"\n");
    t = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    fprintf(TimeFile,"size = (45,25),time cost is %ld \tus.\n",t);
    free(TempResult->cost);
    free(TempResult->dirc);
    free(TempResult);
    TempResult = NULL;
    /***************************** (60,25) test ********************************************/
    fscanf(InputFileB,"%s\n",&X[1]);
    fscanf(InputFileB,"%s\n",&Y[1]);
    gettimeofday(&start,NULL);
    TempResult = FindLCS(X,Y,60,25);
    gettimeofday(&end,NULL);
    PrintLCS(TempResult->dirc,X,60,25,ResultFile);
    fprintf(ResultFile,"\n");
    t = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    fprintf(TimeFile,"size = (60,25),time cost is %ld \tus.\n",t);
    free(TempResult->cost);
    free(TempResult->dirc);
    free(TempResult);
    TempResult = NULL;
    /***************************** (75,25) test ********************************************/
    fscanf(InputFileB,"%s\n",&X[1]);
    fscanf(InputFileB,"%s\n",&Y[1]);
    gettimeofday(&start,NULL);
    TempResult = FindLCS(X,Y,75,25);
    gettimeofday(&end,NULL);
    PrintLCS(TempResult->dirc,X,75,25,ResultFile);
    fprintf(ResultFile,"\n");
    t = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    fprintf(TimeFile,"size = (75,25),time cost is %ld \tus.\n",t);
    free(TempResult->cost);
    free(TempResult->dirc);
    free(TempResult);
    TempResult = NULL;
    /***************************** (90,25) test ********************************************/
    fscanf(InputFileB,"%s\n",&X[1]);
    fscanf(InputFileB,"%s\n",&Y[1]);
    gettimeofday(&start,NULL);
    TempResult = FindLCS(X,Y,90,25);
    gettimeofday(&end,NULL);
    PrintLCS(TempResult->dirc,X,90,25,ResultFile);
    fprintf(ResultFile,"\n");
    t = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    fprintf(TimeFile,"size = (90,25),time cost is %ld \tus.\n",t);
    free(TempResult->cost);
    free(TempResult->dirc);
    free(TempResult);
    TempResult = NULL;
    fclose(InputFileA);
    fclose(InputFileB);
    fclose(ResultFile);
    fclose(TimeFile);
    return 0;
}