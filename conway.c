#include "includes/common.h"

// B3/S23 (Born with 3 neighbours and Survive with 2 or 3 neighbours == conway)
void next_cycle(float (*grid)[GRID_H], float (*grid2)[GRID_H]){
	int i,j;

	for(i = 0; i < GRID_W ; i++) {
		for(j = 0 ; j < GRID_H ; j++) {
			// IF ALIVE
			if(grid[i][j] == 1) {
				int count = 0;
				if(is_in_grid(i-1, j-1) && grid[i-1][j-1] == 1)
					count++;
				if(is_in_grid(i, j-1) && grid[i][j-1] == 1)
					count++;
				if(is_in_grid(i+1,j-1) && grid[i+1][j-1] == 1)
					count++;
				if(is_in_grid(i-1, j) && grid[i-1][j] == 1)
					count++;
				if(is_in_grid(i+1,j) && grid[i+1][j] == 1)
					count++;
				if(is_in_grid(i-1,j+1) && grid[i-1][j+1] == 1)
					count++;
				if(is_in_grid(i,j+1) && grid[i][j+1] == 1)
					count++;
				if(is_in_grid(i+1,j+1) && grid[i+1][j+1] == 1)
					count++;
				if(count == 2 || count == 3) {
					grid2[i][j] = 1;
				} else {
					grid2[i][j] = 0;
				}
			} else { // IF DEAD
				int count = 0;
				if(is_in_grid(i-1, j-1) && grid[i-1][j-1] == 1)
					count++;
				if(is_in_grid(i, j-1) && grid[i][j-1] == 1)
					count++;
				if(is_in_grid(i+1,j-1) && grid[i+1][j-1] == 1)
					count++;
				if(is_in_grid(i-1, j) && grid[i-1][j] == 1)
					count++;
				if(is_in_grid(i+1,j) && grid[i+1][j] == 1)
					count++;
				if(is_in_grid(i-1,j+1) && grid[i-1][j+1] == 1)
					count++;
				if(is_in_grid(i,j+1) && grid[i][j+1] == 1)
					count++;
				if(is_in_grid(i+1,j+1) && grid[i+1][j+1] == 1)
					count++;
				if(count == 3) {
					grid2[i][j] = 1;
				}
			}
		}
	}
}
