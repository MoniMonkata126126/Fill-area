#include <stdio.h>
#include <stdlib.h>

struct pixels{
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

int main(int argc, char** argv){
    FILE* fp;
    fp = fopen(argv[1], "r");
    if(fp == NULL){
        printf("Error!");
        exit(1);
    }
    fclose(fp);
    return 0;
}