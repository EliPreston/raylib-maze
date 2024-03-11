    // Header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// External libraries
#include "raylib.h"
// My files
#include "cellgrid.c"




// Program Entry
int main(int argc, char *argv[]) {

    // Initialization

    // Defaults
    const int width = 1000;
    const int height = 850;
    const int node_distance = 5;
    int run_automation_flag = 0;
    int automation_counter = 0;

    int generation_count = 1;
    char gen_count_txt[] = "Generation #: ";
    char gen_count_int[20];
    snprintf(gen_count_int, sizeof(gen_count_int), "%d", generation_count);

    char *generation_num = malloc(strlen(gen_count_txt) + 20 + 1); // +1 for the null-terminator
    strcpy(generation_num, gen_count_txt);
    strcat(generation_num, gen_count_int);

     // Set up grid
    int num_rows = (height / node_distance);
    int num_cols = (width / node_distance);
    bool init = false;
    
    Cell** cells_grid = NULL;
    cells_grid = createCellGrid(width, height, node_distance);

    InitWindow(width, height, "Cellular Automota");
    SetTargetFPS(60);


    // Main game loop  ---------------
    while (!WindowShouldClose()) {
        automation_counter++;
        
        // Any update functions
        
        if (IsKeyPressed(KEY_R)) {
            run_automation_flag = 0;

            for (int idx = 0; idx < num_rows; idx++) free(cells_grid[idx]);
            free(cells_grid);
            cells_grid = createCellGrid(width, height, node_distance);

            free(generation_num);
            generation_count = 1;
            snprintf(gen_count_int, sizeof(gen_count_int), "%d", generation_count);
            generation_num = malloc(strlen(gen_count_txt) + 20 + 1); // +1 for the null-terminator
            strcpy(generation_num, gen_count_txt);
            strcat(generation_num, gen_count_int);  
        }

        if (IsKeyPressed(KEY_S)) {
            run_automation_flag = 1;
            printf("Starting automation - run_automation_flag set to 1\n");
        }

        if (IsKeyPressed(KEY_P)) {
            run_automation_flag = 0;
            printf("Pausing automation - run_automation_flag set to 0\n");
        }

        if (run_automation_flag == 1 && (automation_counter % 10 == 0)) {

            cells_grid = cellAutomationUpdateGrid(cells_grid, num_rows, num_cols);

            free(generation_num);
            generation_count++;
            snprintf(gen_count_int, sizeof(gen_count_int), "%d", generation_count);
            generation_num = malloc(strlen(gen_count_txt) + 20 + 1); // +1 for the null-terminator
            strcpy(generation_num, gen_count_txt);
            strcat(generation_num, gen_count_int);
        }
        

        // Drawing objects/entities
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            // Draw grid
            drawCellGrid(cells_grid, num_rows, num_cols);

            // Draw FPS and cell generation counter
            DrawRectangle(10, 10, 110, 50, WHITE);
            DrawFPS(20, 20);
            DrawText(generation_num, 20, 40, 10, RED);
            // DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint);
            

        EndDrawing();
    }



    for (int idx = 0; idx < num_rows; idx++) free(cells_grid[idx]);
    free(cells_grid);
    CloseWindow();

    return 0;
}