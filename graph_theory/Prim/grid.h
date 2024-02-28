typedef struct Vertex {
    Vector2 position; // upper left hand corner of square/cell -> use this to calculate center position of node (what the square surrounds), and the other 4 corners of the cell surrounding the vertex
    int dimension;
} Vertex;

typdef struct Edge {
    bool part_of_maze;
    Vertex *v1;
    Vertex *v2;
} Edge;