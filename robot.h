#ifndef ROBOT_H
#define ROBOT_H

#include "arena.h"
#define ROBOT_SIZE 30

typedef struct {
    int r_row;
    int r_col;
    Position hometile;
    Position dir;
    int markerCount;
} Robot;

// Movement and rotation functions
void forward(Robot* robot, int** arena); 
void left(Robot* robot);
void right(Robot* robot);

// Marker interactions
int atMarker(Robot* robot, int** arena); 
int canMoveForward(Robot* robot, int** arena, int** visited);
void pickUpMarker(Robot* robot, int** arena, int test);
void dropMarker(Robot* robot, int** arena);
int markerCount(Robot* robot);
int findMarkers(Robot* robot, int** arena, int test);

#endif // ROBOT_H