#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

#include "grid.h"


// Function declarations
void drawNorthWall(GridCell *curr_cell, int node_distance);
void drawEastWall(GridCell *curr_cell, int node_distance);
void drawSouthWall(GridCell *curr_cell, int node_distance);
void drawWestWall(GridCell *curr_cell, int node_distance);


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
    Vector2 top_left, bottom_left, top_right, bottom_right;
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {

            curr_cell = &grid[i][j];
            top_left = curr_cell->top_left;

            if (curr_cell->cell_state == PART_OF_MAZE_FINAL) {
                // DrawRectangleV(top_left, (Vector2) {node_distance, node_distance}, GREEN);


                if ((curr_cell->cell_exit_direction != NORTH && curr_cell->cell_entrance_direction != NORTH))
                    drawNorthWall(curr_cell, node_distance);

                if (curr_cell->cell_exit_direction != EAST && curr_cell->cell_entrance_direction != EAST)
                    drawEastWall(curr_cell, node_distance);

                if ((curr_cell->cell_exit_direction != SOUTH && curr_cell->cell_entrance_direction != SOUTH)) 
                    drawSouthWall(curr_cell, node_distance);

                if (curr_cell->cell_exit_direction != WEST && curr_cell->cell_entrance_direction != WEST)
                    drawWestWall(curr_cell, node_distance);

            } else { 
                DrawRectangleV(top_left, (Vector2) {node_distance, node_distance}, BLACK); 
                // DrawRectangleLines(top_left.x, top_left.y, node_distance, node_distance, BLACK);  
            }
            
        }
    }

    return 0;
}



// void drawEntrancesExits(GridCell *curr_cell, int node_distance) {
    
//     if ((curr_cell->cell_exit_direction != NORTH && curr_cell->cell_entrance_direction != NORTH)) {
//         drawNorthWall(curr_cell, node_distance);
//     }

//     if (curr_cell->cell_exit_direction != EAST && curr_cell->cell_entrance_direction != EAST) {
//         drawEastWall(curr_cell, node_distance);
//     }

//     if ((curr_cell->cell_exit_direction != SOUTH && curr_cell->cell_entrance_direction != SOUTH)) {
//         drawSouthWall(curr_cell, node_distance);
//     }

//     if (curr_cell->cell_exit_direction != WEST && curr_cell->cell_entrance_direction != WEST) {
//         drawWestWall(curr_cell, node_distance);
//     }
// }


void drawNorthWall(GridCell *curr_cell, int node_distance) {
    Vector2 top_left = (*curr_cell).top_left;
    Vector2 top_right = (Vector2) { top_left.x + node_distance, top_left.y };
    DrawLineV(top_left, top_right, BLACK);
}

void drawSouthWall(GridCell *curr_cell, int node_distance) {
    Vector2 top_left = (*curr_cell).top_left;
    Vector2 bottom_left = (Vector2) { top_left.x, top_left.y + node_distance };
    Vector2 bottom_right = (Vector2) { top_left.x + node_distance, top_left.y + node_distance };
    DrawLineV(bottom_left, bottom_right, BLACK);

}

void drawEastWall(GridCell *curr_cell, int node_distance) {
    Vector2 top_left = (*curr_cell).top_left;
    Vector2 top_right = (Vector2) { top_left.x + node_distance, top_left.y };
    Vector2 bottom_right = (Vector2) { top_left.x + node_distance, top_left.y + node_distance };
    DrawLineV(top_right, bottom_right, BLACK);
}

void drawWestWall(GridCell *curr_cell, int node_distance) {
    Vector2 top_left = (*curr_cell).top_left;
    Vector2 bottom_left = (Vector2) { top_left.x, top_left.y + node_distance };
    DrawLineV(top_left, bottom_left, BLACK);
}