#include "includes/common.h"

/* uses NUM_GROWTH_CONWAY */
int * get_conway_survive() {
  static int values[] = { 0, 0, 1, 1, 0, 0, 0, 0, 0 };

  return values;
}
int * get_conway_born() {
  static int values[] = { 0, 0, 0, 1, 0, 0, 0, 0, 0 };

  return values;
}

// B3/S23 (Born with 3 neighbours and Survive with 2 or 3 neighbours == conway)
int next_cycle(float (*grid)[GRID_H], float (*grid2)[GRID_H], state_t *state){
	int i,j;
	int cells_count = 0;

	for(i = 1; i < GRID_W - 1 ; i++) {
		for(j = 1 ; j < GRID_H - 1 ; j++) {
			int sum = 0;

			for (int x = 0 ; x < KERNEL_SIZE ; x++ ) {
				for (int y = 0 ; y < KERNEL_SIZE; y++) {
					sum += grid[i + x - 1][j + y - 1] * state->kernel[x][y];
				}
			}

			if (grid[i][j] == 1) {
				if (state->survive_conway[sum]) {
					grid2[i][j] = 1;
					cells_count++;
				} else {
					grid2[i][j] = 0;
				}
			} else {
				if (state->born_conway[sum]) {
					grid2[i][j] = 1;
					cells_count++;
				}
			}
		}
	}
	return cells_count;
}
