// Copyright (C) 2023 Burton O Sumner
#include "conway.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
uint8 cont = 1;
int update_interval = UPDATE_INTERVAL;

extern int strcmp(const char *, const char *);

void signal_handler(int sigint) {
  cont = 0;
}


int main(int argc, char *argv[]) {
  if (argc > 1 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) {
    printf("Help menu: Usage = %s <framerate (default: 60)>", argv[0]);
    printf("\tTo escape without causing a memory leak, use SIGINT. (Ctrl+C\n");
    printf("\ton any POSIX-compliant terminal.)\n");
    exit(EXIT_SUCCESS);
  } else if (argc > 1) {
    for (int i = 0; argv[1][i]!='\0'; ++i)
      if (argv[1][i] < '0' || argv[1][i] > '9') {
        fprintf(stderr, "Error: framerate arg, (arg no. 1 = %s)\n", argv[1]);
        fprintf(stderr, "\tCannot be parsed into a numeric value.\n");
        exit(EXIT_FAILURE);
      }
    // Formula derivation: update_interval (in microseconds) = 
    // 10^6 microseconds/second / x frames/second = (10^6/x) microseconds/frame
    update_interval = 1000000/(atoi(argv[1]));
  }
  signal(SIGINT, signal_handler);
  init_grid();
  atexit(dealloc_neighbor_trackers);
  printf(CLR_SCR);
  for(;cont;) {
    print_and_update_grid();
    usleep(update_interval);
  }
    exit(EXIT_SUCCESS);
}
