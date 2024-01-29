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
#define SCALE 4
#define CYCLE_INTERVAL 0.1 // in seconds ; at which interval the next cycle of life is triggered
#define GRID_W WINDOW_WIDTH/SCALE
#define GRID_H WINDOW_HEIGHT/SCALE

#define TRUE 1
#define FALSE 0

typedef struct {
	int 		current_grid;
	int 		cycle_running;
	int 		holding_left_mouse;
	int 		quit;
	int 		mouse_pos_x;
	int 		mouse_pos_y;
	Uint32 	current_time;
} state_t;

int 		is_in_grid(int x, int y);
void 		handle_event(state_t *state, float (*grid)[GRID_H], SDL_Event *event);

/* 			conway */
void 		next_cycle(float (*grid)[GRID_H], float (*grid2)[GRID_H]);


/* 			lenia */
void 		next_cycle_lenia(float (*grid)[GRID_H], float (*grid2)[GRID_H]);
double 	gaussian(int type, int x);
void 		init_lenia(float (*grid)[GRID_H]);
void 		display_gauss(SDL_Renderer *renderer);

#endif
