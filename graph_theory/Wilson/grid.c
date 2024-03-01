#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

#include "grid.h"




// Create grid of nodes based on height, width, and distance between nodes
GridCell **createCellGrid(int window_width, int window_height, int node_distance) {

    int num_rows = (window_height / node_distance);
    int num_cols = (window_width / node_distance);
    // int num_nodes = num_rows * num_cols;

    GridCell **grid;
    grid = malloc(num_rows * sizeof(GridCell *));
    for (int i = 0; i < num_rows; i++) grid[i] = malloc(num_cols * sizeof(GridCell));

    int x_pos = 0;
    int y_pos = 0;

    
    for (int r = 0; r < num_rows; r++) {
        for (int c = 0; c < num_cols; c++) {
            
            
            GridCell gc = {
                (Vector2) { x_pos, y_pos },
                NOT_PART_OF_MAZE,
                NULL,
                NONE,
            };

            grid[r][c] = gc;
            x_pos = x_pos + node_distance;
        }

        x_pos = 0;
        y_pos = y_pos + node_distance;
    }
    
    return grid;
}


// Draw grid of nodes
int drawGridCells(GridCell **grid, int r, int c, int node_distance) {


    GridCell *curr_cell;
    Vector2 top_left;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {

            curr_cell = &grid[i][j];
            top_left = curr_cell->top_left;
            

            if (curr_cell->cell_state == PART_OF_MAZE_FINAL) {
                DrawRectangleV(top_left, (Vector2) {node_distance, node_distance}, GREEN);          
            } else { 
                // DrawRectangleV(top_left, (Vector2) {node_distance, node_distance}, BLACK); 
                DrawRectangleLines(top_left.x, top_left.y, node_distance, node_distance, BLACK);  
            }
            
        }
    }

    return 0;
}

