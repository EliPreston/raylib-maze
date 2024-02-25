#include <stdio.h> 
#include <stdlib.h>

#include "grid.h"


// Create grid of nodes based on height, width, and distance between nodes
GridCell **createCellGrid(int windowWidth, int windowHeight, int nodeDistance) {

    int num_rows = (windowHeight / nodeDistance);
    int num_cols = (windowWidth / nodeDistance);
    // int num_nodes = num_rows * num_cols;

    GridCell **grid;
    grid = malloc(num_rows * sizeof(GridCell *));

    for (int i = 0; i < num_rows; i++) {
        grid[i] = malloc(num_cols * sizeof(GridCell));
    }

    int x_pos = 0;
    int y_pos = 0;
    
    for (int r = 0; r < num_rows; r++) {
        for (int c = 0; c < num_cols; c++) {


            // top_left = (Vector2) { x, y }
            // top_right = (Vector2) { x+nodeDistance, y }
            // bottom_left = (Vector2) { x, y+nodeDistance }
            // bottom_right = (Vector2) { x+nodeDistance, y+nodeDistance }
            GridCell gc = {
                (Vector2) { x_pos, y_pos },
                (Vector2) { x_pos+nodeDistance, y_pos },
                (Vector2) { x_pos, y_pos+nodeDistance },
                (Vector2) { x_pos+nodeDistance, y_pos+nodeDistance },
                false,
            };

            grid[r][c] = gc;
            x_pos = x_pos + nodeDistance;
        }

        x_pos = 0;
        y_pos = y_pos + nodeDistance;
    }
    
    return grid;
}


// Draw grid of nodes
int drawGridCells(GridCell **grid, int r, int c) {

    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {

            GridCell curr_cell = grid[i][j];
            DrawLineEx(curr_cell.top_left, curr_cell.top_right, 1.0, BLACK);
            DrawLineEx(curr_cell.top_right, curr_cell.bottom_right, 1.0, BLACK);
            DrawLineEx(curr_cell.bottom_right, curr_cell.bottom_left, 1.0, BLACK);
            DrawLineEx(curr_cell.bottom_left, curr_cell.top_left, 1.0, BLACK);
        }
    }

    return 0;
}