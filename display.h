#ifndef DISPLAY_H
#define DISPLAY_H

#include "robot.h"
#include "arena.h"

void drawRobot(int x, int y, Position dir);
void updateForeground(Robot* robot, int** arena); // Updates the display of foreground: the robot and markers
void drawArena(int** arena); // Draws the initial arena layout based on the 2D array


#endif