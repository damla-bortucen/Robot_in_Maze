#ifndef ARENA_H
#define ARENA_H

#define ARENA_WIDTH 600
#define ARENA_HEIGHT 600
#define SQUARE_SIZE 30
#define MARKER_DENSITY 15 // Percentage of tiles that will contain markers
#define OBSTACLE_DENSITY 30 // Percentage of tiles that will contain obstacles

extern int NUM_ROWS;
extern int NUM_COLS;

// Represents a position in the arena by its row and column indeces
typedef struct {
    int row;
    int col;
} Position;

void setArenaSize(); // Sets a random arena size within a range
int** createArena(); // Allocates memory to and initializes a 2D array of the arena
void freeArena(int** arena); // Frees memory allocated to the arena
int initializeArena(int** arena); // Adds markers, empty spaces and walls to the arena
void createObstacles(int** arena, Position start_pos, int totaltiles); // Randomly adds obstacles to the arena without blocking the robot's path

#endif //ARENA.H 
// added guards to prevent redefinition errors