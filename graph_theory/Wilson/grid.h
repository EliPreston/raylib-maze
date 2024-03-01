

typedef enum {
    NOT_PART_OF_MAZE,
    PART_OF_MAZE_WALK,
    PART_OF_MAZE_FINAL,
} CellState;

typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST,
    NONE
} ExitDirection;

typedef struct GridCell {
    Vector2 top_left;
    CellState cell_state;      // bool part_of_maze; // bool part_of_final_maze;
    struct GridCell *next_node;
    ExitDirection cell_exit_direction;
} GridCell;