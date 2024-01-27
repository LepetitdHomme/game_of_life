#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define RAND_MAX_FLOAT ((float)RAND_MAX + 1.0)
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define RATE 4
#define SPEED 0.1 // sec
#define GRID_W WINDOW_WIDTH/RATE
#define GRID_H WINDOW_HEIGHT/RATE

//conway
void 	next_cycle(int (*grid)[GRID_H], int (*grid2)[GRID_H]);

#endif