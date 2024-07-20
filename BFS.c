#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"
#include "BFS.h"

void initQueue(struct Queue *q, struct Graph *graph){
    q->headIndex = -1;
    q->tailIndex = -1;

    for (int i = 0; i < graph->maxVertex; i++){
        q->Queue[i] = 0;
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

void bfs(struct Graph *graph, struct Queue *queue, char* startingVertex){
    int visitedNodes[100];
    int i, j;

    for (i = 0; i < graph->maxVertex; i++){
        visitedNodes[i] = 0;
    }

    int initialVertex = getNameIndex(startingVertex, graph);

    initQueue(queue, graph);
    enqueue(queue, initialVertex);
    visitedNodes[initialVertex] = 1;

    while (!isEmpty(queue)){
        int iAmHere = dequeue(queue);

        printf("%s ", graph->name[iAmHere]);
        for (i = 0; i < graph->maxVertex; i++){
            if (graph->matrix[iAmHere][i] == 1 && !visitedNodes[i]){ 
                enqueue(queue, i);
                visitedNodes[i] = 1; // toggle as visited 
            }
        }
    }

    for (i = 0; i < graph->maxVertex; i++){ // check vertices that are not yet visited
        if (!visitedNodes[i]){
            initQueue(queue, graph);
            enqueue(queue, i); // enqueue this index
            visitedNodes[i] = 1; // toggle as visited already

            while (!isEmpty(queue)){
                int iAmHere = dequeue(queue);

                printf("%s ", graph->name[iAmHere]); // perform bfs
                for (j = 0; j < graph->maxVertex; j++){
                    if (graph->matrix[iAmHere][j] == 1 && !visitedNodes[j]){
                        enqueue(queue, j);
                        visitedNodes[j] = 1;  
                    }
                }
            }
        }
    }
    
    printf("\n");
}

