// Header files
#include <stdio.h>
#include <stdlib.h>

// External libraries
#include "raylib.h"
// My files
#include "grid.c"




// Program Entry
int main(int argc, char *argv[]) {

    // Initialization

    // Defaults
    const int width = 800;
    const int height = 500;
    const int nodeDistance = 20;

     // Set up grid
    int num_rows = (height / nodeDistance);
    int num_cols = (width / nodeDistance);
    
    Edge** edge_grid = NULL;
    edge_grid = createCellGrid(width, height, nodeDistance);

    InitWindow(width, height, "Graph theory based maze creation");
    SetTargetFPS(60);


    // Main game loop  ---------------
    while (!WindowShouldClose()) {
        
        // Any update functions
        

        // Drawing objects/entities
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            // Draw grid
            drawGridCells(grid, num_rows, num_cols);

        EndDrawing();
    }


    free(grid);
    CloseWindow();

    return 0;
}