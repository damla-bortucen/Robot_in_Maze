#include "graphics.h"
#include "robot.h"
#include "arena.h"
#include "display.h"
#include <stdlib.h>


void forward(Robot* robot, int** arena) {
    robot->r_row += robot->dir.row;
    robot->r_col += robot->dir.col;
}


void left(Robot* robot) {
    // Turning (x,y) vector left is (-y,x)
    int prev_y = robot->dir.col;
    robot->dir.col = robot->dir.row;
    robot->dir.row = -prev_y;
} 


void right(Robot* robot) {
    // Turning (x,y) vector right is (y, -x)
    int prev_y= robot->dir.col;
    robot->dir.col = -robot->dir.row;
    robot->dir.row = prev_y;
}


int atMarker(Robot* robot, int** arena) {
    return (arena[robot->r_row][robot->r_col] == 2);
}


// Checks if next tile is free and has not been visited before
int canMoveForward(Robot* robot, int** arena, int** visited) {
    int next_row = robot->r_row + robot->dir.row;
    int next_col = robot->r_col + robot->dir.col;

    return !((arena[next_row][next_col] == 1) || 
    (visited[next_row][next_col] == 1) || 
    (arena[next_row][next_col] == 3));
}


void pickUpMarker(Robot* robot, int** arena, int test) {
    if (arena[robot->r_row][robot->r_col] == 2) {
        robot->markerCount++;
        arena[robot->r_row][robot->r_col] = 0;        
    }
}


void dropMarker(Robot* robot, int** arena) {
    if (robot->markerCount != 0) {
        arena[robot->r_row][robot->r_col] = 2;
        robot->markerCount--;
    }
}


int markerCount(Robot* robot) {
    return robot->markerCount;
}


int findMarkers(Robot* robot, int** arena, int test) {
    int top_of_stack = -1; // Stack pointer for backtracking (-1 means empty)
    int all_tiles_visited = 0; // Flag to indicate if all reachable tiles are visited

    // Initialize a 2D array to keep track of visited tiles - replicates maze
    int** visited = malloc(NUM_ROWS * sizeof(int*));
    for (int i = 0; i < NUM_ROWS; i++) {
        visited[i] = malloc(NUM_COLS * sizeof(int));
        for (int j = 0; j < NUM_COLS; j++) {
            if (i>0 && j>0 && i<NUM_ROWS-1 && j<NUM_COLS-1) {
            visited[i][j] = 0;
            } else {
                visited[i][j] = 1;
            }
        }
    }
    
    //A stack of directions to keep track of robot trail, so that it can turn back
    Position* robottrail = malloc(NUM_ROWS * NUM_COLS * sizeof(Position));
    visited[robot->r_row][robot->r_col] = 1;

    do {
        if (atMarker(robot,arena)) {
            pickUpMarker(robot, arena, test);
        }

        if (canMoveForward(robot, arena, visited))  { 
            top_of_stack++;
            robottrail[top_of_stack] = (Position){robot->dir.row, robot->dir.col};
        } else { 
            // Try left
            left(robot);
            if (canMoveForward(robot, arena, visited)) {
                top_of_stack++;
                robottrail[top_of_stack] = (Position){robot->dir.row, robot->dir.col};  
            } else {
                // Try right
                right(robot);
                right(robot);
                if (canMoveForward(robot, arena, visited)) {
                    top_of_stack++;
                    robottrail[top_of_stack] = (Position){robot->dir.row, robot->dir.col};   
                }  else {
                    // Turn back
                    right(robot);
                    if (top_of_stack == -1) { 
                        if (!canMoveForward(robot, arena, visited)) {
                            // If cannot move back and stack is empty, robot is back in home tile
                            all_tiles_visited = 1;
                            right(robot); right(robot);
                        }
                        // Unique condition: the stack is empty and only the tile behind robot is not visited or blocked
                        else {
                            top_of_stack++;
                            robottrail[top_of_stack] = (Position){robot->dir.row, robot->dir.col};
                        }
                    } else {
                        // Retrieve the previous direction from the stack for backtracking
                        robot->dir.row = -robottrail[top_of_stack].row;
                        robot->dir.col = -robottrail[top_of_stack].col;
                        top_of_stack--;
              
                        if (!test) { updateForeground(robot, arena); sleep(100);}
                    }
                }
            } 
        }
        if (!all_tiles_visited) {
            forward(robot, arena);
            visited[robot->r_row][robot->r_col] = 1;          
        }
        
        if (!test) { updateForeground(robot, arena); sleep(100);}

    } while ((top_of_stack > -1) || (!all_tiles_visited)); 

    // Drop markers if back at hometile
    if (!test && robot->markerCount > 0 && 
    (robot->r_row == robot->hometile.row && robot->r_col == robot->hometile.col)) {
        while (robot->markerCount > 0) {
            dropMarker(robot, arena);
        }
        if (!test) { updateForeground(robot, arena); sleep(100);}
    }

    free(robottrail);
    for (int i = 0; i < NUM_ROWS; i++) {
        free(visited[i]);
    }
    free(visited);   

    return robot->markerCount;
}