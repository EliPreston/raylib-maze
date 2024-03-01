#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// #include "grid.h"



// Function declarations
int genRandNum(int min, int max);
void performRandomWalk(GridCell **grid, int r, int c, int random_start_row, int random_start_col);

GridCell **generateWilsonsMaze(GridCell **grid, int r, int c, int node_distance) {

    // 0. Initializations/Declarations
    int random_start_row, random_start_col; 
    int num_of_cells_in_maze = 0;
    GridCell *start_cell;
    GridCell *curr_cell;
    // GridCell *cells_to_add_to_final_maze;
    GridCell *cell_walk;
    GridCell *cell_walk_next;

    bool cell_not_in_maze_found;
    

    // 1. Choose any vertex at random and add it to the UST.
    random_start_row = genRandNum(0, r-1);
    random_start_col = genRandNum(0, c-1);
    printf("%d, %d\n", random_start_row, random_start_col);
    start_cell = &grid[random_start_row][random_start_col];

    start_cell->cell_state = PART_OF_MAZE_FINAL;
    num_of_cells_in_maze++;


     // LOOP UNTIL all vertices have been added to the UST (i.e. All vertices are part of final maze)
    while (num_of_cells_in_maze < r*c) {

            // 2. Select any vertex that is not already in the UST and perform a random walk until you encounter a vertex that is in the UST.
            cell_not_in_maze_found = false;
            while (!cell_not_in_maze_found) {
                random_start_row = genRandNum(0, r-1);
                random_start_col = genRandNum(0, c-1);
                if (grid[random_start_row][random_start_col].part_of_final_maze) {
                    cell_not_in_maze_found = true;
                }
            }
            // 
            // 
            // 
            // 
            // MAYBE USE AN ENUM TO KEEP TRACK OF WHICH DIRECTION TO EXIT EACH CELL (ENUM DIRECTION {LEFT, RIGHT, UP DOWN})
            // COULD ALSO USE AN ENUM TO KEEP TRACK OF WHETHER IT IS PART OF A MAZE-WALK OR PART OF THE MAZE-FINAL
            // 
            // 
            // 
            // 
           performRandomWalk(grid, r, c, random_start_row, random_start_col);
           cell_walk = &grid[random_start_row][random_start_col];
           cell_walk_next = cell_walk->next_node;

            while (cell_walk_next != NULL) {
                
            }

            // NEED TO FIGURE OUT WAY TO INDICATE WHICH SIDE OF CELL THAT THE MAZE CONTINUES ON
            // 3. Add the vertices and edges touched in the random walk to the UST.
            // for (int i = 0; i < r; i++) {
            //     if (cells_to_add_to_final_maze[i][0] == -1) break; 

            //     curr_cell = &grid[cells_to_add_to_final_maze[i][0]][cells_to_add_to_final_maze[i][1]];
            //     curr_cell->part_of_final_maze = true;
            // }

    // END LOOP
    }

    return grid;
}


// Helper function to perform a random walk starting at a random row,col
void performRandomWalk(GridCell **grid, int r, int c, int random_start_row, int random_start_col) {

    // GridCell *cells_added_maze;
    // cells_added_maze = malloc(r * sizeof(int *));
    // for (int i = 0; i < r; i++) cells_added_maze[i] = malloc(2 * sizeof(int))

    GridCell *start_cell, *curr_cell;
    start_cell = &grid[random_start_row][random_start_col];
    
    bool loop_found = false;
    int move_direction;
    while (!loop_found) {

        // choose one of the 4 cardinal directions to move in
        //      N
        //   W     E
        //      S

        move_direction = genRandNum(1, 4);
        if (move_direction == 1) {
            // move North (r-1)
            // check if r-1 is valid
            
        }
        if (move_direction == 2) {
            // move East (c+1)
            // check if c+1 is valid
        }
        if (move_direction == 3) {
            // move South (r+1)
            // check if r+1 is valid
        }
        if (move_direction == 4) {
            // move West (c-1)
            // check if c-1 is valid
        }

    }

    return;
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