#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "tracker.h"
#include "BFS.h"

#define USED_SPACE 42

void drawLineTree(int x1, int y1, int x2, int y2, char renderer[][120]) {
    int xPoint, xStart, xEnd, yPoint;
    float m, b;
  

    if (x1 == x2) { // Vertical line
        if (y1 > y2) {
            int temp = y1;
            y1 = y2;
            y2 = temp;
        }
        for (int yVertical = y1; yVertical <= y2; yVertical++) {
           
            renderer[yVertical + USED_SPACE][x1] = '|';
        }
    } else if (y1 == y2) { // Horizontal line
        if (x1 > x2) {
            int temp = x1;
            x1 = x2;
            x2 = temp;
        }
        for (int xHorizontal = x1; xHorizontal <= x2; xHorizontal++) {
            
            renderer[y1 + USED_SPACE][xHorizontal] = '-';
        }
    }else{
        xStart = (x1 < x2) ? x1 : x2;
        xEnd = (x1 < x2) ? x2 : x1;

        m = (float)(y2 - y1) / (x2 - x1);//slope formula
        b = y1 - m * x1;//derived from slope-intercept formula
    

        for (xPoint = xStart; xPoint <= xEnd; xPoint++) { 
            yPoint = round(m * xPoint + b); //as x progresses, we get the corresponding y using slope intercept
           
            renderer[yPoint+USED_SPACE][xPoint] = '-';
        } 
    }
}


void createTree(struct Graph* graph, int root, char renderer[][120]) {
    struct Queue q;
    initQueue(&q, graph);

    struct Tracker tracker;

    int x = 1, y = 1 + USED_SPACE;
    //the level system basically stores the nodes level in the index corresponding to it.
    //in the nodeCtr, the indices are the corresponding levels while the value is the num of nodes
    int nodeCtr[100], level[100], visited[100];

    //since xOffset is 15, the bonus implementation for trees can displays
    int xOffset = 16, yOffset = 8;

    for(int i= 0; i<graph->maxVertex; i++){
        nodeCtr[i] = 0;
        level[i] = 0;
        visited[i] = 0;
    }
    

    enqueue(&q, root);
    visited[root] = 1;
  
    tracker.x[root] = x;
    tracker.y[root] = y;

    //this is to insert the name of root
    renderer[y][x] ='[';
     for(int j = 1; j<strlen(graph->name[root]) + 1; j++){
            renderer[y][x + j] = graph->name[root][j-1];
        }
    renderer[y][x+strlen(graph->name[root]) + 1] =']';

    //root node has 0 level
   level[root] = 0;

    //a bfs algo for displaying based on the original bfs.c
    while (!isEmpty(&q)) {
        int current = dequeue(&q);
        
        tracker.y[current] = y + level[current] * yOffset;
       
        for (int i = 0; i < graph->maxVertex; i++) {        
            if (graph->matrix[current][i] && !visited[i]) {
                level[i] = level[current] + 1;//assign levels to node
               
               //updating coordinates
                tracker.y[i] = y + level[i] * yOffset;
                x = 1 + nodeCtr[level[current]] * xOffset;
                tracker.x[i] = x;

                //we use the coordinates of one parent and one child to connect each other
                drawLineTree(tracker.x[current], tracker.y[current] - USED_SPACE+1, tracker.x[i], tracker.y[i] - USED_SPACE-1, renderer);
                
                //this is to insert the name into the renderer, single brackets since this is no longer the root
                renderer[y+level[i] * yOffset][x] ='[';
                for(int j=1; j<strlen(graph->name[i])+1; j++){//limit of 12, more than that will result to overlapping
                        renderer[y+level[i] * yOffset][x + j] = graph->name[i][j-1];
                    }
                renderer[y+level[i] * yOffset][x+strlen(graph->name[i])+1] =']';

               
                enqueue(&q, i);
                visited[i] = 1;
               
                nodeCtr[level[current]]++;
            }
            
        }
        x = 1;//reset x position
        
    }

}