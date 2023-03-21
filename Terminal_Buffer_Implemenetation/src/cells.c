// Copyright (C) 2023 Burton O Sumner
#include "conway.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

char BUFF[BUFF_SIZE];
Cell grid[WIDTH][HEIGHT];

static void init_grid_elem(int i, int j, Coordinate *static_arr, int arr_size)
{
    grid[i][j].pos = COORD_INST(i, j);
    grid[i][j].neighbors = malloc(sizeof(Coordinate)*arr_size); 
    for(int k=0;  k< arr_size;k++) {
        grid[i][j].neighbors[k].x = static_arr[k].x;
        grid[i][j].neighbors[k].y = static_arr[k].y;
    }

    grid[i][j].num_neigbors = arr_size;
    

    grid[i][j].alive = grid[i][j].was_alive = !(rand()%2);
}

static uint8 check_if_alive(int x, int y)
{
    uint8 num_alive = 0;
    for(int i=0; i < grid[x][y].num_neigbors; i++)
        if(grid[grid[x][y].neighbors[i].x][grid[x][y].neighbors[i].y].was_alive)
            num_alive++;
    grid[x][y].alive =
        ((grid[x][y].was_alive && num_alive==2) || num_alive==3)?1:0;
        return grid[x][y].alive;
}


void init_grid(void)
{
    time_t t = time(NULL);
    srand(t);
    // Init top corners
    init_grid_elem(0, 0, 
            (Coordinate[3]){
                    COORD_INST(1, 0),
                    COORD_INST(1, 1),
                    COORD_INST(0, 1)}, 3);
    init_grid_elem(WIDTH-1, 0, 
            (Coordinate[3]){
                    COORD_INST(WIDTH-2, 0),
                    COORD_INST(WIDTH-2, 1),
                    COORD_INST(WIDTH-1, 1)}, 3);
    // Init bottom corners
    init_grid_elem(0, HEIGHT-1,
            (Coordinate[3]){
                COORD_INST(1, HEIGHT-1),
                COORD_INST(1, HEIGHT-2),
                COORD_INST(0, HEIGHT-2)}, 3);
    init_grid_elem(WIDTH-1, HEIGHT-1,
            (Coordinate[3]){
                COORD_INST(WIDTH-2, HEIGHT-1),
                COORD_INST(WIDTH-2, HEIGHT-2),
                COORD_INST(WIDTH-1, HEIGHT-2)}, 3);
    /* Loop through and init cells in both 
     * top and bottom edges in one unrolled loop. */
    for (int x=1; x < WIDTH-1; x++)
    {
        init_grid_elem(x, 0, 
                (Coordinate[5]){
                    COORD_INST(x-1, 0),
                    COORD_INST(x-1, 1),
                    COORD_INST(x, 1),
                    COORD_INST(x+1, 0),
                    COORD_INST(x+1, 1)}, 5);
        init_grid_elem(x, HEIGHT-1, 
                (Coordinate[5]){
                    COORD_INST(x-1, HEIGHT-1),
                    COORD_INST(x-1, HEIGHT-2),
                    COORD_INST(x, HEIGHT-2),
                    COORD_INST(x+1, HEIGHT-1),
                    COORD_INST(x+1, HEIGHT-2)}, 5);
    }
    /* Loop through and init cells in both
     * left and right edges in one unrolled loop. */
    for(int y=1; y<HEIGHT-1; y++) {
        init_grid_elem(0, y,
                (Coordinate[5]){
                    COORD_INST(0, y-1),
                    COORD_INST(1, y-1),
                    COORD_INST(1, y),
                    COORD_INST(0, y+1),
                    COORD_INST(1, y+1)}, 5);
        init_grid_elem(WIDTH-1, y,
                (Coordinate[5]){
                    COORD_INST(WIDTH-1, y-1),
                    COORD_INST(WIDTH-2, y-1),
                    COORD_INST(WIDTH-2, y),
                    COORD_INST(WIDTH-1, y+1),
                    COORD_INST(WIDTH-2, y+1)}, 5);
    }
    
    // Init all middle pieces
    
    for(int y = 1; y < HEIGHT-1; y++)
        for(int x = 1; x < WIDTH-1; x++)
            init_grid_elem(x, y,
                    (Coordinate[8]){
                        COORD_INST(x-1, y-1),
                        COORD_INST(x-1, y),
                        COORD_INST(x-1, y+1),
                        COORD_INST(x, y-1),
                        COORD_INST(x, y+1),
                        COORD_INST(x+1, y-1),
                        COORD_INST(x+1, y),
                        COORD_INST(x+1, y+1)}, 8);
}



void print_and_update_grid(void)
{

    memset(BUFF, 32, BUFF_SIZE);
    for(int x=0; x<WIDTH; x++)
        for(int y=0; y<HEIGHT;y++)
        {
            BUFF[INDEX_P(x, y)] = (check_if_alive(x, y))?ALIVE:DEAD;

        }
    printf(RESET_CURSOR); 
    for (int y=0; y<HEIGHT;y++) {
        for (int x=0; x<WIDTH;x++) {
            grid[x][y].was_alive = grid[x][y].alive;
            putchar(BUFF[INDEX_P(x, y)]);
        }
        putchar(10);
    }
}


void dealloc_neighbor_trackers(void)
{
    printf("\nFreed dynamically allocated memory!\n");
    for (int x = 0; x < WIDTH;x++)
        for (int y = 0; y < HEIGHT; y++)
            free(grid[x][y].neighbors);
}
