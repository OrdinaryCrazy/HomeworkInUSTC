#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>
#define GROUPS 5
#define ASIZE 6
int FIRSTFINDPOSITION;
int* BadCharacterCompute(char* P,int m){
    int* BC = (int*)malloc(ASIZE * sizeof(int));
    int i;
    for(i = 0;i < ASIZE;i++){
        BC[i] = m;
    }
    for(i = 0;i < m-1;i++){
        BC[P[i] - 'A'] = m - 1 - i;
    }
    return BC;
}
void BMHMatcher(char* T,char* P,int n,int m){
    int* BC = BadCharacterCompute(P,m);
    int j = 0;
    while(j <= n - m){
        if(P[m - 1] == T[j + m - 1] && memcmp(P,&T[j],m) == 0){
            printf("Found at %d\n",j);
            if(FIRSTFINDPOSITION == -1) FIRSTFINDPOSITION = j;
        }
        j += BC[T[j + m - 1] - 'A'];
    }  
    free(BC);
}
int main(){
    FILE* InputFile = fopen("../../input/input_string.txt","r");
    FILE* OutputFile = fopen("../../output/BMH/output.txt","w");
    int text_size[GROUPS] = {(int)pow(2.0,5.0),(int)pow(2.0,8.0),(int)pow(2.0,11.0),(int)pow(2.0,14.0),(int)pow(2.0,17.0)};
    int pattern_size[GROUPS] = {2,3,4,5,6};
    int i;
    struct timeval start,end;
    for(i = 0;i < GROUPS;i++){
        char* text = (char*)malloc(text_size[i] * sizeof(char));
        char* pattern = (char*)malloc(pattern_size[i] * sizeof(char));
        fread(text,sizeof(char),text_size[i],InputFile);
        fgetc(InputFile);
        fread(pattern,sizeof(char),pattern_size[i],InputFile);
        fgetc(InputFile);
        fprintf(OutputFile,"%d %d ",text_size[i],pattern_size[i]);
        FIRSTFINDPOSITION = -1;
        printf("The %dth Search:\n",i + 1);
        gettimeofday(&start,NULL);
        BMHMatcher(text,pattern,text_size[i],pattern_size[i]);
        gettimeofday(&end,NULL);
        fprintf(OutputFile,"%d %ldus\n",FIRSTFINDPOSITION,(end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
        free(text);
        free(pattern);
    }
    fclose(InputFile);
    fclose(OutputFile);
}