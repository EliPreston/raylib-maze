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

    for (int i = 0; i < num_rows; i++) {
        grid[i] = malloc(num_cols * sizeof(GridCell));
    }

    int x_pos = 0;
    int y_pos = 0;

    
    for (int r = 0; r < num_rows; r++) {
        for (int c = 0; c < num_cols; c++) {
            
            // printf("%d@%d -> %d, %d\n", c, r, x_pos, y_pos);
            GridCell gc = {
                (Vector2) { x_pos, y_pos },
                (Vector2) { x_pos+node_distance, y_pos },
                (Vector2) { x_pos, y_pos+node_distance },
                (Vector2) { x_pos+node_distance, y_pos+node_distance },
                false,
                NULL,
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

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {

            GridCell curr_cell = grid[i][j];

            if (curr_cell.part_of_maze) {
                DrawRectangleV(curr_cell.top_left, (Vector2) {node_distance, node_distance}, GREEN);          
            } else { 
                DrawLineEx(curr_cell.top_left, curr_cell.top_right, 1.0, BLACK);
                DrawLineEx(curr_cell.top_right, curr_cell.bottom_right, 1.0, BLACK);
                DrawLineEx(curr_cell.bottom_right, curr_cell.bottom_left, 1.0, BLACK);
                DrawLineEx(curr_cell.bottom_left, curr_cell.top_left, 1.0, BLACK);
            }
            
        }
    }

    return 0;
}


// Paramters r and c are the num of rows/cols in the grid, and dictate 
// the bounds for generating the random positions
int **generateRandomGrid(int r, int c) {

    // Setup random positions
    time_t t;
    srand(time(&t));
    int **random_grid;
    int rand_row, rand_col;
    random_grid = malloc(r * c * 2 * sizeof(int *));

    for (int i = 0; i < r*c*2; i++) {
        random_grid[i] = malloc(2 * sizeof(int));
        random_grid[i][0] = rand() / (RAND_MAX / r + 1);
        random_grid[i][1] = rand() / (RAND_MAX / c + 1);
    }

    return random_grid;
}

void incrementRandGridIdx(GridCell cell, int *curr_random_grid_index) {
    while (cell.part_of_maze) {
        (*curr_random_grid_index)++;
    }
    return;
}

// https://weblog.jamisbuck.org/2011/1/20/maze-generation-wilson-s-algorithm
// Generate maze using Wilson's algorithm
int generateWilsonsMaze(GridCell **grid, int r, int c, int node_distance, bool already_set) {

    // Reset grid if already set 
    if (already_set) {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) grid[i][j].part_of_maze = false;
        }
    }

    // Setup random positions
    int **random_grid = generateRandomGrid(r, c);
    int curr_random_grid_index = 0;
    int *curr_random_pos = random_grid[curr_random_grid_index];

    // Setup variables for algorithm
    bool reached_end_of_walk = false;

    GridCell initial_cell = grid[curr_random_pos[0]][curr_random_pos[1]];
    GridCell start_of_walk;
    start_of_walk = grid[curr_random_pos[0]][curr_random_pos[1]];
    start_of_walk.part_of_maze = true;

    GridCell curr_cell_in_walk = start_of_walk;

    // 0 is up, 1 is left, 2 is right, 3 is down
    int next_cell_in_walk;
    next_cell_in_walk = rand() / (RAND_MAX / 4 + 1); 

    incrementRandGridIdx(start_of_walk, &curr_random_grid_index);
    printf("%d, %d\n, ", curr_random_grid_index, next_cell_in_walk);

    while (curr_random_grid_index < r*c*2) {
        
        while (!reached_end_of_walk) {
            
        }
    }


    





    for (int i = 0; i < r*c*2; i++) free(random_grid[i]);
    free(random_grid);
    return 0;
}
