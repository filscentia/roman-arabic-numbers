#include <stdio.h>

int main(int i, char** argv){
    printf("Hello World %d %s\n",i,argv[1]);

    if (i=3) {
        if (strcmp(argv[1],"--file")){
            printf("File %s",argv[2]);
        }
    }
    return 0;
}





