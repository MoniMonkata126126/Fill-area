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

