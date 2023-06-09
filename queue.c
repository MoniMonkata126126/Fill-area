#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct queue* init_queue(){
    struct queue* new_queue = malloc(sizeof(struct queue));
    new_queue->capacity = 2;
    new_queue->size = 0;
    new_queue->values = malloc(sizeof(int)*new_queue->capacity);
    return new_queue;
}

int is_full(struct queue* q){
    if(q->size == q->capacity)
        return 1;
    return 0;
}

int is_empty(struct queue* q){
    if(q->size == 0)
        return 1;
    return 0;
}

void resize(struct queue* q){
    q->capacity *= 2;
    q->values = realloc(q->values, sizeof(int)*q->capacity);
}

void push_back(struct queue* q, int coords){
    if(q == NULL){
        q = init_queue();   
    }
    if(is_full(q)){
        resize(q);
    }
    q->values[q->size++] = coords;
}

int pop(struct queue* q){
    if(q == NULL){
        return -1;
    }
    if(is_empty(q)){
        return -1;
    }
    if(q->size == 1){
        q->size--;
        return q->values[0];
    }

    int elem_to_pop = q->values[0];

    for(int i = 0; i < q->size-1; i++){
        q->values[i] = q->values[i+1];
    }
    q->size--;

    return elem_to_pop;
}

int is_in_queue(struct queue* q, int coords){
    if(q == NULL){
        return 0;
    }
    if(is_empty(q)){
        return 0;
    }
    for(int i = 0; i < q->size; i++){
        if(q->values[i] == coords){
            return 1;
        }
    }
    return 0;
}
