#include<stdio.h>
#include<string.h>
#include "graph.h"
#include "helperFuncs.c"


int main(){

    struct Graph graph;

    FILE *fp_input;
    FILE *fp_output;
 
    String100 fileName;
    String100 temp;

    int vertexCtr = 0;
    int curr = 0;
    int newVertex = 1;

    printf("Input filename: ");
    scanf("%s", fileName);

    fp_input = fopen(fileName, "r");
    fp_output = fopen("TRAVERSAL.txt", "w");

    if (fp_input == NULL){
        printf("Error accessing file");
        return 0;
    }

    if (fp_output == NULL){
        printf("Error accessing file");
        return 0;
    }

    fscanf(fp_input, "%d", &graph.maxVertex);

    initializeGraph(&graph);

//scans for the vertex and assigns them an Index/ID in graph->name[]
    while(fscanf(fp_input, "%s", temp) != EOF){
        if(strcmp(temp, "-1") != 0 && !nameExists(temp, &graph) && newVertex){
            insertName(temp, vertexCtr, &graph);
            vertexCtr++;
            newVertex = 0;
        }
        
        if(strcmp(temp, "-1") == 0){
            newVertex = 1;
        }
    }
    fseek(fp_input, 0, SEEK_SET);

    fscanf(fp_input, "%d", &graph.maxVertex);

//scanning for the edges
    while(fscanf(fp_input, "%s", temp) != EOF){
        if(strcmp(temp, "-1") != 0 && getNameIndex(temp, &graph) != curr){
            createEdge(curr, getNameIndex(temp, &graph), &graph);
        }

        if(strcmp(temp, "-1") != 0 && getNameIndex(temp, &graph) != curr){
            createEdge(curr, getNameIndex(temp, &graph), &graph);
        }

        if(strcmp(temp, "-1") == 0){
            curr++;
        }
    }

    printVertexAndDegree(&graph);

    fclose(fp_input);
    fclose(fp_output);
}