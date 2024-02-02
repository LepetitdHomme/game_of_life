#include "includes/common.h"

void init_primordia(float (*grid)[GRID_H]) {
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

int next_cycle_primordia(float (*grid)[GRID_H], float (*grid2)[GRID_H]){
  int i,j;
  int cells_count = 0;
  float max = 1.0;
  float min = 0.0;

  for(i = 1; i < GRID_W - 1 ; i++) {
    for(j = 1 ; j < GRID_H - 1; j++) {
      float sum = 0.0;

      for (int c = -1; c <= 1 ; c++) {
        for (int d = -1 ; d <= 1 ; d++) {
          sum += grid[i + c][j + d] * conwayKernel(c + 1, d + 1);
        }
      }

      if (sum >= 2.00 && sum <= 3.00) {
        grid2[i][j] = grid[i][j]; // Growth condition
      } else if (sum <= 1.0 || sum >= 3.0) {
        grid2[i][j] = grid[i][j] - 1.0; // Shrinkage condition
      } else {
        grid2[i][j] = 0.0; // No change
      }
      // if (sum >= 7.0) {
      //   grid2[i][j] = grid[i][j];
      // } else {
      //   grid2[i][j] = 0.0;
      // }

      grid2[i][j] = fmin(fmax(sum, min), max);
      printf("%f-", grid2[i][j]);

      if (grid2[i][j] > 0.0) {
        cells_count++;
      }
    }
  }
  return cells_count;
}
