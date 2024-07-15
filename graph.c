#include "graph.h"


void initializeGraph(struct Graph* graph){
    for(int i = 0; i < graph->maxVertex; i++){
        for(int j = 0; j < graph->maxVertex; j++){
            graph->matrix[i][j] = 0;
        }
    }
}

void createEdge(int src, int dest, struct Graph* graph){
    graph->matrix[src][dest] = 1;
    graph->matrix[dest][src] = 1;
}

int getVertexDegree(int vertex, struct Graph* graph){
    int deg = 0;
    for(int i = 0; i < graph->maxVertex; i++)
        deg += graph->matrix[vertex][i];

    return deg;
}