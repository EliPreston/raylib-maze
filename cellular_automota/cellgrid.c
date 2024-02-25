#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "cell.h"


// Create grid of nodes based on height, width, and distance between nodes
Cell **createCellGrid(int window_width, int window_height, int cell_dimension) {

    int num_rows = (window_height / cell_dimension);
    int num_cols = (window_width / cell_dimension);
    printf("%d x %d\n", num_rows, num_cols);

    Cell **grid;
    grid = malloc(num_rows * sizeof(Cell *));

    for (int i = 0; i < num_rows; i++) {
        grid[i] = malloc(num_cols * sizeof(Cell));
    }

    int x_pos = 0;
    int y_pos = 0;
    int solid_val = 0;

    int row_mid = floor(num_rows/2) - 1;
    int col_mid = floor(num_cols/2) - 1;
    
    time_t t;
    srand((unsigned) time(&t));
    
    for (int r = 0; r < num_rows; r++) {
        for (int c = 0; c < num_cols; c++) {

            
            // 10 x 10
            // row 39 to 49, col 59 to 69
            
            if (((r >= row_mid-5) && (r <= row_mid+5)) && ((c >= col_mid-5) && (c <= col_mid+5))) {
                if (rand() % 50 < 25) solid_val = 1;
            } 


            Cell gc = {
                (Vector2) { x_pos, y_pos },
                cell_dimension,
                solid_val,
            };

            grid[r][c] = gc;
            x_pos = x_pos + cell_dimension;
            solid_val = 0;
        }

        x_pos = 0;
        y_pos = y_pos + cell_dimension;
    }
    
    return grid;
}


int drawCellGrid(Cell **grid, int r, int c) {

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {

            Vector2 curr_cell_position = grid[i][j].position;
            int cell_dimension = grid[i][j].dimension;
            int curr_cell_solid = grid[i][j].solid;

            // If solid == 1
            if (curr_cell_solid) {
                DrawRectangleV(curr_cell_position, (Vector2) {cell_dimension, cell_dimension}, BLACK);
            } else {
                DrawRectangleLines(curr_cell_position.x, curr_cell_position.y, cell_dimension, cell_dimension, GRAY);    
            }

        }
    }

    return 0;
}



Cell **cellAutomationUpdateGrid(Cell **grid, int r, int c) {

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {




        }
    }
}