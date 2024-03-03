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

    int start_row;
    int start_col;
    int num_of_cells_in_maze;
    bool cell_not_in_maze_found;
    bool connected_to_final_maze;

    int took_too_long_count = 0;
    bool took_too_long = false;
    int flip_search_direction = 0;

    int walk_start_row;
    int walk_start_col;
    int walk_next_row;
    int walk_next_col;
    int move_direction;
    
    GridCell *start_cell;
    GridCell *cell_walk_start;
    GridCell *cell_walk_curr;
    GridCell *cell_walk_prev;

    GridCell *curr_cell_backtrack;

    int reset_edges[4];


    // start_row = genRandNum(0, r-1);
    // start_col = genRandNum(0, c-1);
    start_row = 0;
    start_col = 0;
    (&grid[start_row][start_col])->cell_state = PART_OF_MAZE_FINAL;
    (&grid[start_row][start_col])->start_cell = true;
    num_of_cells_in_maze = 1;

    printf("INITAL CELL: (%d, %d)\n", start_row, start_col);
   

    int count1 = 0;
    while (num_of_cells_in_maze <= (r*c)) {
    // while (count1 < 200) {
        count1++;

        cell_not_in_maze_found = false;
        // printf("finding cell not in maze: ");
        while (!cell_not_in_maze_found && !took_too_long) {

            walk_start_row = genRandNum(0, r-1);
            walk_start_col = genRandNum(0, c-1);

            if ((&grid[walk_start_row][walk_start_col])->cell_state != PART_OF_MAZE_FINAL) {
                cell_walk_start = &grid[walk_start_row][walk_start_col];
                cell_not_in_maze_found = true;
                // printf("found free cell at %d, %d\n", walk_start_row, walk_start_col);
            }

            took_too_long_count++;
            if (took_too_long_count > 1000) took_too_long = true;
        }

        if (took_too_long) {
            switch (flip_search_direction) {
                case 0:
                    flip_search_direction = 1;
                    for (int i = 0; i < r; i++) {
                        for (int j = 0; j < c; j++) {
                            if ((&grid[i][j])->cell_state != PART_OF_MAZE_FINAL) {
                                cell_walk_start = &grid[i][j];
                                cell_not_in_maze_found = true;
                                // printf("Took too long, but found free cell at %d, %d\n", i, j);
                                break;
                            }
                        }
                        if (cell_not_in_maze_found) break;
                    }   
                
                case 1:
                    flip_search_direction = 1;
                    for (int j = 0; j < c; j++) {
                        for (int i = 0; i < r; i++) {
                            if ((&grid[i][j])->cell_state != PART_OF_MAZE_FINAL) {
                                cell_walk_start = &grid[i][j];
                                cell_not_in_maze_found = true;
                                // printf("Took too long, but found free cell at %d, %d\n", i, j);
                                break;
                            }
                        }
                        if (cell_not_in_maze_found) break;
                    }   
            }

            if (!cell_not_in_maze_found) {
                printf("NO EMPTY CELLS\n");
                return grid;
            }
        }


        // Need to set the next position(s) to the start position(s) initally because the 
        // getValidMove method modifies these positions directly
        walk_next_row = walk_start_row;
        walk_next_col = walk_start_col;
        cell_walk_prev = cell_walk_start;
        connected_to_final_maze = false;

        while (!connected_to_final_maze) {

            move_direction = getValidMove(grid, r, c, &walk_next_row, &walk_next_col);
            cell_walk_curr = &grid[walk_next_row][walk_next_col];
            cell_walk_prev->next_node = cell_walk_curr;

            // RATHER THAN KEEPING TRACK OF DIRECTION HERE
            // CALCULATE WHICH EDGES NEED TO BE DRAWN/REMOVED WHEN BACKTRACKING

            if (cell_walk_curr->cell_state == PART_OF_MAZE_FINAL) {
                
                connected_to_final_maze = true;
                cell_walk_curr->next_node = NULL;

                switch (move_direction) {
                    case 1: 
                        // change prev cell edges to correspond with which direction it was exited
                        // change curr cell edges to correspond with which direction it was entered
                        (cell_walk_prev->edges)[0] = 0; 
                        (cell_walk_curr->edges)[2] = 0;
                        break;
                    case 2: 
                        (cell_walk_prev->edges)[1] = 0; 
                        (cell_walk_curr->edges)[3] = 0;
                        break;
                    case 3: 
                        (cell_walk_prev->edges)[2] = 0; 
                        (cell_walk_curr->edges)[0] = 0;
                        break;
                    case 4: 
                        (cell_walk_prev->edges)[3] = 0; 
                        (cell_walk_curr->edges)[1] = 0;
                        break;
                    default: printf("Should not hit this default case, this is an error\n");
                }


            } 
            else {
                //              NORTH  EAST  SOUTH  WEST
                // edges[4] = { 1/0,   1/0,  1/0,   1/0 }
                switch (move_direction) {
                    case 1: 
                        // change prev cell edges to correspond with which direction it was exited
                        // change curr cell edges to correspond with which direction it was entered
                        (cell_walk_prev->edges)[0] = 0; 
                        (cell_walk_curr->edges)[2] = 0;
                        break;
                    case 2: 
                        (cell_walk_prev->edges)[1] = 0; 
                        (cell_walk_curr->edges)[3] = 0;
                        break;
                    case 3: 
                        (cell_walk_prev->edges)[2] = 0; 
                        (cell_walk_curr->edges)[0] = 0;
                        break;
                    case 4: 
                        (cell_walk_prev->edges)[3] = 0; 
                        (cell_walk_curr->edges)[1] = 0;
                        break;
                    default: printf("Should not hit this default case, this is an error\n");
                    }
            }

            cell_walk_prev = cell_walk_curr;
            move_direction = 0;
        }

        // 3. Add the vertices and edges touched in the random walk to the UST.
        curr_cell_backtrack = cell_walk_start;

        while (curr_cell_backtrack->next_node != NULL) {

            curr_cell_backtrack->cell_state = PART_OF_MAZE_FINAL;
            curr_cell_backtrack = curr_cell_backtrack->next_node;
            
            num_of_cells_in_maze++;
        }

        // 4. RESET GRID SPACES NOT IN FINAL MAZE
        // (spaces that were part of the random walk, but potentially not added to final maze)

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if ((&grid[i][j])->cell_state != PART_OF_MAZE_FINAL) {
                    (&grid[i][j])->cell_state = NOT_PART_OF_MAZE;
                    (&grid[i][j])->next_node = NULL;
                    ((&grid[i][j])->edges)[0] = 1;
                    ((&grid[i][j])->edges)[1] = 1;
                    ((&grid[i][j])->edges)[2] = 1;
                    ((&grid[i][j])->edges)[3] = 1;


                    // reset_edges = (&grid[i][j])->edges;
                    // for (int k = 0; k < 3; k++)
                
                    // (&grid[i][j])->cell_entrance_direction = NONE;
                    // (&grid[i][j])->cell_exit_direction = NONE;
                }

                
            }
        }
    }

    int cell_count = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j].cell_state == PART_OF_MAZE_FINAL) cell_count++;
        }
    }
    printf("Real count of number of cells in final maze: %d\n", cell_count);
    printf("------------------\n");

    return grid;
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
                    return 1;
                }
            }
            if (move_direction == 2) {
                // move East (c+1): check if c+1 is valid
                if (isValidIndex(r, c, (*curr_row_pos), (*curr_col_pos)+1)) {
                    (*curr_col_pos)++;
                    found_valid_move = true;
                    return 2;
                }
            }
            if (move_direction == 3) {
                // move South (r+1): check if r+1 is valid
                if (isValidIndex(r, c, (*curr_row_pos)+1, (*curr_col_pos))) {
                    (*curr_row_pos)++;
                    found_valid_move = true;
                    return 3;
                }
            }
            if (move_direction == 4) {
                // move West (c-1): check if c-1 is valid
                if (isValidIndex(r, c, (*curr_row_pos), (*curr_col_pos)-1)) {
                    (*curr_col_pos)--;
                    found_valid_move = true;
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
             (&grid[i][j])->start_cell = false;
            (&grid[i][j])->next_node = NULL;
        }
    }
    printf("Grid/Board reset\n");
    return;
}