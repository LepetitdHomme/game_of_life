#include "includes/common.h"

/* TODO
** Need to initialize the menu beforehand, right now everything - place - is recomputed everytime, this is ridiculous
** Factorize display of graphs
** Primordia graph buttons are slow on reset + pause, why ?
** 
*/

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
      if ((state.current_time - last_cycle) > CYCLE_INTERVAL) {
        last_cycle = state.current_time;
        state.cycle_count++;
        if (state.current_grid == 0) {
          switch (state.current_rule) {
            case PRIMORDIA:
              state.cells_count = next_cycle_primordia(grid, grid2, &state);
              break;
            case LENIA:
              state.cells_count = next_cycle_lenia(grid, grid2, &state);
              break;
            default:
              state.cells_count = next_cycle(grid, grid2, &state);
          }
          reinitialize_grid(grid);
          state.current_grid = 1;
        } else {
          switch (state.current_rule) {
            case PRIMORDIA:
              state.cells_count = next_cycle_primordia(grid2, grid, &state);
              break;
            case LENIA:
              state.cells_count = next_cycle_lenia(grid2, grid, &state);
              break;
            default:
              state.cells_count = next_cycle(grid2, grid, &state);
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
    SDL_Delay(8);
  }

  /*********** SDL FREE/QUIT ************/
  free_menu(&menu);
  SDL_DestroyRenderer(sdl.renderer);
  SDL_DestroyWindow(sdl.window);
  TTF_Quit();
  SDL_Quit();
  return 0;
}
