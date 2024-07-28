#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
#include "graph.h"
#include "tracker.h"

#define PI 3.14159265358979323846
#define RADIUS 20

void printNamesInCircle(struct Graph* graph, struct Tracker* tracker, char renderer[][120]) {
    int x, y;
    double angle, angleBetween;

    angleBetween = 2 * PI / graph->maxVertex;
    
    for (int i = 0; i < graph->maxVertex; i++) {
        //SOH CAH, radius is hypotenuse
        angle = i * angleBetween;
        x = (int)(RADIUS * cos(angle)) + RADIUS; 
        y = (int)(RADIUS * sin(angle)) + RADIUS;  

        //print on coordinate, x is multiplied by 2 since width and height are not same size when displayed in terminal
        tracker->x[i]= x*2;
        tracker->y[i] = y+1;
        for(int j = 0; j<strlen(graph->name[i]) + 2 ; j++){
            renderer[tracker->y[i]-1][tracker->x[i] + j] = '=';

        }
       
        renderer[tracker->y[i]][tracker->x[i]] = '|';

        for(int j=1; j<strlen(graph->name[i])+1; j++){
            renderer[tracker->y[i]][tracker->x[i] + j] = graph->name[i][j-1];
        }

        renderer[tracker->y[i]][tracker->x[i] + strlen(graph->name[i]) + 1] = '|';

        for(int j = 0; j<strlen(graph->name[i]) + 2; j++){
            renderer[tracker->y[i]+1][tracker->x[i] + j] = '=';
        }
    }

}

void drawLineGraph(int x1, int y1, int x2, int y2, char renderer[][120]) {
    int xStart, xEnd, xPoint, yPoint, temp;
    float m, b;

    if (x1 == x2) { // Vertical line
        if (y1 > y2) {
            //swap
            temp = y1;
            y1 = y2;
            y2 = temp;
        }
        for (int yVertical = y1; yVertical <= y2; yVertical++) {
            renderer[yVertical][x1] = '|';
        }
    } else if (y1 == y2) { // Horizontal line
        if (x1 > x2) {
            //swap
            temp = x1;
            x1 = x2;
            x2 = temp;
        }
        for (int xHorizontal = x1; xHorizontal <= x2; xHorizontal++) {
            renderer[y1][xHorizontal] = '-';
        }
    }else{
        xStart = (x1 < x2) ? x1 : x2;
        xEnd = (x1 < x2) ? x2 : x1;

        m = (float)(y2 - y1) / (x2 - x1);//slope formula
        b = y1 - m * x1;//derived from slope-intercept formula
    

        for (xPoint = xStart; xPoint <= xEnd; xPoint++) { 
            yPoint = round(m * xPoint + b); //as x progresses, we get the corresponding y using slope intercept
            renderer[yPoint][xPoint] = '-';  
        } 
    }
}


void createGraph(struct Graph* graph, char renderer[][120]){
    struct Tracker coordinate;

    printNamesInCircle(graph, &coordinate, renderer);
    
    for(int i = 0; i < graph->maxVertex; i++){
        for(int j = i; j < graph->maxVertex; j++){
            if(graph->matrix[i][j])
                drawLineGraph(coordinate.x[i], coordinate.y[i], coordinate.x[j], coordinate.y[j], renderer);
            }
    }

    printNamesInCircle(graph, &coordinate, renderer);

}



