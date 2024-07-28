#include "DFS.h"
#include "graph.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// creates a stack
void createStack(struct Stack *stack, struct Graph *graph){

    stack->top = -1;
    stack->max = graph->maxVertex;
     for(int i = 0; i<graph->maxVertex; i++){
        stack->Stack[i] = 0;
     }        
}

// checks if stack is empty
int is_empty(struct Stack *stack){
    return stack->top == -1;
}

// pushes onto the stack
void push(struct Stack *stack, int vertex){
    if (stack->top < (stack->max - 1)){
        stack->Stack[++stack->top] = vertex;
    }
}

// pops from stack
int pop(struct Stack* stack){
    if(is_empty(stack)){
        return -1;
    }
    return stack->Stack[stack->top--];
}

void depthFirstSearch(struct Stack *stack, struct Graph *graph, char *startVertex, FILE* fp) {
    int visited[100] = {0};  // Array containing visited vertices
    int current; 
    int vertexNum; 

    vertexNum = getNameIndex(startVertex, graph); 
    createStack(stack, graph);
    push(stack, vertexNum);

    //Dfs algorithm
    while (!is_empty(stack)) {
        current = pop(stack);
        if (!visited[current]) {
            fprintf(fp, "%s ", graph->name[current]);
            visited[current] = 1;
            for (int i = graph->maxVertex - 1; i >= 0; i--) {
                if (graph->matrix[current][i] == 1 && !visited[i]) {
                    push(stack, i);
                }
            }
        }
    }
}
