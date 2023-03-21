#include <SFML/Main.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include "conway.hpp"
#include "render.hpp"

Event_Cues cues = {
  false,
  false,
  false
};

static sf::RenderWindow win;



int main(int argc, char *argv[]) {
  std::uint16_t win_size = DEF_WIN_DIMS, grid_size = DEF_GRID_DIMS;
  if (argc!=1) {
    bool invalid_arg;
    for (int i = 1; i < argc; i++) {
      invalid_arg = false;
      if (argv[i][0] == '-') {
        char *temp;
        switch (argv[i][1]) {
          case '-':

            if(!std::strcmp(argv[i], "--help")) {
              std::cout << "Help: Usage = " << argv[0] << "<options>\n"
              << "\tOptions:\n"
              << "\t\t-W <Window Size in pixels> (or --window_size=<...>)\n"
              << "\t\t-G <Cell Grid Size> (or --grid_size=<...>)\n"
              << "\t\t-h (or --help) for help menu.\n";
            win.close();
            exit(EXIT_SUCCESS);
            }
            if (!std::strncmp(argv[i], "--win_size=", sizeof(char)*11)) {
              temp = argv[i] + 11;
              if (temp[0]=='\0') invalid_arg = true;
              int size;
              for (size = 0; temp[size]!='\0'; size++)
                if (temp[size] < '0' && temp[size] > '9') invalid_arg = true;
              if (invalid_arg) {
                std::cerr << "Error: \"" << temp << "\" cannot be parsed into "
                  << "a number. (Contains non-numeric characters).\n"
                  << "Using default window size of " << DEF_WIN_DIMS << '\n';
                continue;
              }

              win_size = std::atoi(temp);
              continue;
            } else if(!std::strncmp(argv[i], "--grid_size=", sizeof(char)*12)) {
              temp = argv[i] + 12;
              if (temp[0]=='\0') invalid_arg = true;
              int size;
              for (size = 0; temp[size]!='\0'; size++)
                if (temp[size] < '0' && temp[size] > '9') invalid_arg = true;
              if (invalid_arg) {
                std::cerr << "Error: \"" << temp << "\" cannot be parsed into "
                  << "a number. (Contains non-numeric characters).\n"
                  << "Using default grid size of " << DEF_GRID_DIMS << '\n';
                continue;
              }
              grid_size = std::atoi(temp);
              continue;
            } else {
              std::cerr << "Error: \"" << argv[i] << "\" is an unknown command "
                << "option.\n";
              continue;
            }
            break;
          case 'W':
            temp = argv[i+1];
            for (int j = 0; temp[j]!='\0'; j++)
              if (temp[j] < '0' && temp[j] > '9') {
                invalid_arg = true;
                break;
              }
            if (invalid_arg) {
              std::cerr << "Error: \"" << temp << "\" cannot be parsed into "
                << "a number. (Contains non-numeric characters).\n"
                << "Using default win size of " << DEF_WIN_DIMS << '\n';
              continue;
            }
            win_size = std::atoi(temp);
            i++;
            break;
          case 'G':
            temp = argv[i+1];
            for (int j = 0; temp[j]!='\0'; j++)
              if (temp[j] < '0' && temp[j] > '9') {
                std::cerr << "Error: \"" << temp << "\" cannot be parsed into "
                  << "a number. (Contains non-numeric characters).\n"
                  << "Using default grid size of " << DEF_GRID_DIMS << '\n';
                continue;
              }
            grid_size = std::atoi(temp);
            i++;
            continue;
          case 'h':
            std::cout << "Help: Usage = " << argv[0] << "<options>\n" 
              << "\tOptions:\n"
              << "\t\t-W <Window Size in pixels> (or --window_size=<...>)\n"
              << "\t\t-G <Cell Grid Size> (or --grid_size=<...>)\n"
              << "\t\t-h (or --help) for help menu.\n";
            win.close();
            exit(EXIT_SUCCESS);
          default:
            std::cerr << "Error: \"" << temp << "\" is not a valid command " 
              << "option.\nUse -h (or --help) to see help menu.\n";
            win.close();
            exit(EXIT_FAILURE);
            break;
        }
      }
    }
  }
  win.create(sf::VideoMode(win_size, win_size), "Conways Game of Life");
  seed_stdlib_rng();
  init_buffers(win_size, grid_size);
  atexit(exit_sequence);
  while (win.isOpen()) {
    if (cues.sim_on)
      step_simulator();
    else
      update_paused_buffer();
    poll_evs(win, cues);
    display_and_sleep(win);
  }
  exit(EXIT_SUCCESS);
}

void exit_sequence(void) {
  win.close();
  dealloc_mem();
}
