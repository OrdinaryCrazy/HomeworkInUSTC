#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>
#define GROUPS 5
int FIRSTFINDPOSITION;
int* ComputePrefixFunction(char* P,int m){
    int* Pai = (int*)malloc((m + 1) * sizeof(int));
    Pai[1] = 0;
    int k = 0;  //匹配的模式串指针
    int q;      //被匹配的模式串指针
    for(q = 2;q <= m;q++){
        while(k > 0 && P[k+1] != P[q]){
            k = Pai[k];
        }
        if(P[k+1] == P[q]){
            k++;
        }
        Pai[q] = k;
    }
    return Pai;
}
void KMPMatcher(char* T,char* P,int n,int m){
    int* Pai = ComputePrefixFunction(P,m);
    int q = 0;  //匹配的模式串指针
    int i;      //被匹配的模式串指针
    for(i = 1;i <= n;i++){
        while(q > 0 && P[q + 1] != T[i]){
            q = Pai[q];
        }
        if(P[q + 1] == T[i]){
            q++;
        }
        if(q == m){
            printf("Found at %d\n",i - m);
            if(FIRSTFINDPOSITION == -1) FIRSTFINDPOSITION = i - m;
            q = Pai[q];
        }
    }
    free(Pai);
}
int main(){
    FILE* InputFile = fopen("../../input/input_string.txt","r");
    FILE* OutputFile = fopen("../../output/KMP/output.txt","w");
    int text_size[GROUPS] = {(int)pow(2.0,5.0),(int)pow(2.0,8.0),(int)pow(2.0,11.0),(int)pow(2.0,14.0),(int)pow(2.0,17.0)};
    int pattern_size[GROUPS] = {2,3,4,5,6};
    int i;
    struct timeval start,end;
    for(i = 0;i < GROUPS;i++){
        char* text = (char*)malloc((text_size[i] + 1) * sizeof(char));
        char* pattern = (char*)malloc((pattern_size[i] + 1) * sizeof(char));
        fread(&text[1],sizeof(char),text_size[i],InputFile);
        fgetc(InputFile);
        fread(&pattern[1],sizeof(char),pattern_size[i],InputFile);
        fgetc(InputFile);
        fprintf(OutputFile,"%d %d ",text_size[i],pattern_size[i]);
        FIRSTFINDPOSITION = -1;
        printf("The %dth Search:\n",i + 1);
        gettimeofday(&start,NULL);
        KMPMatcher(text,pattern,text_size[i],pattern_size[i]);
        gettimeofday(&end,NULL);
        fprintf(OutputFile,"%d %ldus\n",FIRSTFINDPOSITION,(end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
        free(text);
        free(pattern);
    }
    fclose(InputFile);
    fclose(OutputFile);
}