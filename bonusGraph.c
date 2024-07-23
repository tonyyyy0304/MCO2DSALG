#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
#include "graph.h"

#define PI 3.14159265358979323846
#define RADIUS 15

struct Tracker{
    int x[100];
    int y[100];
};

void move_cursor(int x, int y) {
    printf("\033[%d;%dH", y, x);//ANSI escape sequence, something i used in ccprog2
}


void printNamesInCircle(struct Graph* graph, struct Tracker* tracker, FILE* fp_output) {
    int x, y;
    double angle, angleBetween;

    angleBetween = 2 * PI / graph->maxVertex;
    
    for (int i = 0; i < graph->maxVertex; i++) {
        //SOH CAH, radius is hypotenuse
        angle = i * angleBetween;
        x = (int)(RADIUS * cos(angle)) + RADIUS; 
        y = (int)(RADIUS * sin(angle)) + RADIUS;  

        //print on coordinate, x is multiplied by 2 since width and height are not same size when displayed in terminal
        move_cursor(x*2, y);
        tracker->x[i]= x*2;
        tracker->y[i] = y+1;
        for(int j = 0; j<strlen(graph->name[i])*1.4; j++){
            printf("=");
        }
        move_cursor(x*2, y+1);
        
        printf("|%s|", graph->name[i]);

        move_cursor(x*2, y+2);
        for(int j = 0; j<strlen(graph->name[i])*1.4; j++){
            printf("=");
        }
        
        fprintf(fp_output, "%s", graph->name[i]);
    }

    move_cursor(0, RADIUS * 2 + 1);//moves cursor at the bottom of circle, kinda like newline
}

void drawLine(int x1, int y1, int x2, int y2, FILE* fp_output) {
    int xPoint, xStart, xEnd, yPoint;
    float m, b;

    xStart = (x1 < x2) ? x1 : x2;
    xEnd = (x1 < x2) ? x2 : x1;

    m = (float)(y2 - y1) / (x2 - x1);//slope formula
    b = y1 - m * x1;//derived from slope-intercept formula

    for (xPoint = xStart; xPoint <= xEnd; xPoint++) { 
        yPoint = round(m * xPoint + b); //as x progresses, we get the corresponding y using slope intercept
        move_cursor(xPoint, yPoint);
        fprintf(fp_output, "-");
        printf("-");
    } 
}


void createGraph(struct Graph* graph){
    struct Tracker coordinate;

    FILE* fp_output = fopen("bonus.txt", "w");

    printNamesInCircle(graph, &coordinate, fp_output);
    
    for(int i = 0; i < graph->maxVertex; i++){
        for(int j = i; j < graph->maxVertex; j++){
            if(graph->matrix[i][j])
                drawLine(coordinate.x[i], coordinate.y[i], coordinate.x[j], coordinate.y[j], fp_output);
            }
    }

    printNamesInCircle(graph, &coordinate, fp_output);

}



