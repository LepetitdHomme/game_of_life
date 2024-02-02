#include "includes/common.h"

float gaussianKernel(int i, int j) {
  // Define discrete Gaussian kernel (example)
  static float gaussianKernel[KERNEL_SIZE][KERNEL_SIZE] = {
    {0.075, 0.125, 0.075},
    {0.125, 0.200, 0.125},
    {0.075, 0.125, 0.075}
  };

  return gaussianKernel[i][j];
}

float vonNeumannKernel(int i, int j) {
  // Define discrete Von Neumann kernel
  static float vonNeumannKernel[KERNEL_SIZE][KERNEL_SIZE] = {
    {0, 1, 0},
    {1, 1, 1},
    {0, 1, 0}
  };

  return vonNeumannKernel[i][j];
}

float mooreKernel(int i, int j) {
  // Define discrete Moore kernel
  static float mooreKernel[KERNEL_SIZE][KERNEL_SIZE] = {
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1}
  };

  return mooreKernel[i][j];
}

float conwayKernel(int i, int j) {
  // Define discrete Moore kernel
  static float conwayKernel[KERNEL_SIZE][KERNEL_SIZE] = {
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1}
  };

  return conwayKernel[i][j];
}

float random_float(float lower_bound, float upper_bound) {
    // Generate a random integer between 0 and RAND_MAX
    int random_int = rand();

    // Scale and shift the random integer to the range [0, 1]
    float scaled_random = (float)random_int / RAND_MAX;

    // Scale and shift the random float to the specified range [lower_bound, upper_bound]
    float random_float = (upper_bound - lower_bound) * scaled_random + lower_bound;

    return random_float;
}

void reinitialize_grid(float (*grid)[GRID_H]) {
  int i,j;
  for(i = 0 ; i < GRID_W ; i++) {
    for (j = 0 ; j < GRID_H ; j++) {
      grid[i][j] = 0.0;
    }
  }
}

void map_life_to_color(float life, Uint8 *r, Uint8 *g, Uint8 *b) {
  // Define the color gradient range (e.g., from blue to red)
  Uint8 min_color = 0;
  Uint8 max_color = 255;

  *b = 0;//(Uint8)((1.0 - life) * max_color + life * min_color);
  *g = (Uint8)((1.0 - life) * min_color + life * max_color);
  *r = (Uint8)((1.0 - life) * min_color + life * max_color);
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
