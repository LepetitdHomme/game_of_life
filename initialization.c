#include "includes/common.h"

void init_game_state(state_t *state) {
  state->current_grid = 0; // switch between 2 grids for computing next cycle without erasing current values
  state->current_rule = CONWAY; // ENUM
  state->cycle_running = FALSE; // will next cycle be computed and displayed ?
  state->cycle_count = 0;
  state->cells_count = 0;
  state->holding_left_mouse = FALSE; // used to draw ; make cells alive
  state->menu_opened = FALSE;
  state->menu_pos_x = -MENU_WIDTH; // basically -MENU_WIDTH or 0 (x screen coord);
  // the button up left that opens the menu
  state->menu_button.x = MENU_WIDTH / 10;
  state->menu_button.y = MENU_WIDTH / 10;
  state->menu_button.w = state->menu_button.x;
  state->menu_button.h = state->menu_button.x;
  // menu button that resets current grid with current rule
  state->reset_button.x = MENU_WIDTH * 20 / 100;
  state->reset_button.y = state->reset_button.x / 2;
  state->reset_button.w = state->reset_button.x;
  state->reset_button.h = state->reset_button.x;
  // menu button to pause cycles
  state->pause_button.x = MENU_WIDTH * 20 / 100;
  state->pause_button.y = state->pause_button.x / 2;
  state->pause_button.w = state->pause_button.x;
  state->pause_button.h = state->pause_button.x;
  //
  state->quit = FALSE; // quits program if true
  state->mouse_pos_x = 0;
  state->mouse_pos_y = 0;

  init_primordia_growth(state);
  init_conway_growth(state);
  init_kernel(state);
}

void init_sdl(sdl_t *sdl) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL initialization failed: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  sdl->window = SDL_CreateWindow("Game of life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (sdl->window == NULL) {
    printf("Window creation failed: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  sdl->renderer = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED);
  if (sdl->renderer == NULL) {
    printf("Renderer creation failed: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  if (TTF_Init() == -1) {
    printf("SDL_ttf could not init ! %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }
}

// avoidable
void reinitialize_grid(float (*grid)[GRID_H]) {
  int i,j;
  for(i = 0 ; i < GRID_W ; i++) {
    for (j = 0 ; j < GRID_H ; j++) {
      grid[i][j] = 0.0;
    }
  }
}

void init_menu(sdl_t *sdl, menu_t *menu) {
  menu->font = TTF_OpenFont("assets/metropolis.regular.otf", 50); // not really readable under 50 ?
  if (menu->font == NULL) {
    printf("Failed to open font ! SDL_ttf error: %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }
}

void init_kernel(state_t *state) {
  int kernel[KERNEL_SIZE][KERNEL_SIZE] = {
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1}
  };

  for (int i = 0; i < KERNEL_SIZE ; i++) {
    for (int j = 0; j < KERNEL_SIZE ; j++) {
      state->kernel[i][j] = kernel[i][j];
      state->kernel_buttons[i][j].x = 0;
      state->kernel_buttons[i][j].y = 0;
      state->kernel_buttons[i][j].w = 0;
      state->kernel_buttons[i][j].h = 0;
    }
  }
}

void init_conway_growth(state_t *state) {
  int *survive = get_conway_survive();
  int *born = get_conway_born();

  if (survive != NULL && born != NULL) {
    for (int i = 0; i < NUM_GROWTH_CONWAY; i++) {
      state->survive_conway[i] = survive[i];
      state->born_conway[i] = born[i];
      for (int j = 0; j < 2; j++) {
        state->survive_conway_graph_buttons[i][j].x = state->born_conway_graph_buttons[i][j].x = 0;
        state->survive_conway_graph_buttons[i][j].y = state->born_conway_graph_buttons[i][j].y = 0;
        state->survive_conway_graph_buttons[i][j].w = state->born_conway_graph_buttons[i][j].w = 0;
        state->survive_conway_graph_buttons[i][j].h = state->born_conway_graph_buttons[i][j].h = 0;
      }
    }
  } else {
    printf("Initialization Failed at conway rule init ; exiting.\n");
    exit(EXIT_FAILURE);
  }
}

void init_primordia(float (*grid)[GRID_H]) {
  int i,j;
  float random;

  for(i = 0 ; i < GRID_W ; i++) {
    for (j = 0 ; j < GRID_H ; j++) {
      random = random_float(-2.5, 1.0);
      grid[i][j] = fmin(fmax(random, 0.0), 1.0);
    }
  }
}

void init_primordia_growth(state_t *state) {
  float *values = get_primordia_growth();

  if (values != NULL) {
    for (int i = 0; i < NUM_GROWTH_PRIMORDIA; i++) {
      state->growth_primordia[i] = values[i];
      state->primordia_graph_buttons[i].x = 0;
      state->primordia_graph_buttons[i].y = 0;
      state->primordia_graph_buttons[i].w = 0;
      state->primordia_graph_buttons[i].h = 0;
    }
  } else {
    printf("Initialization Failed at primordia rule init; exiting.\n");
    exit(EXIT_FAILURE);
  }
}

void init_lenia(float (*grid)[GRID_H]) {
  int i,j;
  for(i = 0 ; i < GRID_W ; i++) {
    for (j = 0 ; j < GRID_H ; j++) {
      grid[i][j] = random_float(0.0, 1.0);
      if (grid[i][j] <= 0.8) { // play with this
        grid[i][j] = 0.0;
      }
    }
  }
}
