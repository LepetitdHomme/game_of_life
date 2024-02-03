#include "includes/common.h"

void init_primordia(float (*grid)[GRID_H]) {
  int i,j;

  for(i = 0 ; i < GRID_W ; i++) {
    for (j = 0 ; j < GRID_H ; j++) {
      grid[i][j] = random_float(0.0, 1.0);
      // if (grid[i][j] <= 0.8) { // play with this
      //   grid[i][j] = 0.0;
      // }
    }
  }
}

float growth_primordia(float X) {
  static float growth[] = { -1.0, -1.0, 0.0, 1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0 };

  return growth[(int)(X)];
}

int next_cycle_primordia(float (*grid)[GRID_H], float (*grid2)[GRID_H]){
  int i,j;
  int cells_count = 0;
  float max = 1.0;
  float min = 0.0;
  float result = 0.0;

  for(i = 1; i < GRID_W - 1 ; i++) {
    for(j = 1 ; j < GRID_H - 1; j++) {
      float sum = 0.0;

      for (int c = -1; c <= 1 ; c++) {
        for (int d = -1 ; d <= 1 ; d++) {
          sum += grid[i + c][j + d] * conwayKernel(c + 1, d + 1);
        }
      }

      result = grid[i][j] + growth_primordia(sum);
      grid2[i][j] = fmin(fmax(result, min), max);

      if (grid2[i][j] > 0.0) {
        cells_count++;
      }
    }
  }
  return cells_count;
}
