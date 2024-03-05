    // Header files
#include <stdio.h>
#include <stdlib.h>

// External libraries
#include "raylib.h"
// My files
#include "cellgrid.c"




// Program Entry
int main(int argc, char *argv[]) {

    // Initialization

    // Defaults
    const int width = 1000;
    const int height = 850;
    const int node_distance = 5;

     // Set up grid
    int num_rows = (height / node_distance);
    int num_cols = (width / node_distance);
    bool init = false;
    
    Cell** cells_grid = NULL;
    cells_grid = createCellGrid(width, height, node_distance);

    int* cells_grid_v2 = NULL;
    cells_grid_v2 = createCellGridV2(width, height);
    
    InitWindow(width, height, "Cellular Automota");
    SetTargetFPS(60);


    // Main game loop  ---------------
    while (!WindowShouldClose()) {
        
        // Any update functions
        if (IsKeyPressed(KEY_R)) {
            for (int idx = 0; idx < num_rows; idx++) free(cells_grid[idx]);
            free(cells_grid);
            cells_grid = createCellGrid(width, height, node_distance);
            
        }

        if (IsKeyPressed(KEY_S)) {
            cells_grid = cellAutomationUpdateGrid(cells_grid, num_rows, num_cols);
        }
        
        

        // Drawing objects/entities
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            // Draw grid
            drawCellGrid(cells_grid, num_rows, num_cols);
            

        EndDrawing();
    }



    for (int idx = 0; idx < num_rows; idx++) free(cells_grid[idx]);
    free(cells_grid);
    CloseWindow();

    return 0;
}