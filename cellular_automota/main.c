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
    const int width = 1200;
    const int height = 900;
    const int node_distance = 10;

     // Set up grid
    int num_rows = (height / node_distance);
    int num_cols = (width / node_distance);
    bool init = false;
    
    Cell** cells_grid = NULL;
    cells_grid = createCellGrid(width, height, node_distance);

    InitWindow(width, height, "Graph theory based maze creation - Wilson's Algorithm");
    SetTargetFPS(60);


    // Main game loop  ---------------
    while (!WindowShouldClose()) {
        
        // Any update functions
        if (IsKeyPressed(KEY_R)) {
            cells_grid = createCellGrid(width, height, node_distance);
        }
        

        // Drawing objects/entities
        BeginDrawing();

            ClearBackground(RAYWHITE);
            if (!init) {
                drawCellGrid(cells_grid, num_rows, num_cols);
                init = true;
            }
            
            // Draw grid
            
            

        EndDrawing();
    }




    free(cells_grid);
    CloseWindow();

    return 0;
}