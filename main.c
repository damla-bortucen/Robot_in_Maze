#include <stdio.h>
#include "arena.h"
#include "robot.h"
#include "display.h"
#include "graphics.h"
#include <stdlib.h>


Position placeRobot(int** arena) {
    int rd_row = rand() % (NUM_ROWS - 2) + 1; // Ensures the row is within bounds (1 < rd_row < NUM_ROWS-1), avoiding the borders.
    int start, end;

    for (int i = 1; i < NUM_COLS - 1; i++) {
        if (arena[rd_row][i] != 1 && arena[rd_row][i - 1] == 1) {
            start = i; // Start of empty space
        } 
        if (arena[rd_row][i] != 1 && arena[rd_row][i + 1] == 1) {
            end = i; // End of empty space
            break;
        }
    }
    int rd_col = rand() % (end - start + 1) + start; // Random column within the empty space

    return ((Position){rd_row, rd_col});
}


Position randRobotDir() {
    switch (rand() % 4) {
        case 0 : return (Position){-1, 0};
                break;
        case 1 : return (Position){0, 1};
                break;
        case 2 : return (Position){1, 0};
                break;
        case 3 : return (Position){0, -1};
                break;
    }
    return (Position){-1, -1};
}


int main(void) {
    setArenaSize(); 
    int** arena = createArena();

    // Initialize arena with markers
    int totalmarkers = initializeArena(arena);
    
    // Place the robot at a valid random position in the arena
    Position robot_start_pos = placeRobot(arena);  
    Robot robot = {robot_start_pos.row, robot_start_pos.col, robot_start_pos, randRobotDir(), 0};

    createObstacles(arena, robot_start_pos, totalmarkers);

    // Set the window size for graphics
    setWindowSize(ARENA_WIDTH, ARENA_HEIGHT);
    clear();
    drawArena(arena);
    updateForeground(&robot, arena);
    sleep(400);

    
    findMarkers(&robot, arena, 0); // The 0 indicates that findMarkers() is not being run as a test
    
    // Free allocated memory for arena
    freeArena(arena);

    return 0;
}