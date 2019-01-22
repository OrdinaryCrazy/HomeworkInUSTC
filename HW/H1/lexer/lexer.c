#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
	int i, j;
	for(i = 1;i < argc;i++){
		int len = strlen(argv[i]);
		for(j = 0;j < len;j++){
			if(argv[i][j] == '=')
				printf("(relop,EQ),start=%d end=%d\n",j,j + 1);
			else if(argv[i][j] == '>'){
				if(argv[i][j + 1] == '=')
					printf("(relop,GE),start=%d end=%d\n",j,(j++) + 2);
				else
					printf("(relop,GT),start=%d end=%d\n",j,j + 1);
			}
			else if(argv[i][j] == '<'){
				if(argv[i][j + 1] == '=')
					printf("(relop,LE),start=%d end=%d\n",j,(j++) + 2);
				else if(argv[i][j + 1] == '>')
					printf("(relop,NE),start=%d end=%d\n",j,(j++) + 2);
				else
					printf("(relop,LT),start=%d end=%d\n",j,j + 1);
			}
		}
	}
	return 0;
}
