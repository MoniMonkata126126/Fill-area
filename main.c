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


int main(int argc, char** argv){

    int last_row, last_column, row, column;
    FILE* fp;
    fp = fopen(argv[2], "r");

    fscanf(fp, "%d, %c, %d", last_row, NULL, last_column);

    struct pixel** img = (struct pixel**)malloc(sizeof(struct pixel*)*last_row);
    for(int i = 0; i < last_row; i++){
        img[i] = (struct pixel*)malloc(sizeof(struct pixel)*last_column);
    }

    for(int i = 0; i < last_row; i++){
        for(int j = 0; j < last_column; j++){
            fscanf(fp, "%u", img[i][j].R);
            fscanf(fp, "%c", NULL);
            fscanf(fp, "%u", img[i][j].G );
            fscanf(fp, "%c", NULL);
            fscanf(fp, "%u", img[i][j].B);
            img[i][j].is_visited = 0;
        }
    }

    fclose(fp);

    printf("Give row of pixel: ");
    scanf("%d", &row);
    printf("Give column of pixel: ");
    scanf("%d", &column);

    img = fill_area(img, row, column, last_row, last_column);

    FILE* ft;
    ft = fopen(argv[2], "w");

    fprintf(ft, "%d, %c, %d", last_row, ":", last_column);

    for(int i = 0; i < last_row; i++){
        for(int j = 0; j < last_column; j++){
            fprintf(fp, "%u", img[i][j].R);
            fprintf(fp, "%c", ":");
            fprintf(fp, "%u", img[i][j].G);
            fprintf(fp, "%c", ":");
            fprintf(fp, "%u", img[i][j].B);
            fprintf(fp, "%c", 32);
        }
        fprintf(ft, "\n");
    }

    fclose(ft);

    return 0;
}