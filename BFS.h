#ifndef BFS_H
#define BFS_H

#include<stdio.h>

struct Queue{
    int Queue[100];
    int tailIndex;
    int headIndex; 
};

void initQueue(struct Queue *q, struct Graph *graph);
void enqueue(struct Queue *q, int vertex);
int isEmpty(struct Queue *q);
int dequeue(struct Queue *q);

#endif 