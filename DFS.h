#ifndef DFS_H
#define DFS_H

#include<stdio.h>

struct Stack{
    int Stack[100];
    int top;
    int max; 
};

void createStack(struct Stack *stack, struct Graph *graph);
int is_empty(struct Stack *stack);
void push(struct Stack *stack, int vertex);
int pop(struct Stack* stack);
void depthFirstSearch(struct Stack *stack, struct Graph *graph, char *startVertex, FILE* fp);

#endif