#include<conio.h>
#include<string.h>
#include "graph.h"

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

void printVertexAndDegree(struct Graph* graph){
    for(int i = 0; i < graph->maxVertex; i++){
        printf("%s    %d\n", graph->name[i], getVertexDegree(i, graph));
    }
    getch();
}