// typedef struct Wall {
//     Vector2 start_point;
//     Vector2 end_point;
// } Wall;


typedef struct GridCell {
    Vector2 top_left;
    Vector2 top_right;
    Vector2 bottom_left;
    Vector2 bottom_right;
    bool part_of_maze;
    struct GridCell *next_node;
} GridCell;