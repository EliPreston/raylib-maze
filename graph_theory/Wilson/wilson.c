#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// #include "grid.h"



// Function declarations
int genRandNum(int min, int max);
bool isValidIndex(int row_max, int col_max, int given_row, int given_col);
int getValidMove(GridCell **grid, int r, int c, int *curr_row_pos, int *curr_col_pos);
void performRandomWalk(GridCell **grid, int r, int c, int random_start_row, int random_start_col);
void resetMaze(GridCell **grid, int r, int c);

GridCell **generateWilsonsMaze(GridCell **grid, int r, int c, int node_distance) {

    // 0. Initializations/Declarations
    int random_start_row, random_start_col; 
    int num_of_cells_in_maze = 0;
    bool cell_not_in_maze_found;

    GridCell *start_cell;
    GridCell *cell_walk_next;
    GridCell *curr_cell_in_walk;
    

    // 1. Choose any vertex at random and add it to the UST.
    // Initially start_cell is the very first cell chosen to be added the final maze
    // and random_start_row/col is the location of that first cell in the grid
    // (the meaning of these variables change in the while loop below)
    random_start_row = genRandNum(0, r-1);
    random_start_col = genRandNum(0, c-1);
    printf("%d, %d\n", random_start_row, random_start_col);

    start_cell = &grid[random_start_row][random_start_col];
    start_cell->cell_state = PART_OF_MAZE_FINAL;
    num_of_cells_in_maze++;


    // LOOP UNTIL all vertices have been added to the UST (i.e. All vertices are part of final maze)
    while (num_of_cells_in_maze < r*c) {
            
            printf("Number of cells currently in final maze: %d\n", num_of_cells_in_maze);
            // 2. Select any vertex that is not already in the UST and perform a random walk until you encounter a vertex that is in the UST.
            // Variables random_start_row/col now denote the position of the random start position of the current random walk
            cell_not_in_maze_found = false;
            while (!cell_not_in_maze_found) {
                random_start_row = genRandNum(0, r-1);
                random_start_col = genRandNum(0, c-1);
                if ((&grid[random_start_row][random_start_col])->cell_state == NOT_PART_OF_MAZE) {
                    // Similarily for start_cell as random_start_row/col, start_cell is now the cell that starts the current random walk
                    start_cell = &grid[random_start_row][random_start_col];
                    cell_not_in_maze_found = true;
                }
            }
            // printf("Found a cell not in the final maze at: %d, %d\n", random_start_row, random_start_col);
            performRandomWalk(grid, r, c, random_start_row, random_start_col);


            // 3. Add the vertices and edges touched in the random walk to the UST.
            cell_walk_next = start_cell->next_node;
            while (cell_walk_next != NULL) {
                curr_cell_in_walk = cell_walk_next;
                cell_walk_next = curr_cell_in_walk->next_node;
                curr_cell_in_walk->cell_state = PART_OF_MAZE_FINAL;
                num_of_cells_in_maze++;
            }
    

            // 4. RESET GRID SPACES NOT IN FINAL MAZE
            // (spaces that were part of the random walk, but potentially not added to final maze)
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    if ((&grid[i][j])->cell_state == PART_OF_MAZE_WALK) (&grid[i][j])->cell_state = NOT_PART_OF_MAZE;
                }
            }

    // END LOOP
    printf("------------------\n");
    printf("Number of cells in final maze: %d / %d\n", num_of_cells_in_maze, r*c);
    }

    return grid;
}


// Helper function to perform a random walk starting at a random row,col
void performRandomWalk(GridCell **grid, int r, int c, int random_start_row, int random_start_col) {

    printf("Performing random walk starting at: %d, %d\n", random_start_row, random_start_col);

    GridCell *curr_cell, *next_cell;
    curr_cell = &grid[random_start_row][random_start_col];

    // int curr_row_pos = random_start_row;
    // int curr_col_pos = random_start_col;

    int next_row_pos = random_start_row;
    int next_col_pos = random_start_col;
    
    // bool loop_found = false;
    bool connected_to_final_maze = false;
    int move_direction;
    while (!connected_to_final_maze) {

        // choose one of the 4 cardinal directions to move in
        //           N 
        //          (1)
        //  W (4)         (2) E
        //          (3) 
        //           S

        // printf("Moving from: %d, %d to ", next_row_pos, next_col_pos);
        // getValidMove() modifies next_row/col_pos so that when the method returns, the variables identify the position of the next valid cell 
        move_direction = getValidMove(grid, r, c, &next_row_pos, &next_col_pos);
        // printf("%d, %d with direction %d\n", next_row_pos, next_col_pos, move_direction);

        // printf("Trying to find cell: %d, %d\n", random_start_row, random_start_col);

        next_cell = &grid[next_row_pos][next_col_pos];

        curr_cell->next_node = next_cell;
        if (next_cell->cell_state == PART_OF_MAZE_FINAL) {
            
            switch (move_direction) {
                case 1: 
                    curr_cell->cell_exit_direction = NORTH; 
                    next_cell->cell_entrance_direction = SOUTH;
                    break;
                case 2: 
                    curr_cell->cell_exit_direction = EAST;
                    next_cell->cell_entrance_direction = WEST;
                    break;
                case 3: 
                    curr_cell->cell_exit_direction = SOUTH; 
                    next_cell->cell_entrance_direction = NORTH;
                    break;
                case 4: 
                    curr_cell->cell_exit_direction = WEST; 
                    next_cell->cell_entrance_direction = EAST;
                    break;
                default: printf("Should not hit this defualt case, this is an error\n");
            }
            connected_to_final_maze = true;
        } 
        else if (next_cell->cell_state == NOT_PART_OF_MAZE || next_cell->cell_state == PART_OF_MAZE_WALK) {

            curr_cell->cell_state = PART_OF_MAZE_WALK;
            switch (move_direction) {
                case 1: 
                    curr_cell->cell_exit_direction = NORTH; 
                    next_cell->cell_entrance_direction = SOUTH;
                    break;
                case 2: 
                    curr_cell->cell_exit_direction = EAST;
                    next_cell->cell_entrance_direction = WEST;
                    break;
                case 3: 
                    curr_cell->cell_exit_direction = SOUTH; 
                    next_cell->cell_entrance_direction = NORTH;
                    break;
                case 4: 
                    curr_cell->cell_exit_direction = WEST; 
                    next_cell->cell_entrance_direction = EAST;
                    break;
                default: printf("Should not hit this defualt case, this is an error\n");
            }

        }
        curr_cell = next_cell;
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

// Helper function to verify whether an index in an r x c grid is within bounds
bool isValidIndex(int row_max, int col_max, int given_row, int given_col) {

    if (given_row < 0 || given_row >= row_max) return false;
    if (given_col < 0 || given_col >= col_max) return false;
    return true;
}

int getValidMove(GridCell **grid, int r, int c, int *curr_row_pos, int *curr_col_pos) {
    
        bool found_valid_move = false;
        int move_direction;
        while (!found_valid_move) {

            move_direction = genRandNum(1, 5);

            if (move_direction == 1) {
                //  move North (r-1): check if r-1 is valid
                if (isValidIndex(r, c, (*curr_row_pos)-1, (*curr_col_pos))) {
                    (*curr_row_pos)--;
                    found_valid_move = true;
                    // printf("moving north (1)\n");
                    return 1;
                }
            }
            if (move_direction == 2) {
                // move East (c+1): check if c+1 is valid
                if (isValidIndex(r, c, (*curr_row_pos), (*curr_col_pos)+1)) {
                    (*curr_col_pos)++;
                    found_valid_move = true;
                    // printf("moving east (2)\n");
                    return 2;
                }
            }
            if (move_direction == 3) {
                // move South (r+1): check if r+1 is valid
                if (isValidIndex(r, c, (*curr_row_pos)+1, (*curr_col_pos))) {
                    (*curr_row_pos)++;
                    found_valid_move = true;
                    // printf("moving south (3)\n");
                    return 3;
                }
            }
            if (move_direction == 4) {
                // move West (c-1): check if c-1 is valid
                if (isValidIndex(r, c, (*curr_row_pos), (*curr_col_pos)-1)) {
                    (*curr_col_pos)--;
                    found_valid_move = true;
                    // printf("moving west (4)\n");
                    return 4;
                }
            }

        }
        return -1;
}


void resetMaze(GridCell **grid, int r, int c) {

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            (&grid[i][j])->cell_state = NOT_PART_OF_MAZE;
            (&grid[i][j])->cell_exit_direction = NONE;
            (&grid[i][j])->next_node = NULL;
        }
    }
    printf("Grid/Board reset\n");
    return;
}