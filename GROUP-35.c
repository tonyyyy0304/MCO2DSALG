#include<stdio.h>
#include<string.h>
#include<windows.h>
#include "graph.c"
#include "DFS.c"
#include "BFS.c"

#include "bonusGraphWithRenderer.c"
#include "bonusTreeWithRenderer.c"


int main(){

    struct Graph graph;
    struct Queue queue;
    struct Stack stack;

    FILE *fp_input;
    FILE *fp_output;
 
    String100 fileName;
    String100 temp;
    String100 vertexStart;

    //variables for checkers and necessary values/reference
    int vertexCtr = 0;
    int curr = 0;
    int newVertex = 1;
    int validFile = 1;
    int validRoot = 1;

    // inputs
    printf("Input filename: ");
    scanf("%s", fileName);

    fp_input = fopen(fileName, "r");
    fp_output = fopen("TRAVERSAL.txt", "w");

    if (fp_input == NULL){
        validFile = 0;
    }

    if (fp_output == NULL){
        printf("Error accessing file");
    }

    //file checker
    if(validFile == 0){
        printf("%s not found.", fileName);
        return 0;
    }

    //traversal input
    printf("Input start vertex for the traversal: ");
    scanf(" %s", vertexStart);

    //scan the number
    fscanf(fp_input, "%d", &graph.maxVertex);

    initializeGraph(&graph);

    //scans for the vertex and assigns them an index in graph->name[]
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

    validRoot = rootValidity(&graph, vertexStart);
    
    if(validRoot != -1 && validFile){
        //reset file read
        fseek(fp_input, 0, SEEK_SET);

        fscanf(fp_input, "%d", &graph.maxVertex);

        //scanning for the edges
        while(fscanf(fp_input, "%s", temp) != EOF){
            if(strcmp(temp, "-1") != 0 && newVertex){
                newVertex = 0;
                curr = getNameIndex(temp, &graph);
            }

            if(strcmp(temp, "-1") == 0){
                newVertex = 1;
            }

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
        printVertexAndDegree(&graph, fp_output);
        //we first print before sorting, to follow the specs
        sort(&graph);

        //we reset
        fseek(fp_input, 0, SEEK_SET);

        fscanf(fp_input, "%d", &graph.maxVertex);

        initializeGraph(&graph);

        /*scanning for the edges, we do it again after sorting since 
            BFS and DFS relies on sorted names. e.g.alex < brian, when on choosing a path*/
        while(fscanf(fp_input, "%s", temp) != EOF){
            if(strcmp(temp, "-1") != 0 && newVertex){
                newVertex = 0;
                curr = getNameIndex(temp, &graph);
            }

            if(strcmp(temp, "-1") == 0){
                newVertex = 1;
            }

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

        fprintf(fp_output, "\n");
        bfs(&graph, &queue, vertexStart, fp_output);
        fprintf(fp_output, "\n");
        fprintf(fp_output, "\n");
        depthFirstSearch(&stack, &graph, vertexStart, fp_output);
    }
    else if(validRoot == -1)
        printf("Vertex %s not found.", vertexStart);

    fclose(fp_input);
    fclose(fp_output);
}
