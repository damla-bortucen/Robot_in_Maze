#include "graphics.h"
#include "display.h"
#include "arena.h"
#include "robot.h"
#include <stdio.h>
#include <stdlib.h>

int initial_x; 
int initial_y; 


void drawRobot(int x, int y, Position dir) {
    int corners[2][3];

    // Determine corners of robot triangle based on direction
    if ((dir.row == -1) && (dir.col == 0)) { //UP
            corners[0][0] = x;
            corners[1][0] = y + ROBOT_SIZE;
            corners[0][1] = x + ROBOT_SIZE;
            corners[1][1] = y + ROBOT_SIZE;
            corners[0][2] = x + (ROBOT_SIZE/2);
            corners[1][2] = y;
    } else if ((dir.row == 0) && (dir.col == 1)) { //RIGHT
            corners[0][0] = x;
            corners[1][0] = y;
            corners[0][1] = x;
            corners[1][1] = y + ROBOT_SIZE;
            corners[0][2] = x + ROBOT_SIZE;
            corners[1][2] = y + (ROBOT_SIZE/2);
    } else if ((dir.row == 1) && (dir.col == 0)) { //DOWN 
            corners[0][0] = x;
            corners[1][0] = y;
            corners[0][1] = x + ROBOT_SIZE;
            corners[1][1] = y;
            corners[0][2] = x + (ROBOT_SIZE/2);
            corners[1][2] = y + ROBOT_SIZE;
    } else { //LEFT
            corners[0][0] = x + ROBOT_SIZE;
            corners[1][0] = y;
            corners[0][1] = x + ROBOT_SIZE;
            corners[1][1] = y + ROBOT_SIZE;
            corners[0][2] = x;
            corners[1][2] = y + (ROBOT_SIZE/2);
    }
    //Draw the robot
    setColour(blue);
    drawPolygon(3, corners[0], corners[1]);
    fillPolygon(3, corners[0], corners[1]);
}


void updateForeground(Robot* robot, int** arena) {
    foreground();
    clear();
    
    int x = initial_x, y = initial_y;

    // Draw home tile
    setColour(cyan);
    drawRect(robot->hometile.col*SQUARE_SIZE+initial_x, robot->hometile.row*SQUARE_SIZE+initial_y, SQUARE_SIZE, SQUARE_SIZE);
    fillRect(robot->hometile.col*SQUARE_SIZE+initial_x, robot->hometile.row*SQUARE_SIZE+initial_y, SQUARE_SIZE, SQUARE_SIZE);

    // Draw markers
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            if (arena[row][col] == 2) {
                setColour(pink);
                drawRect(x,y, SQUARE_SIZE, SQUARE_SIZE);
                fillRect(x,y, SQUARE_SIZE, SQUARE_SIZE);
            }
            x += SQUARE_SIZE;
        }
        x = initial_x;
        y += SQUARE_SIZE;
    }

    // Draw robot
    int robot_x = initial_x + (robot->r_col * SQUARE_SIZE);
    int robot_y = initial_y + (robot->r_row * SQUARE_SIZE);
    drawRobot(robot_x, robot_y, robot->dir);
}


void drawArena(int** arena) {
    // Center the arena within the window
    initial_x = (ARENA_WIDTH - (SQUARE_SIZE * NUM_COLS))/2;
    initial_y = (ARENA_HEIGHT - (SQUARE_SIZE * NUM_ROWS))/2;

    background();
    int x = initial_x, y = initial_y;
    
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {

            setColour(gray);
            drawRect(x,y, SQUARE_SIZE, SQUARE_SIZE);

            if (arena[row][col] == 1) { // Wall
                setColour(darkgray);
                fillRect(x,y, SQUARE_SIZE, SQUARE_SIZE);
            } else if (arena[row][col] == 3) { // Obstacle
                setColour(gray);
                fillRect(x,y, SQUARE_SIZE, SQUARE_SIZE);
            }
            x += SQUARE_SIZE;
        }
        x = initial_x;
        y += SQUARE_SIZE;
    }  
}