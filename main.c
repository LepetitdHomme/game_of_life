#include "includes/common.h"

void reinitialize_grid(float (*grid)[GRID_H]) {
  int i,j;
  for(i = 0 ; i < GRID_W ; i++) {
    for (j = 0 ; j < GRID_H ; j++) {
      grid[i][j] = 0.0;
    }
  }
}

void draw_current_grid(SDL_Renderer *renderer, float grid[GRID_W][GRID_H]) {
  for (int i = 0 ; i < WINDOW_WIDTH ; i++) {
    for (int j = 0; j < WINDOW_HEIGHT ; j++) {
      float cell;
      if ((cell = grid[i/SCALE][j/SCALE]) > 0.0) {
        Uint8 r = (int)((cell - floor(cell)) * 100) % 256;
        SDL_SetRenderDrawColor(renderer, r, r, 64, 255);
        SDL_RenderDrawPoint(renderer, i, j);
      }
    }
  }
}

void init_game_state(state_t *state) {
  state->current_grid = 0;
  state->cycle_running = FALSE;
  state->holding_left_mouse = FALSE;
  state->quit = FALSE;
  state->mouse_pos_x = 0;
  state->mouse_pos_y = 0;
}

int is_in_grid(int x, int y) {
  if (x >= 0 && x < GRID_W && y >= 0 && y < GRID_H) {
    return TRUE;
  } else {
    return FALSE;
  }
}

int main() {
  /********** SDL INIT ***************/
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      printf("SDL initialization failed: %s\n", SDL_GetError());
      return 1;
  }
  SDL_Window *window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
  if (window == NULL) {
      printf("Window creation failed: %s\n", SDL_GetError());
      return 1;
  }
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_Event event;

  /********** VAR INIT ***************/
  float grid[GRID_W][GRID_H] = { {0} };
  float grid2[GRID_W][GRID_H] = { {0} };
  state_t state;
  init_game_state(&state);
  uint32_t last_cycle = SDL_GetTicks();
  init_lenia(grid);

  /********** GAME LOOP *************/
  while (state.quit == FALSE) {
    state.current_time = SDL_GetTicks();
    while (SDL_PollEvent(&event)) {
      handle_event(&state, (state.current_grid == 0) ? grid : grid2 ,&event);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    /* computes next cycle on appropriate grid, depending on life CYCLE_INTERVAL */
    if (state.cycle_running) {
      if ((state.current_time - last_cycle) / 1000.0 > CYCLE_INTERVAL) {
        last_cycle = state.current_time;
        if (state.current_grid == 0) {
          next_cycle_lenia(grid, grid2);
          reinitialize_grid(grid);
          state.current_grid = 1;
        } else {
          next_cycle_lenia(grid2, grid);
          reinitialize_grid(grid2);
          state.current_grid = 0;
        }
      }
    }

    draw_current_grid(renderer, (state.current_grid == 0) ? grid : grid2);

    display_gauss(renderer);

    SDL_RenderPresent(renderer);
  }

  /*********** SDL FREE/QUIT ************/
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
