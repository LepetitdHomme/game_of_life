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
  // initial growth function for primordia rule
  float values[] = { -1.0, -1.0, 0.0, 1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0 };
  for (int i = 0; i < NUM_GROWTH_PRIMORDIA; i++) {
    state->growth_primordia[i] = values[i];
    for (int j = 0; j < 3 ; j++) {
      state->primordia_graph_buttons[i][j].x = 0;
      state->primordia_graph_buttons[i][j].y = 0;
      state->primordia_graph_buttons[i][j].w = 0;
      state->primordia_graph_buttons[i][j].h = 0;
    }
  }
  //
  state->quit = FALSE; // quits program if true
  state->mouse_pos_x = 0;
  state->mouse_pos_y = 0;
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

int main() {
  srand(time(NULL));
  sdl_t sdl;
  sdl.window = NULL;
  sdl.renderer = NULL;
  init_sdl(&sdl);

  menu_t menu;
  init_menu(&sdl, &menu);

  /********** VAR INIT ***************/
  float grid[GRID_W][GRID_H] = { {0} };
  float grid2[GRID_W][GRID_H] = { {0} };
  state_t state;
  init_game_state(&state);
  uint32_t last_cycle = SDL_GetTicks();
  // init_lenia(grid);

  /********** GAME LOOP *************/
  while (state.quit == FALSE) {
    state.current_time = SDL_GetTicks();
    while (SDL_PollEvent(&sdl.Event)) {
      handle_event(&state, (state.current_grid == 0) ? grid : grid2 ,&sdl.Event);
    }
    SDL_SetRenderDrawColor(sdl.renderer, 0, 0, 0, 255);
    SDL_RenderClear(sdl.renderer);

    /* computes next cycle on appropriate grid, depending on life CYCLE_INTERVAL */
    if (state.cycle_running) {
      if ((state.current_time - last_cycle) / 1000.0 > CYCLE_INTERVAL) {
        last_cycle = state.current_time;
        state.cycle_count++;
        if (state.current_grid == 0) {
          switch (state.current_rule) {
            case CONWAY:
              state.cells_count = next_cycle(grid, grid2);
              break;
            case PRIMORDIA:
              state.cells_count = next_cycle_primordia(grid, grid2, state.growth_primordia);
              break;
            case LENIA:
              state.cells_count = next_cycle_lenia(grid, grid2);
              break;
            default:
              state.cells_count = next_cycle(grid, grid2);
          }
          reinitialize_grid(grid);
          state.current_grid = 1;
        } else {
          switch (state.current_rule) {
            case CONWAY:
              state.cells_count = next_cycle(grid2, grid);
              break;
            case PRIMORDIA:
              state.cells_count = next_cycle_primordia(grid2, grid, state.growth_primordia);
              break;
            case LENIA:
              state.cells_count = next_cycle_lenia(grid2, grid);
              break;
            default:
              state.cells_count = next_cycle(grid2, grid);
          }
          reinitialize_grid(grid2);
          state.current_grid = 0;
        }
      }
    }

    draw_current_grid(sdl.renderer, (state.current_grid == 0) ? grid : grid2);
    draw_menu(sdl.renderer, &menu, &state);

    // display_gauss(renderer);

    SDL_RenderPresent(sdl.renderer);
    SDL_Delay(16);
  }

  /*********** SDL FREE/QUIT ************/
  free_menu(&menu);
  SDL_DestroyRenderer(sdl.renderer);
  SDL_DestroyWindow(sdl.window);
  TTF_Quit();
  SDL_Quit();
  return 0;
}
