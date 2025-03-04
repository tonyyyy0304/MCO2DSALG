#include "graph.h"
#include<conio.h>

//replace garbage with 0
void initializeGraph(struct Graph* graph){
    for(int i = 0; i < graph->maxVertex; i++){
        for(int j = 0; j < graph->maxVertex; j++){
            graph->matrix[i][j] = 0;
        }
    }
}

//add an edge to the matrix
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

//checker if name exists
int nameExists(char* name, struct Graph* graph){
    for(int i = 0; i < graph->maxVertex; i++){
        if(strcasecmp(name, graph->name[i]) == 0)
            return 1;
    }
    return 0;
}

//insertion to the list of names
void insertName(char* name, int ctr, struct Graph* graph){
    strcpy(graph->name[ctr], name);
}

int getNameIndex(char* name, struct Graph* graph){
     for(int i = 0; i < graph->maxVertex; i++){
         if(strcasecmp(name, graph->name[i]) == 0)
            return i;
     }

     return -1;

}

//output for number of degrees of each vertex
void printVertexAndDegree(struct Graph* graph, FILE* output){
    for(int i = 0; i < graph->maxVertex; i++){
        fprintf(output, "%s    %d\n", graph->name[i], getVertexDegree(i, graph));
    }
}

//root checker
int rootValidity(struct Graph* graph, char* root){
    int ret = -1;
    for(int i = 0; i<graph->maxVertex; i++){
        if(strcasecmp(graph->name[i], root) == 0)
            ret = 1;
    }
    return ret;
}

//sort for the traversals
void sort(struct Graph* graph){
    int i, j;
    String100 temp;

	//selection sort
    for (i = 0; i < graph->maxVertex - 1; i++)
    {
        for (j = i + 1; j < graph->maxVertex; j++)
        {
            if (strcasecmp(graph->name[j], graph->name[i]) < 0)
            {
                strcpy(temp, graph->name[i]);
                strcpy(graph->name[i], graph->name[j]);
                strcpy(graph->name[j], temp);
            }
        }
    }
}