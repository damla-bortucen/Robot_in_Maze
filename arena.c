#include "graphics.h"
#include "arena.h"
#include "robot.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int NUM_ROWS = 0;
int NUM_COLS = 0;

#define MAX(a,b) (((a) > (b)) ? (a) : (b))

void setArenaSize() {
    srand(time(NULL)); // Seed the random number generator with the current time so its truly random
    NUM_ROWS = (rand() % ((ARENA_HEIGHT / SQUARE_SIZE) - 12)) + 12; // minimum 12 and max height/square_size <- range
    NUM_COLS = (rand() % ((ARENA_WIDTH / SQUARE_SIZE) - 12)) + 12;

}


int** createArena() {
    // Arena is a 2D array represented as a pointer to an array of row pointers.
    // Each row pointer points to an array of integers.
    int** arena = malloc(NUM_ROWS * sizeof(int*));
    for (int i = 0; i < NUM_ROWS; i++) {
        arena[i] = malloc(NUM_COLS * sizeof(int));
    }
    return arena;
}


void freeArena(int** arena) {
    for (int i = 0; i < NUM_ROWS; i++) {
        free(arena[i]);
    }
    free(arena);
}


int initializeArena(int** arena) {
    int prev_start = 1; 
    int prev_end = NUM_COLS - 2;;
    int row_start;
    int row_end;
    int random_number; 
    int total_markers = 0;

    for (int row = 0; row < NUM_ROWS; row++) {
        // Generate start and end points of each row, making sure its connected to the previous row
        row_start = (rand() % (prev_end)) + 1;
        row_end = (rand() % (NUM_COLS - 1 - MAX(prev_start, row_start))) + MAX(prev_start, row_start);
        
        for (int col = 0; col < NUM_COLS; col++) {
            if (row == 0 || col < row_start || row == (NUM_ROWS-1) || col > row_end) {
                arena[row][col] = 1; // Wall
            } else if (row_end - row_start > 1) {
                // Only create markers and obstacles if the passage is larger than 1 tile
                random_number = (rand() % 100);
                if (random_number < MARKER_DENSITY) {
                    arena[row][col] = 2; // Marker
                    total_markers++;
                } else {
                    arena[row][col] = 0; // Empty
                }   
            } else {
                arena[row][col] = 0; // Empty
            }
        }
        prev_start = row_start;
        prev_end = row_end;
    }
    return total_markers;
}


void createObstacles(int** arena, Position start_pos, int totalmarkers) {
    int markers_after_obstacle;
    int obstacle_probability;
    
    int** copy_of_arena = malloc(NUM_ROWS * sizeof(int*));
    for (int i = 0; i < NUM_ROWS; i++) {
        copy_of_arena[i] = malloc(NUM_COLS * sizeof(int));
    }
    // Initialize test robot at start position
    Robot testrobot = {start_pos.row, start_pos.col, start_pos, {0,1}, 0};

    for (int row = 1; row < NUM_ROWS-1; row++) {
        for (int col = 1; col < NUM_COLS-1; col++) {

            if ((arena[row][col] == 0)  && !((row == start_pos.row) && (col == start_pos.col))) {
                // Set copy_of_arena to initial arena
                for (int row2 = 0; row2 < NUM_ROWS; row2++) {
                    for (int col2 = 0; col2 < NUM_COLS; col2++) {
                        copy_of_arena[row2][col2] = arena[row2][col2];
                    }
                }
                arena[row][col] = 3;
                copy_of_arena[row][col] = 3;
                // findMarkers() is run as a test to see if all markers can be reached
                markers_after_obstacle = findMarkers(&testrobot, copy_of_arena, 1);
                // Reset Robot
                testrobot.r_row = start_pos.row;
                testrobot.r_col = start_pos.col;
                testrobot.hometile = start_pos;
                testrobot.markerCount = 0;
                // Determines if an obstacle should be placed based on OBSTACLE_DENSITY.
                obstacle_probability = (rand() % 100) < OBSTACLE_DENSITY;

                if (markers_after_obstacle != totalmarkers || !obstacle_probability){
                    arena[row][col] = 0;
                    copy_of_arena[row][col] = 0;
                }
            }
        }
    }
    // Free memory for copy_of_arena
    freeArena(copy_of_arena);
}