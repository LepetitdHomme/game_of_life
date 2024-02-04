#include "includes/common.h"

/* uses NUM_GROWTH_PRIMORDIA */
float * get_primordia_growth() {
  static float values[] = { -1.0, -1.0, 0.0, 1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0 };

  return values;
}

int next_cycle_primordia(float (*grid)[GRID_H], float (*grid2)[GRID_H], state_t *state){
  int i,j;
  int cells_count = 0;
  float max = 1.0;
  float min = 0.0;
  float result = 0.0;

  for(i = 1; i < GRID_W - 1 ; i++) {
    for(j = 1 ; j < GRID_H - 1; j++) {
      float sum = 0.0;

      for (int c = 0; c < KERNEL_SIZE ; c++) {
        for (int d = 0 ; d < KERNEL_SIZE ; d++) {
          sum += grid[i + c - 1][j + d - 1] * state->kernel[c][d];
        }
      }

      result = grid[i][j] + state->growth_primordia[(int)sum];
      grid2[i][j] = fmin(fmax(result, min), max);

      if (grid2[i][j] > 0.0) {
        cells_count++;
      }
    }
  }
  return cells_count;
}
