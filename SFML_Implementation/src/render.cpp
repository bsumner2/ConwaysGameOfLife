#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Err.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include <csignal>
#include <ctime>
#include <unistd.h>
#include "conway.hpp"
#include "render.hpp"


sf::Image pbuff;
sf::Texture buff_displayer;



void signal_handler(int signum) {
  std::cout << "Interrupt signal intercepted (signal number: " << signum <<
    ").\nStarting deallocation sequences.\n";
  exit(EXIT_SUCCESS);
}

void seed_stdlib_rng(void) {
  // Ensure if interrupt signal recieved, dynamically allocated memory is still
  // deallocated.
  std::signal(SIGINT, signal_handler);
  std::time_t currtime = std::time(nullptr);
  std::srand(static_cast<unsigned long>(currtime));
}

void init_buffers(std::uint16_t win_size, std::uint16_t grid_size) {
  buff_displayer.create(win_size, win_size);
  pbuff.create(win_size, win_size);
  init_grid(win_size, grid_size);
}

void update_paused_buffer(void) {
  update_paused_grid(pbuff);
  buff_displayer.update(pbuff);
}

void step_simulator(void) {
    update_grid_and_display(pbuff);
    buff_displayer.update(pbuff);
}

void display_and_sleep(sf::RenderWindow &win) {
  sf::Sprite spr;
  spr.setTexture(buff_displayer);
  win.clear();
  win.draw(spr);
  win.display();
  usleep(UPDATE_INTERVAL);
}

static inline void
handle_keypresses(sf::Event::KeyEvent &details, Event_Cues &ev_cues) {

  switch (details.code) {
    case sf::Keyboard::Space:
      ev_cues.sim_on = !(ev_cues.sim_on);
      ev_cues.draw_mode =
        ev_cues.erase_mode = false;
      break;
    case sf::Keyboard::D:
      ev_cues.draw_mode = !(ev_cues.draw_mode);
      ev_cues.sim_on = 
        ev_cues.erase_mode = false;
      break;
    case sf::Keyboard::E:
      ev_cues.erase_mode = !(ev_cues.erase_mode);
      ev_cues.sim_on =
        ev_cues.draw_mode = false;
    default:
      break;
  }
}


static inline void
handle_mouse_movement(int x_pos, int y_pos, bool set_state) {
  set_grid_state(x_pos, y_pos, set_state); 
}

void poll_evs(sf::RenderWindow &win, Event_Cues &ev_cues) {
  sf::Event ev;
  while (win.pollEvent(ev)) {
    switch (ev.type) {
      case sf::Event::Closed:
        exit(EXIT_SUCCESS);
        break;
      case sf::Event::KeyPressed:
        handle_keypresses(ev.key, ev_cues);
        break;
      case sf::Event::MouseMoved:
        if (ev_cues.sim_on || (!ev_cues.draw_mode && !ev_cues.erase_mode))
          break;
        handle_mouse_movement(ev.mouseMove.x, ev.mouseMove.y,
            ev_cues.draw_mode);
      default:
        break;
    }
  }
}


