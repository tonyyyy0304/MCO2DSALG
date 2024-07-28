#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"
#include "BFS.h"

void initQueue(struct Queue *q, struct Graph *graph){
    q->headIndex = -1;
    q->tailIndex = -1;

    for (int i = 0; i < graph->maxVertex; i++){
        q->Queue[i] = -1;
    }
}

int isEmpty(struct Queue *q){
    return q->headIndex == -1;
}

void enqueue(struct Queue *q, int vertex){
    
    if (q->tailIndex == 99){
        printf("Full");
    }else{
        if (q->headIndex == -1){
            q->headIndex = 0;
        }

        q->tailIndex++;
        q->Queue[q->tailIndex] = vertex;

    }
    
}

int dequeue(struct Queue *q){
    int vertex; 

    if (q->tailIndex == -1){
        return -1;
    }else{ 
        vertex = q->Queue[q->headIndex];
        q->headIndex++;    

        if (q->headIndex > q->tailIndex){
            q->headIndex = -1;
            q->tailIndex = -1;
        }

        return vertex;    
    }
}

void bfs(struct Graph *graph, struct Queue *queue, char* startingVertex, FILE* fp){
    int visitedNodes[100];
    int i;

    for (i = 0; i < graph->maxVertex; i++){
        visitedNodes[i] = 0;
    }

    int initialVertex = getNameIndex(startingVertex, graph);

    initQueue(queue, graph);
    enqueue(queue, initialVertex);
    visitedNodes[initialVertex] = 1;

    while (!isEmpty(queue)){
        int iAmHere = dequeue(queue);

        fprintf(fp, "%s ", graph->name[iAmHere]);
        for (i = 0; i < graph->maxVertex; i++){
            if (graph->matrix[iAmHere][i] == 1 && !visitedNodes[i]){ 
                enqueue(queue, i);
                visitedNodes[i] = 1; // toggle as visited 
            }
        }
    }

    
    printf("\n");
}

