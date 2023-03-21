#include <cstdint>
#include <cstring>
#include <iostream>
#include "conway.hpp"

static Cell **grid;
static std::uint32_t **intrm_buff;
static std::uint16_t GRID_WIDTH, GRID_HEIGHT, WIN_WIDTH, WIN_HEIGHT;
static uint8_t GRID_PX;

static inline bool init_life(void) {
//  return false;
  return !(std::rand()%2);
}

void init_grid(std::uint16_t win_dims, std::uint16_t grid_dims) {
  grid = new Cell*[grid_dims];
  intrm_buff = new std::uint32_t*[grid_dims];
  WIN_WIDTH = WIN_HEIGHT = win_dims;
  GRID_WIDTH = GRID_HEIGHT = grid_dims;
  for (int i=0; i < grid_dims; i++) {
    grid[i] = new Cell[grid_dims];
    intrm_buff[i] = new std::uint32_t[grid_dims];
  }
  GRID_PX = win_dims/grid_dims;

  Coord *temp = new Coord[3];
  // Corners
  //   - Top left
  temp[0] = new_coord(1, 0);
  temp[1] = new_coord(1, 1);
  temp[2] = new_coord(0, 1);
  grid[0][0].neighbors = temp;
  grid[0][0].num_neighbors = 3;
  grid[0][0].is_alive = grid[0][0].was_alive = init_life();
  intrm_buff[0][0] = ((grid[0][0].is_alive)?COL_ALIVE:COL_DEAD);
  //   - Top right
  temp = new Coord[3];
  temp[0] = new_coord(GRID_WIDTH-2, 0);
  temp[1] = new_coord(GRID_WIDTH-2, 1);
  temp[2] = new_coord(GRID_WIDTH-1, 1);
  grid[GRID_WIDTH-1][0].neighbors = temp;
  grid[GRID_WIDTH-1][0].num_neighbors = 3;
  grid[GRID_WIDTH-1][0].is_alive =
    grid[GRID_WIDTH-1][0].was_alive = init_life();
  intrm_buff[GRID_WIDTH-1][0] =
    ((grid[GRID_WIDTH-1][0].is_alive)?COL_ALIVE:COL_DEAD);
  //   - Bottom left
  temp = new Coord[3];
  temp[0] = new_coord(1, GRID_HEIGHT-1);
  temp[1] = new_coord(1, GRID_HEIGHT-2);
  temp[2] = new_coord(0, GRID_HEIGHT-2);
  grid[0][GRID_HEIGHT-1].neighbors = temp;
  grid[0][GRID_HEIGHT-1].num_neighbors = 3;
  grid[0][GRID_HEIGHT-1].is_alive =
    grid[0][GRID_HEIGHT-1].was_alive = init_life();
  intrm_buff[0][GRID_HEIGHT-1] = 
    ((grid[0][GRID_HEIGHT-1].is_alive) ? COL_ALIVE : COL_DEAD);

  
  //   - Bottom right
  temp = new Coord[3];
  temp[0] = new_coord(GRID_WIDTH-2, GRID_HEIGHT-1);
  temp[1] = new_coord(GRID_WIDTH-2, GRID_HEIGHT-2);
  temp[2] = new_coord(GRID_WIDTH-1, GRID_HEIGHT-2);
  grid[GRID_WIDTH-1][GRID_HEIGHT-1].neighbors = temp;
  grid[GRID_WIDTH-1][GRID_HEIGHT-1].num_neighbors = 3;
  grid[GRID_WIDTH-1][GRID_HEIGHT-1].is_alive =
    grid[GRID_WIDTH-1][GRID_HEIGHT-1].was_alive = init_life();
  intrm_buff[GRID_WIDTH-1][GRID_HEIGHT-1] =
    ((grid[GRID_WIDTH-1][GRID_HEIGHT-1].is_alive) ? COL_ALIVE : COL_DEAD);

  // Top and bottom edges 
  for (int x=1; x < GRID_WIDTH-1; ++x) {
    temp = new Coord[5];
    temp[0] = new_coord(x-1, 0);
    temp[1] = new_coord(x-1, 1);
    temp[2] = new_coord(x, 1);
    temp[3] = new_coord(x+1, 1);
    temp[4] = new_coord(x+1, 0);
    grid[x][0].neighbors = temp;
    grid[x][0].num_neighbors = 5;
    grid[x][0].is_alive = grid[x][0].was_alive = init_life();
    intrm_buff[x][0] = ((grid[x][0].is_alive) ? COL_ALIVE : COL_DEAD);
        
    temp = new Coord[5];
    temp[0] = new_coord(x-1, GRID_HEIGHT-1);
    temp[1] = new_coord(x-1, GRID_HEIGHT-2);
    temp[2] = new_coord(x, GRID_HEIGHT-2);
    temp[3] = new_coord(x+1, GRID_HEIGHT-2);
    temp[4] = new_coord(x+1, GRID_HEIGHT-1);
    grid[x][GRID_HEIGHT-1].neighbors = temp;
    grid[x][GRID_HEIGHT-1].num_neighbors = 5;
    grid[x][GRID_HEIGHT-1].is_alive =
      grid[x][GRID_HEIGHT-1].was_alive = init_life();
    intrm_buff[x][GRID_HEIGHT-1] =
      ((grid[x][GRID_HEIGHT-1].is_alive) ? COL_ALIVE : COL_DEAD);
  }

  // Left and right edges
  for (int y=1; y < GRID_HEIGHT-1; ++y) {
    temp = new Coord[5];
    temp[0] = new_coord(0, y-1);
    temp[1] = new_coord(1, y-1);
    temp[2] = new_coord(1, y);
    temp[3] = new_coord(1, y+1);
    temp[4] = new_coord(0, y+1);
    grid[0][y].neighbors = temp;
    grid[0][y].num_neighbors = 5;
    grid[0][y].is_alive = grid[0][y].was_alive = init_life();
    intrm_buff[0][y] = ((grid[0][y].is_alive) ? COL_ALIVE : COL_DEAD);

    temp = new Coord[5];
    temp[0] = new_coord(GRID_WIDTH-1, y-1); 
    temp[1] = new_coord(GRID_WIDTH-2, y-1);
    temp[2] = new_coord(GRID_WIDTH-2, y);
    temp[3] = new_coord(GRID_WIDTH-2, y+1);
    temp[4] = new_coord(GRID_WIDTH-1, y+1);
    grid[GRID_WIDTH-1][y].neighbors = temp;
    grid[GRID_WIDTH-1][y].num_neighbors = 5;
    grid[GRID_WIDTH-1][y].is_alive =
      grid[GRID_WIDTH-1][y].was_alive = init_life();
    intrm_buff[GRID_WIDTH-1][y] =
      ((grid[GRID_WIDTH-1][y].is_alive) ? COL_ALIVE : COL_DEAD);
  }

  // The rest
  for(int x = 1; x < GRID_WIDTH-1; ++x)
    for(int y = 1; y < GRID_HEIGHT-1; ++y) {
      temp = new Coord[8];
      temp[0] = new_coord(x-1, y-1);
      temp[1] = new_coord(x-1, y);
      temp[2] = new_coord(x-1, y+1);
      temp[3] = new_coord(x, y-1);
      temp[4] = new_coord(x, y+1);
      temp[5] = new_coord(x+1, y-1);
      temp[6] = new_coord(x+1, y);
      temp[7] = new_coord(x+1, y+1);
      grid[x][y].neighbors = temp;
      grid[x][y].num_neighbors = 8;
      grid[x][y].is_alive = grid[x][y].was_alive = init_life();
      intrm_buff[x][y] = ((grid[x][y].is_alive) ? COL_ALIVE : COL_DEAD);
    }
}

bool check_if_alive(int x, int y) {
  int num_alive = 0;
  for (int i=0; i < grid[x][y].num_neighbors; ++i)
    if (grid[grid[x][y].neighbors[i].x][grid[x][y].neighbors[i].y].was_alive) 
      ++num_alive;
  grid[x][y].is_alive = 
    ((grid[x][y].was_alive && num_alive==2) || num_alive==3);
  return grid[x][y].is_alive?1:0;
}

void update_grid_and_display(sf::Image &px_buff) {

  for (int x=0; x < GRID_WIDTH; x++)
    for (int y=0; y < GRID_HEIGHT; y++)
      intrm_buff[x][y] = (check_if_alive(x, y))?COL_ALIVE:COL_DEAD;
  
  for (int x = 0; x < GRID_WIDTH; x++)
    for (int y = 0; y < GRID_HEIGHT; y++) {
      int xoff = x*GRID_PX,
          yoff = y*GRID_PX,
          xlim = xoff+GRID_PX,
          ylim = yoff+GRID_PX;
      grid[x][y].was_alive = grid[x][y].is_alive;
      sf::Color cell_col(intrm_buff[x][y]);
      for ( ; xoff < xlim; ++xoff) {
        for ( ; yoff < ylim; ++yoff) {
          px_buff.setPixel(xoff, yoff, cell_col);
        }
        yoff = y*GRID_PX;
      }
    }
}


void dealloc_mem(void) {
  std::cout << "Freeing dynamically alloc'd mem!\n";
  for (int x = 0; x < GRID_WIDTH; ++x)
    for (int y=0; y < GRID_HEIGHT; ++y)
      delete [] grid[x][y].neighbors;
  for (int i = 0; i < GRID_WIDTH; i++) {
      delete [] grid[i];
      delete [] intrm_buff[i];
  }
  delete [] grid;
  delete [] intrm_buff;
}

static bool is_valid_grid_coord(int x, int y) {
  std::cout << "Mouse move: x = " << x << ", y = " << y << '\n';
  return (x > -1 && x < WIN_WIDTH && y > -1 && y < WIN_HEIGHT);
}

static void turn_alive_at(int x, int y) {
  x/=GRID_PX;
  y/=GRID_PX;

  grid[x][y].is_alive = grid[x][y].was_alive = 1;
  intrm_buff[x][y] = COL_ALIVE;
}

static void turn_dead_at(int x, int y) {
  x/=GRID_PX;
  y/=GRID_PX;
  

  grid[x][y].is_alive = grid[x][y].was_alive = 0;
  intrm_buff[x][y] = COL_DEAD;
}

void set_grid_state(int x, int y, bool alive) {
  if (!is_valid_grid_coord(x, y))
    return;
  (alive)?turn_alive_at(x, y):turn_dead_at(x, y);

}

void update_paused_grid(sf::Image &px_buff) {
  for (int i = 0; i < GRID_WIDTH; ++i)
    for (int j = 0; j < GRID_HEIGHT; ++j) {
      int x = i*GRID_PX,
        y = j*GRID_PX,
        xlim = x+GRID_PX,
        ylim = y+GRID_PX;
      sf::Color cell_col(intrm_buff[i][j]);
      for ( ; x < xlim; ++x) {
        for( ; y < ylim; ++y) {
          px_buff.setPixel(x, y, cell_col);
        }
        y = j*GRID_PX;
      }
    }
}
