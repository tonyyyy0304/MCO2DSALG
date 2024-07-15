#include<stdio.h>

#define ROW 20
#define COL 20

typedef char String100[100];

struct Graph {
    String100 name[21];

    int matrix[ROW][COL];
    int maxVertex;
};

void initializeGraph(struct Graph* graph);
void createEdge(int src, int dest, struct Graph* graph);
int getVertexDegree(int vertex, struct Graph* graph);

