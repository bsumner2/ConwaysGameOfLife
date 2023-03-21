#ifndef _CONWAY_HPP_
#define _CONWAY_HPP_
#include <SFML/Graphics/Image.hpp>
#include <cstdint>
#include <cstdlib>

// -REGION: If any one of these changes, then all have to be adjusted to reflect
//          The changes of any derivative macros. 
//              E.G if GRID_WIDTH and GRID_HEIGHT change, then GRID_PX needs to
//              be reset to equal WIN_(WIDTH|HEIGHT)/GRID_(WIDTH|HEIGHT)


#define DEF_GRID_DIMS 256
#define DEF_WIN_DIMS 512



#define COL_ALIVE 0x00FFFFFF
#define COL_DEAD  0x000000FF

//#define UPDATE_INTERVAL 6061
// Default update interval is such that framerate cap is 60 fps
#define UPDATE_INTERVAL 16667

#define alloc_array(type, size) (static_cast<type*>(malloc(sizeof(type)*size)))

struct Coord {
  int x, y;
}; 
 

struct Cell {
  Coord *neighbors;
  uint8_t num_neighbors;
  bool is_alive, was_alive;
};

//#define new_coord(a, b) ((Coord){a, b})
static inline Coord new_coord(int x, int y) {return {x, y};}

void init_grid(std::uint16_t, std::uint16_t);
void update_grid_and_display(sf::Image&);
void dealloc_mem(void);
void set_grid_state(int, int, bool);
void update_paused_grid(sf::Image&);

#endif // _CONWAY_HPP_
