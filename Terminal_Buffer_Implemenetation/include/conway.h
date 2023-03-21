// Copyright (C) 2023 Burton O Sumner
#ifndef CONWAY_H_
#define CONWAY_H_
/**
 * @brief Clears screen and puts cursor back at start*/
#define CLR_SCR "\x1b[2J"
#define RESET_CURSOR "\x1b[d"

/** 
 * Total buffer size. */
#define BUFF_SIZE 1760

/** 
 * Buffer height. */
#define HEIGHT    22

/**
 * Buffer width. */
#define WIDTH     80




#define ALIVE '#'
#define DEAD  ' '


/**
 * Ease of access macro for getting index via cartesian coordinates 
 * within single subscripted buffer array. */
#define INDEX_P(x, y) (x+(WIDTH*y))
#define INDEX_C(coord)  (coord.x + (coord.y*WIDTH))

#define COORD_INST(x_, y_) ((Coordinate){.x = x_, .y = y_})
#define UPDATE_INTERVAL (16667)

typedef unsigned char uint8;

typedef struct
{
    int x, y;
} Coordinate;


typedef struct{
    Coordinate pos;
    Coordinate *neighbors;
    int num_neigbors;
    uint8 alive, was_alive;
} Cell;

void init_grid(void);
void print_and_update_grid(void);
void dealloc_neighbor_trackers(void);

#endif // CONWAY_H_
