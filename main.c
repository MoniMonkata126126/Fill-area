#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct pixel{
    unsigned char R;
    unsigned char G;
    unsigned char B;
    int is_visited;
};


struct pixel** fill_area(struct pixel** img, int row, int column, int last_row, int last_column){
    if(img == NULL){
        printf("No image!");
        return 0;
    }

    int curr_row, curr_column;

    struct queue* q = init_queue();
    push_back(q, (row<<16|column));

    while(q->size != 0){
        

        curr_row = pop(q);
        curr_column = curr_row & 32769;
        curr_row = curr_row >> 16;
        img[curr_row][curr_column].is_visited = 1;


        for(int i = curr_row - 1,  j = curr_column - 1; i < 3; i++){
            if(j < 0)
                break;
            if(i < 0 || i > last_row)
                continue;
            
            if((img[i][j].is_visited == 0) && 
                (((img[i][j].R + img[i][j].G + img[i][j].B)/3 == 
                (img[row][column].R + img[row][column].G + img[row][column].B)/3) ||
                ((img[i][j].R + img[i][j].G + img[i][j].B)/3 == 
                (img[row][column].R + img[row][column].G + img[row][column].B)/3) + 1 ||
                ((img[i][j].R + img[i][j].G + img[i][j].B)/3 == 
                (img[row][column].R + img[row][column].G + img[row][column].B)/3) - 1)){
                    push_back(q, (i<<16|j));
                    img[i][j].R = 0; 
                    img[i][j].G = 0; 
                    img[i][j].B = 0;
            }
        }

        for(int i = curr_row + 1,  j = curr_column + 1; i < 3; i--){
            if(j > last_column)
                break;
            if(i < 0 || i > last_row)
                continue;
            
            if((img[i][j].is_visited == 0) && 
                (((img[i][j].R + img[i][j].G + img[i][j].B)/3 == 
                (img[row][column].R + img[row][column].G + img[row][column].B)/3) ||
                ((img[i][j].R + img[i][j].G + img[i][j].B)/3 == 
                (img[row][column].R + img[row][column].G + img[row][column].B)/3) + 1 ||
                ((img[i][j].R + img[i][j].G + img[i][j].B)/3 == 
                (img[row][column].R + img[row][column].G + img[row][column].B)/3) - 1)){
                    push_back(q, (i<<16|j));
                    img[i][j].R = 0; 
                    img[i][j].G = 0; 
                    img[i][j].B = 0;
            }
        }

        if(curr_row - 1 >= 0){
            if((img[curr_row-1][curr_column].is_visited == 0) && 
                (((img[curr_row-1][curr_column].R + img[curr_row-1][curr_column].G + img[curr_row-1][curr_column].B)/3 == 
                (img[row][column].R + img[row][column].G + img[row][column].B)/3) ||
                ((img[curr_row-1][curr_column].R + img[curr_row-1][curr_column].G + img[curr_row-1][curr_column].B)/3 == 
                (img[row][column].R + img[row][column].G + img[row][column].B)/3) + 1 ||
                ((img[curr_row-1][curr_column].R + img[curr_row-1][curr_column].G + img[curr_row-1][curr_column].B)/3 == 
                (img[row][column].R + img[row][column].G + img[row][column].B)/3) - 1)){
                    push_back(q, (curr_row-1<<16|curr_column));
                    img[curr_row-1][curr_column].R = 0; 
                    img[curr_row-1][curr_column].G = 0; 
                    img[curr_row-1][curr_column].B = 0;
            }
        }

        if(curr_row + 1 >= 0){
            if((img[curr_row+1][curr_column].is_visited == 0) && 
                (((img[curr_row+1][curr_column].R + img[curr_row+1][curr_column].G + img[curr_row+1][curr_column].B)/3 == 
                (img[row][column].R + img[row][column].G + img[row][column].B)/3) ||
                ((img[curr_row+1][curr_column].R + img[curr_row+1][curr_column].G + img[curr_row+1][curr_column].B)/3 == 
                (img[row][column].R + img[row][column].G + img[row][column].B)/3) + 1 ||
                ((img[curr_row+1][curr_column].R + img[curr_row+1][curr_column].G + img[curr_row+1][curr_column].B)/3 == 
                (img[row][column].R + img[row][column].G + img[row][column].B)/3) - 1)){
                    push_back(q, (curr_row+1<<16|curr_column));
                    img[curr_row+1][curr_column].R = 0; 
                    img[curr_row+1][curr_column].G = 0; 
                    img[curr_row+1][curr_column].B = 0;
            }
        }

    }
    free(q->values);
    free(q);
    return img;
}


int main(){

    //This main is made for testing purposes
    int matrix[4][12] = {{1, 2, 3, 234, 243, 255, 2, 35, 64, 255, 255, 255},
                {1, 2, 3, 234, 243, 255, 2, 35, 64, 255, 255, 255},
                {1, 2, 3, 234, 243, 255, 2, 35, 64, 255, 255, 255},
                {1, 2, 3, 234, 243, 255, 2, 35, 64, 255, 255, 255}};

    struct pixel** img = (struct pixel**)malloc(sizeof(struct pixel*)*4);
    for(int i = 0; i < 4; i++){
        img[i] = (struct pixel*)malloc(sizeof(struct pixel)*4);
    }

    for(int i = 0; i < 4; i++){
        for(int j = 0, k = 0; j < 4; j++){
            img[i][j].R = matrix[i][k++];
            img[i][j].G = matrix[i][k++];
            img[i][j].B = matrix[i][k++];
            img[i][j].is_visited = 0;
        }
    }

    for(int i = 0; i < 4; i++){
        for(int j = 0, k = 0; j < 4; j++){
            printf("%d:",img[i][j].R);
            printf("%d:",img[i][j].G);
            printf("%d ",img[i][j].B);
        }
        printf("\n");
    }

    img = fill_area(img, 2, 3, 4, 4);

    for(int i = 0; i < 4; i++){
        for(int j = 0, k = 0; j < 4; j++){
            printf("%d:",img[i][j].R);
            printf("%d:",img[i][j].G);
            printf("%d ",img[i][j].B);
        }
        printf("\n");
    }

    return 0;
}