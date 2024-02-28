// typedef struct Wall {
//     Vector2 start_point;
//     Vector2 end_point;
// } Wall;


typedef struct GridCell {
    Vector2 top_left;
    bool part_of_maze;
    bool part_of_final_maze;
    struct GridCell *next_node;
} GridCell;