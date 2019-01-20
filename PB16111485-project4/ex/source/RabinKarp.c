#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>
#define GROUPS 5
int FIRSTFINDPOSITION;
void RabinKarpMatcher(char* T,char* P,int n,int m,int d,int q){
    //A-F.6种不同的字符，对应6进制的0-5
    int h = ((int)pow((double)d,(double)(m-1))) % q;
    int p = 0;
    int t = 0;
    int i;
    for(i = 0;i < m;i++){
        p = (d * p + (P[i] - 'A')) % q;
        t = (d * t + (T[i] - 'A')) % q;
    }
    for(i = 0;i <= n-m;i++){
        if(p == t){
            if(memcmp(P,&T[i],m) == 0){
                printf("Found at %d\n",i);
                if(FIRSTFINDPOSITION == -1) FIRSTFINDPOSITION = i;
            }
        }
        if(i < n-m){
            t = (d*(t - (T[i] - 'A')*h) + (T[i + m] - 'A')) % q;
            if(t < 0) t += q;
        }
    }
}
int main(){
    FILE* InputFile = fopen("../../input/input_string.txt","r");
    FILE* OutputFile = fopen("../../output/RabinKarp/output.txt","w");
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
        //选择素数为37
        FIRSTFINDPOSITION = -1;
        printf("The %dth Search:\n",i + 1);
        gettimeofday(&start,NULL);
        RabinKarpMatcher(text,pattern,text_size[i],pattern_size[i],6,37);
        gettimeofday(&end,NULL);
        fprintf(OutputFile,"%d %ldus\n",FIRSTFINDPOSITION,(end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
        free(text);
        free(pattern);
    }
    fclose(InputFile);
    fclose(OutputFile);
}