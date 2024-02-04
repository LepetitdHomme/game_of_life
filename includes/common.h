#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> 

#define WINDOW_WIDTH 1280 // >= 1000 for menu !!
#define WINDOW_HEIGHT ((WINDOW_WIDTH * 9) / 16)
#define SCALE 2
#define CYCLE_INTERVAL 0.04 // in seconds ; at which interval the next cycle of life is triggered
#define GRID_W WINDOW_WIDTH/SCALE
#define GRID_H WINDOW_HEIGHT/SCALE

#define MENU_WIDTH WINDOW_WIDTH / 5
#define MENU_ANIMATION_SPEED WINDOW_WIDTH / 100
#define VISIBLE_TEXT_SIZE 10

#define LENIA_THRESHOLD 10.0
#define KERNEL_SIZE 3
#define NUM_GROWTH_PRIMORDIA 10
#define NUM_GROWTH_CONWAY 9

#define TRUE 1
#define FALSE 0

enum Rule {
	CONWAY,
	PRIMORDIA,
	LENIA
};

typedef struct {
	SDL_Window 		*window;
	SDL_Renderer 	*renderer;
	SDL_Event 		Event;
} sdl_t;

typedef struct {
	TTF_Font 			*font;
} menu_t;

typedef struct {
  float   **data;
  int     radius;
} kernel_t;

typedef struct {
	int 			current_grid;
	int 			cycle_running;
	int 			cycle_count;
	int 			cells_count;
	int 			holding_left_mouse;
	int 			menu_opened;
	int 			menu_pos_x;
	SDL_Rect 	menu_button;
	SDL_Rect 	reset_button;
	SDL_Rect 	pause_button;
	SDL_Rect 	conway_button;
	SDL_Rect 	primordia_button;
	SDL_Rect 	lenia_button;
	float 		growth_primordia[NUM_GROWTH_PRIMORDIA];
	SDL_Rect 	primordia_graph_buttons[NUM_GROWTH_PRIMORDIA];
  int       survive_conway[NUM_GROWTH_CONWAY];
  int       born_conway[NUM_GROWTH_CONWAY];
  SDL_Rect  survive_conway_graph_buttons[NUM_GROWTH_CONWAY][2];
  SDL_Rect  born_conway_graph_buttons[NUM_GROWTH_CONWAY][2];
  int       kernel[KERNEL_SIZE][KERNEL_SIZE];
  SDL_Rect  kernel_buttons[KERNEL_SIZE][KERNEL_SIZE];
  kernel_t  kernel_lenia;
	int 			quit;
	int 			mouse_pos_x;
	int 			mouse_pos_y;
	Uint32 		current_time;
	enum Rule current_rule;
} state_t;

/*      initialization */
void    init_game_state(state_t *state);
void    init_sdl(sdl_t *sdl);
void 		init_menu(sdl_t *sdl, menu_t *menu);
void    init_conway_growth(state_t *state);
void 		init_primordia(float (*grid)[GRID_H]);
void    init_primordia_growth(state_t *state);
void 		init_lenia(float (*grid)[GRID_H]);
void    init_kernel(state_t *state);
void    init_kernel_lenia(state_t *state, int radius);
void 		reinitialize_grid(float (*grid)[GRID_H]);

/* 			grid */
void 		draw_current_grid(SDL_Renderer *renderer, float grid[GRID_W][GRID_H]);
int 		is_in_grid(int x, int y);

/* 			events */
int 		mouse_on_button(SDL_Rect button, state_t *state);
void 		handle_event(state_t *state, float (*grid)[GRID_H], SDL_Event *event);

/* 			conway */
int     *get_conway_survive();
int     *get_conway_born();
int 		next_cycle(float (*grid)[GRID_H], float (*grid2)[GRID_H], state_t *state);

/* 			primordia */
float   *get_primordia_growth();
int 		next_cycle_primordia(float (*grid)[GRID_H], float (*grid2)[GRID_H], state_t *state);

/* 			lenia */
int 		next_cycle_lenia(float (*grid)[GRID_H], float (*grid2)[GRID_H], state_t *state);
double 	gaussian(int type, int x);
void 		display_gauss(SDL_Renderer *renderer);

/*      kernel */
int     *get_kernel();
int     updating_kernel(state_t *state);
void    draw_kernel(SDL_Renderer *renderer, menu_t *menu, state_t *state, SDL_Rect *quad);

/* 			compute */
float 	gaussianKernel(int i, int j);
float 	conwayKernel(int i, int j);
float 	vonNeumannKernel(int i, int j);
float 	mooreKernel(int i, int j);
float 	random_float(float lower_bound, float upper_bound);

/* 			menu */
void 		free_menu(menu_t *menu);
void 		open_menu(state_t *state);
void    render_text(SDL_Renderer *renderer, menu_t *menu, char *text, SDL_Rect *rect, SDL_Color color);
void 		draw_menu(SDL_Renderer *renderer, menu_t *menu, state_t *state);

/* 			menu_primordia */
int 		updating_primordia_graph(state_t *state);
void 		draw_primordia_menu(SDL_Renderer *renderer, menu_t *menu, state_t *state, SDL_Rect *render_quad);

/*      menu_conway */
int     updating_conway_graph(state_t *state);
void    draw_conway_menu(SDL_Renderer *renderer, menu_t *menu, state_t *state, SDL_Rect *quad);
// int     update_conway_graph(state_t *state);

#endif
