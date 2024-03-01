// Header files
#include <stdio.h>
#include <stdlib.h>

// External libraries
#include "raylib.h"
// My files
#include "grid.c"
#include "wilson.c"




// Program Entry
int main(int argc, char *argv[]) {

    // Initialization

    // Defaults
    const int width = 900;
    const int height = 600;
    const int node_distance = 15;

     // Set up grid
    int num_rows = (height / node_distance);
    int num_cols = (width / node_distance);
    
    GridCell** grid = NULL;
    grid = createCellGrid(width, height, node_distance);
    // generateWilsonsMaze(grid, num_rows, num_cols, node_distance);
    // generateWilsonsMaze(grid, num_rows, num_cols, node_distance, false);

    InitWindow(width, height, "Graph theory based maze creation - Wilson's Algorithm");
    SetTargetFPS(60);


    // Main game loop  ---------------
    while (!WindowShouldClose()) {
        
        // Any update functions
        if (IsKeyPressed(KEY_R)) {
            // This doens't work, i don't know why it basically generates the same set of numbers over and over
            // generateWilsonsMaze(grid, num_rows, num_cols, node_distance, true);
            generateWilsonsMaze(grid, num_rows, num_cols, node_distance);
        }
        

        // Drawing objects/entities
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            // Draw grid
            drawGridCells(grid, num_rows, num_cols, node_distance);
            

        EndDrawing();
    }


    free(grid);
    CloseWindow();

    return 0;
}