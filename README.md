# Conway's Game of Life

A zero-player game that relies on the initial conditions to generate all sorts of cool patterns
via the simulation rules that allow for the formation of cellular automata. These are the different
implementations I made of Conway's Game of Life, using the same basic idea and porting it to different
graphical engines and even one that uses the terminal itself as a graphical medium via escape sequences
and an ASCII-based buffer.

Credits:
- The concept behind Conways Game of Life, as its namesake suggests,
  is the brainchild of The British mathematician, John Conway.
- Special thanks to the SFML dev team for their game-making API that I used for one implementation.
- The code is written by myself, Burton O Sumner

## SFML implementation

This version was written by me in C++ and it uses the SFML library, a game-making API written for C++.
The game starts with a randomly-generated initial conditions board. This can be changed by setting the
static inline boolean function, init_life() to return 0 if you want to start an all-dead (empty) board,
or change the modulus operation's right hand operand, in the return statement, to whatever you want the
probability that a given pixel's initial state is alive to be. The rng is seeded at runtime with the
current time since the universal time epoch.

### Requirements

.- SFML
.- Unix-like OS (Ideally, a GNU/Linux OS)

### Usage

Command: [executable] [args]
    Valid args:      
        "-W <window size>" Window size option flag followed by window size as an integer.
          OR                 Only a single dimension (unit = pixels) is accepted in order to keep
        "--win_size=<..>"  the window shape square.
.-----------------------------------------------------------------------------------------------------
        "-G <grid size>"   Grid size option flag followed by grid size as an integer.
          OR                 Only a single dimension (unit = cells) is accepted in order to keep
          "--grid_size=<..>" the grid shape square.
.-----------------------------------------------------------------------------------------------------
        - "-h" OR "--help"   Displays the help menu.
.-----------------------------------------------------------------------------------------------------
In-Game Controls:
    .- Spacebar = Toggle the simulation to be on or off.
    .- D-key = Toggle draw mode.  (Sets simulation mode and erase mode to ff)
    .- E-key = Toggle erase mode. (Sets simulation mode and draw mode to off)
    .- Mouse Movement = Use mouse cursor to draw/erase living cells from the grid,
                        when in draw/erase mode respectively.
.-----------------------------------------------------------------------------------------------------
Exit Safely (Ways to ensure memory is deallocated properly):
    .- Can quit by closing the window as you normally would.
    .- Or by pressing Ctrl+C in the terminal used to exec the program.
.-----------------------------------------------------------------------------------------------------

## ASCII Graphics/Terminal implementation

This version was written in C and uses escape sequences to turn the terminal itself into a graphical display
that can display an ASCII display buffer.

### Requirements

- Unix-like OS (Ideally a GNU/Linux or a POSIX-compliant terminal emulator/tty)

### Usage
Command: [executable] [arg]
    Valid arg options:
    "-h" OR "--help" To see the help menu.
.-----------------------------------------------------------------------------------------------------
    "<framerate>" Framerate given as a numeric string. The string is parsed and used to calculate the
                  sleep interval (the time interval between each display update).
.-----------------------------------------------------------------------------------------------------
Exiting Safely:
    .- Can quit by using Ctrl+C in a POSIX-compliant TTY screen or terminal emulator, as the
       program is designed to intercept the SIGINT signal in order to enter ensure the program enters the
       exit callback function that deallocates all dynamically-allocated memory blocks before exiting the
       program as a whole.
