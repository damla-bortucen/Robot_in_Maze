# Robot_in_Maze

## Description
This program simulates a robot navigating through a random-sized and shaped 2D arena with randomly placed obstacles and markers. The robot autonomously locates and collects all markers while avoiding obstacles, and returns them to its home-tile.

#### Arena Layout
- **Markers:** Pink tiles
- **Obstacles:** Light gray tiles
- **Robot:** Blue triangle
- **Walls:** Dark gray tiles
- **Home Tile:** Cyan tile

<img width="597" alt="Screen Shot 2024-11-07 at 2 29 18 PM" src="https://github.com/user-attachments/assets/a464fc1c-5116-4e26-a8d5-62d83e3b28ae" />

## Compliling and Execution
To **Compile** the program, run this command in terminal:
```bash
gcc graphics.c arena.c robot.c display.c main.c
```
Ensure all source files are in the same directory.

To **Run** the program, execute: 
```bash
./a.out | java -jar drawapp-4.0.jar
```
This command runs the C program and pipes its output to the drawing application drawapp-4.1.jar for visual display. Make sure drawapp-4.1.jar is in the same directory and is version 4.1.

## What Does it Do:
When the program is executed:
1. A random-sized and shaped 2D arena is generated, including
- **Markers:** Randomly placed across the arena, occupying around 20% of open tiles (defined by MARKER_DENSITY).
- **Obstacles:** Randomly placed across the arena, ensuring they do not block the robot's access to any markers.
2. A robot is initialized on a randomly chosen, empty tile and faces a random direction. This starting tile is it's **home tile**.

#### Robot Navigation:
The robot uses a depth-first search(DFS) algorithm to explore all tiles in the arena:
1. Collecting the markers it encounters.
2. Returning them to the home tile once all the markers are collected.

**Arena Initially:**

<img width="600" alt="Screen Shot 2024-11-07 at 2 44 18 PM" src="https://github.com/user-attachments/assets/fe0eb8af-20ef-4a7e-8929-0f4c6cc2cc72" />

**Arena Finally:**

<img width="598" alt="Screen Shot 2024-11-07 at 2 44 43 PM" src="https://github.com/user-attachments/assets/3af50128-a61b-49be-8e73-aac10a20823d" />
