
struct queue{
    int* values;
    int capacity;
    int size;
};

struct queue* init_queue();
int is_full(struct queue* q);
int is_empty(struct queue* q);
void resize(struct queue* q);
void push_back(struct queue* q, int coords);
int pop(struct queue* q);
int is_in_queue(struct queue* q, int coords);
