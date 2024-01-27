#include "includes/common.h"

void reinit_grid(int (*grid)[GRID_H]) {
  int i,j;
  for(i = 0 ; i < GRID_W ; i++) {
    for (j = 0 ; j < GRID_H ; j++) {
      grid[i][j] = 0;
    }
  }
}

void draw_grid(SDL_Renderer *renderer, int grid[GRID_W][GRID_H]) {
  for (int i = 0 ; i < WINDOW_WIDTH ; i++) {
    for (int j = 0; j < WINDOW_HEIGHT ; j++) {
      if (grid[i/RATE][j/RATE] == 1) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawPoint(renderer, i, j);
      }
    }
  }
}

// cell value continue 0->1
// sum neighbours creates emergence of new rules
// we can consider life/death now as 'growth'
// 
int main() {

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

  int grid[GRID_W][GRID_H] = { {0} };
  int grid2[GRID_W][GRID_H] = { {0} };

  SDL_Event event;
  int quit = 0;
  int start = 0;
  int current_grid = 0;
  uint32_t last_cycle = SDL_GetTicks();
  int l_mouse_down, x_mouse, y_mouse = 0;

  while (!quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = 1;
      }
      if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
          l_mouse_down = 1;
        }
      }
      if (event.type == SDL_MOUSEBUTTONUP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
          if (current_grid == 0) {
            grid[event.button.x/RATE][event.button.y/RATE] = 1;
          } else {
            grid2[event.button.x/RATE][event.button.y/RATE] = 1;
          }
          l_mouse_down = 0;
        }
      }
      if (event.type == SDL_MOUSEMOTION && l_mouse_down == 1) {
        SDL_GetMouseState(&x_mouse,&y_mouse);
        if (current_grid == 0) {
          grid[x_mouse/RATE][y_mouse/RATE] = 1;
        } else {
          grid2[x_mouse/RATE][y_mouse/RATE] = 1;
        }
      }
      if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_SPACE) {
          if(start == 1) {
            printf("stopped\n");
            start = 0;
          } else {
            printf("running\n");
            start = 1;
          }
        }
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    uint32_t currTime = SDL_GetTicks();
    if(start && ((currTime - last_cycle) / 1000.0) > SPEED) {
      last_cycle = currTime;
      if (current_grid == 0) {
        next_cycle(grid, grid2);
        reinit_grid(grid);
        current_grid = 1;
      } else {
        next_cycle(grid2, grid);
        reinit_grid(grid2);
        current_grid = 0;
      }
    }

    if (current_grid == 0) {
      draw_grid(renderer, grid);
    } else {
      draw_grid(renderer, grid2);
    }

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
