#ifndef _RENDER_HPP_
#define _RENDER_HPP_

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cstdint>
struct Event_Cues
{
  bool sim_on, draw_mode, erase_mode;
};

void signal_handler(int);
void exit_sequence(void);
void seed_stdlib_rng(void);
void init_buffers(std::uint16_t, std::uint16_t);
void step_simulator(void);
void update_paused_buffer(void);
void display_and_sleep(sf::RenderWindow&);
void poll_evs(sf::RenderWindow&, Event_Cues&);



#endif // _RENDER_HPP_
