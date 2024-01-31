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

int is_in_grid(int x, int y) {
  if (x >= 0 && x < GRID_W && y >= 0 && y < GRID_H) {
    return TRUE;
  } else {
    return FALSE;
  }
}
