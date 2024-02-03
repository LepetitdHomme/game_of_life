#include "includes/common.h"

void map_life_to_color(float life, Uint8 *r, Uint8 *g, Uint8 *b) {
  // Define the color gradient ranges
  Uint8 blue_min = 0;
  Uint8 blue_max = 255;
  Uint8 yellow_min = 0;
  Uint8 yellow_max = 255;

  if (life < 0.7) {
    // If life is less than 0.7, interpolate from blue to yellow
    *r = (Uint8)((life / 0.7) * blue_max + ((0.7 - life) / 0.7) * yellow_max);
    *g = (Uint8)((life / 0.7) * blue_max + ((0.7 - life) / 0.7) * yellow_max);
    *b = (Uint8)((life / 0.7) * blue_max + ((0.7 - life) / 0.7) * yellow_min);
  } else {
    // If life is greater than or equal to 0.7, set to full yellow
    *r = yellow_max;
    *g = yellow_max;
    *b = yellow_min;
  }
}

void draw_current_grid(SDL_Renderer *renderer, float grid[GRID_W][GRID_H]) {
  Uint8 r,g,b;

  for (int i = 0 ; i < WINDOW_WIDTH ; i++) {
    for (int j = 0; j < WINDOW_HEIGHT ; j++) {
      float cell;
      if (is_in_grid(i/SCALE, j/SCALE)) {
        if ((cell = grid[i/SCALE][j/SCALE]) > 0.0) {
          // = (int)((cell - floor(cell)) * 100) % 256;
          map_life_to_color(cell, &r, &g, &b);
          SDL_SetRenderDrawColor(renderer, r, g, b, 255);
          SDL_RenderDrawPoint(renderer, i, j);
        }
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
