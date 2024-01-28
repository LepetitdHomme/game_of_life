#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define RAND_MAX_FLOAT ((float)RAND_MAX + 1.0)
#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 1600
#define RATE 2
#define SPEED 0.9 // sec
#define GRID_W WINDOW_WIDTH/RATE
#define GRID_H WINDOW_HEIGHT/RATE

//conway
void 	next_cycle(float (*grid)[GRID_H], float (*grid2)[GRID_H]);
// lenia
void next_cycle_lenia(float (*grid)[GRID_H], float (*grid2)[GRID_H]);
double gaussian(int x);
void init_lenia(float (*grid)[GRID_H]);

#endif