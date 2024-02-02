#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> 

#define RAND_MAX_FLOAT ((float)RAND_MAX + 1.0)
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT ((WINDOW_WIDTH * 9) / 16)
#define SCALE 4
#define CYCLE_INTERVAL 0.1 // in seconds ; at which interval the next cycle of life is triggered
#define GRID_W WINDOW_WIDTH/SCALE
#define GRID_H WINDOW_HEIGHT/SCALE

#define MENU_WIDTH WINDOW_WIDTH / 5
#define MENU_ANIMATION_SPEED WINDOW_WIDTH / 100
#define VISIBLE_TEXT_SIZE 10

#define TRUE 1
#define FALSE 0

typedef struct {
	SDL_Window 		*window;
	SDL_Renderer 	*renderer;
	SDL_Event 		Event;
} sdl_t;

typedef struct {
	TTF_Font 			*font;
} menu_t;

typedef struct {
	int 			current_grid;
	int 			cycle_running;
	int 			cycle_count;
	int 			cells_count;
	int 			holding_left_mouse;
	int 			menu_opened;
	int 			menu_pos_x;
	SDL_Rect 	menu_button;
	int 			quit;
	int 			mouse_pos_x;
	int 			mouse_pos_y;
	Uint32 		current_time;
} state_t;

/* 			grid */
void 		reinitialize_grid(float (*grid)[GRID_H]);
int 		draw_current_grid(SDL_Renderer *renderer, float grid[GRID_W][GRID_H]);
int 		is_in_grid(int x, int y);

/* 			menu */
void 		init_menu(sdl_t *sdl, menu_t *menu);
void 		free_menu(menu_t *menu);
void 		open_menu(state_t *state);
void 		draw_menu(SDL_Renderer *renderer, menu_t *menu, state_t *state);

/* 			events */
void 		handle_event(state_t *state, float (*grid)[GRID_H], SDL_Event *event);
void 		handle_menu_event(menu_t *menu, state_t *state, SDL_Event *event);

/* 			conway */
void 		next_cycle(float (*grid)[GRID_H], float (*grid2)[GRID_H]);

/* 			lenia */
void 		next_cycle_lenia(float (*grid)[GRID_H], float (*grid2)[GRID_H]);
double 	gaussian(int type, int x);
void 		init_lenia(float (*grid)[GRID_H]);
void 		display_gauss(SDL_Renderer *renderer);

#endif
