#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// #include "grid.h"



// Function declarations
int genRandNum(int min, int max);
int **performRandomWalk(GridCell **grid, int r, int c, int random_start_row, int random_start_col);

GridCell **generateWilsonsMaze(GridCell **grid, int r, int c, int node_distance) {

    // 0. Initializations/Declarations
    int random_start_row, random_start_col; 
    int num_of_cells_in_maze = 0;
    GridCell *start_cell;
    

    // 1. Choose any vertex at random and add it to the UST.
    random_start_row = genRandNum(0, r-1);
    random_start_col = genRandNum(0, c-1);
    printf("%d, %d\n", random_start_row, random_start_col);
    start_cell = &grid[random_start_row][random_start_col];

    start_cell->part_of_final_maze = true;
    num_of_cells_in_maze++;


     // LOOP UNTIL all vertices have been added to the UST (i.e. All vertices are part of maze)
    while (num_of_cells_in_maze < r*c) {

            // 2. Select any vertex that is not already in the UST and perform a random walk until you encounter a vertex that is in the UST.
            random_start_row = genRandNum(0, r-1);
            random_start_col = genRandNum(0, c-1);
            performRandomWalk(grid, r, c, random_start_row, random_start_col);

            // 3. Add the vertices and edges touched in the random walk to the UST.
        // END LOOP
    }

    return grid;
}


// Helper function to perform a random walk starting at a random row,col
int **performRandomWalk(GridCell **grid, int r, int c, int random_start_row, int random_start_col) {

    int **cells_added_maze;
    cells_added_maze = malloc(r * sizeof(int *));
    // for (int i = 0; i < r; i++) cells_added_maze[i] = malloc(2 * sizeof(int))

    GridCell *start_cell;
    start_cell = &grid[random_start_row][random_start_col];
    
    bool loop_found = false;
    while (!loop_found) {
        // choose one of 4 cardinal directions to move in

    }
}


// Helper function to generate a random number between min and max
int genRandNum(int min, int max) {
    
    unsigned int rand_seed;    
    FILE *f;
    
    f = fopen("/dev/urandom", "r");
    fread(&rand_seed, sizeof(rand_seed), 1, f);
    fclose(f);

    srand(rand_seed);    
    return rand() % (max-1) + min;
}