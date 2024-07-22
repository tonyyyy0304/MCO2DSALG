#include "graph.h"
#include "BFS.h"

void createGraphDot(char* fileName, struct Graph* graph) {
    FILE *fp = fopen(fileName, "w");
    if (fp == NULL) {
        return;
    }
    fprintf(fp, "graph X {\n");
    for(int i=0; i<graph->maxVertex; i++){
        for(int j=i; j<graph->maxVertex; j++){
            if(graph->matrix[i][j])
            fprintf(fp, "    %s -- %s;\n", graph->name[i], graph->name[j]);
            }
    }

    fprintf(fp, "}\n");
    fclose(fp);
}

int getRootNodeIndex(struct Graph* graph, char* root){
    int rootIndex = -1;
     for (int i = 0; i < graph->maxVertex; i++) {
        if (strcmp(graph->name[i], root) == 0) {
            rootIndex = i;
        }
    }
    return rootIndex;
}

void createTreeDot(char* fileName, struct Graph* graph, char* root) {
    struct Queue q;
    initQueue(&q, graph);
    FILE *fp = fopen(fileName, "w");
    if (fp == NULL) {
        fprintf(fp, "Error: could not open file %s for writing\n", fileName);
    }

    int visited[100] = {0};
   
    int rootIndex = -1;
    int validRoot = 1;

    rootIndex = getRootNodeIndex(graph, root);

    if (rootIndex == -1) {
        fprintf(fp, "Vertex %s not found.\n", root);
        validRoot = 0;
    }
    if(validRoot){

        enqueue(&q, rootIndex);
        visited[rootIndex] = 1;

        fprintf(fp, "graph Tree {\n");

        while (!isEmpty(&q)) {
            int current = dequeue(&q);
            for (int i = 0; i < graph->maxVertex; i++) {
                if (graph->matrix[current][i] && !visited[i]) {
                    fprintf(fp, "    %s -- %s;\n", graph->name[current], graph->name[i]);
                    enqueue(&q, i);
                    visited[i] = 1;
                }
            }
        }
        fprintf(fp, "}\n");
    }
    
    fclose(fp);
}
