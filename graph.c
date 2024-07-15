#include "graph.h"
#include<conio.h>


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


int nameExists(char* name, struct Graph* graph){
    for(int i = 0; i < graph->maxVertex; i++){
        if(strcmp(name, graph->name[i]) == 0)
            return 1;
    }
    return 0;
}

void insertName(char* name, int ctr, struct Graph* graph){
    strcpy(graph->name[ctr], name);
}

int getNameIndex(char* name, struct Graph* graph){
     for(int i = 0; i < graph->maxVertex; i++){
         if(strcmp(name, graph->name[i]) == 0)
            return i;
     }

     return -1;

}

void printVertexAndDegree(struct Graph* graph, FILE* output){
    for(int i = 0; i < graph->maxVertex; i++){
        fprintf(output, "%s    %d\n", graph->name[i], getVertexDegree(i, graph));
    }
}