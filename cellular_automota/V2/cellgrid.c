#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include "cell.h"



int* createCellGridV2(int window_width, int window_height) {

    int num_rows = (window_height / cell_dimension);
    int num_cols = (window_width / cell_dimension);
    printf("%d x %d\n", num_rows, num_cols);

    int *grid;
    grid = malloc((num_rows * num_cols) * sizeof(int));

    // 0 means dead cell, 1 means alive cell
    



}


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

    Cell gc;
    int x_pos = 0;
    int y_pos = 0;
    int solid_val = 0;

    int row_mid = floor(num_rows/2) - 1;
    int col_mid = floor(num_cols/2) - 1;
    int initial_size = 30;
    
    time_t t;
    srand((unsigned) time(&t));
    
    for (int r = 0; r < num_rows; r++) {
        for (int c = 0; c < num_cols; c++) {
            
            if (((r >= row_mid-(initial_size/2)) && (r <= row_mid+(initial_size/2))) && 
                ((c >= col_mid-(initial_size/2)) && (c <= col_mid+(initial_size/2)))) {
                    if (rand() % 50 < 30) solid_val = 1;
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

    Vector2 curr_cell_position;
    int cell_dimension;
    int curr_cell_solid ;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {

            curr_cell_position = grid[i][j].position;
            cell_dimension = grid[i][j].dimension;
            curr_cell_solid = grid[i][j].solid;

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


// i,j is the cell in grid[i][j]
int checkSurroundingCells(Cell **grid, int i, int j, int r, int c) {

    Cell curr_cell = grid[i][j];
    int alive_cells = 0;

    if ((i-1) > -1 && (i-1) < r) {
        Cell n = grid[i-1][j];
        if (n.solid) alive_cells++;
    }
    if ((i-1) > -1 && (i-1) < r && (j+1) > -1 && (j+1) < c) {
        Cell ne = grid[i-1][j+1];
        if (ne.solid) alive_cells++;
    }
    if ((j+1) > -1 && (j+1) < c) {
        Cell e = grid[i][j+1];
        if (e.solid) alive_cells++;
    }
    if ((i+1) > -1 && (i+1) < r && (j+1) > -1 && (j+1) < c) {
        Cell se = grid[i+1][j+1];
        if (se.solid) alive_cells++;
    }
    if ((i+1) > -1 && (i+1) < r) {
        Cell s = grid[i+1][j];
        if (s.solid) alive_cells++;
    }
    if ((i+1) > -1 && (i+1) < r && (j-1) > -1 && (j-1) < c) {
        Cell sw = grid[i+1][j-1];
        if (sw.solid) alive_cells++;
    }
    if ((j-1) > -1 && (j-1) < c) {
        Cell w = grid[i][j-1];
        if (w.solid) alive_cells++;
    }
    if ((i-1) > -1 && i < r && (j-1) > -1 && j < c) {
        Cell nw = grid[i-1][j-1];
        if (nw.solid) alive_cells++;
    }

    return alive_cells;
}


Cell **cellAutomationUpdateGrid(Cell **grid, int r, int c) {

    Cell *curr_cell;
    int neighbourhood;

    // for (int iter = 1; iter < 6; iter++) {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {

                
                curr_cell = &grid[i][j];
                neighbourhood = checkSurroundingCells(grid, i, j, r, c);
                
                if (curr_cell->solid == 0) {
                    
                    if (neighbourhood == 3) {
                        curr_cell->solid = 1;
                    } 
                }
                if (curr_cell->solid == 1) {
                    if (neighbourhood < 1 || neighbourhood > 5) {
                        curr_cell->solid = 0;
                    }
                }            
            }
        }
    // }

    return grid;
}