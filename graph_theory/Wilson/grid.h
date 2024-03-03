

typedef enum {
    NOT_PART_OF_MAZE,
    PART_OF_MAZE_WALK,
    PART_OF_MAZE_FINAL,
    START,
} CellState;

typedef struct GridCell {
    Vector2 top_left;
    bool start_cell;
    CellState cell_state;
    struct GridCell *next_node;
    int edges[4];
} GridCell;