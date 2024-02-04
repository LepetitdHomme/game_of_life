#include "includes/common.h"

int updating_kernel(state_t *state) {
  for (int x = 0; x < KERNEL_SIZE ; x++) {
    for (int y = 0 ; y < KERNEL_SIZE ; y++) {
      if (mouse_on_button(state->kernel_buttons[x][y], state)) {
        if (state->kernel[x][y] == 0) {
          state->kernel[x][y] = 1;
        } else {
          state->kernel[x][y] = 0;
        }
        return 1;
      }
    }
  }
  return 0;
}

void draw_kernel(SDL_Renderer *renderer, menu_t *menu, state_t *state, SDL_Rect *quad) {
  quad->y += 80;
  quad->w = MENU_WIDTH / 2;
  quad->h = quad->w;
  quad->x = state->menu_pos_x + (MENU_WIDTH - quad->w) / 2;
  int i,j,c,d,tmp_i,tmp_j,e;
  SDL_Rect text;
  SDL_Color color = { 255, 255, 255 };

  // text
  char kernel[] = "Kernel";
  text.x = state->menu_pos_x + 5;
  text.y = quad->y;
  text.w = MENU_WIDTH - 10;
  text.h = 20;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer, &text);
  text.w = strlen(kernel) * VISIBLE_TEXT_SIZE;
  render_text(renderer, menu, kernel, &text, color);

  // graph
  quad->y += 25;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer, quad);
  // display legend ?
  int step_x = quad->w / KERNEL_SIZE;
  int step_y = quad->h / KERNEL_SIZE;

  SDL_SetRenderDrawColor(renderer, 16, 16, 16, 255);
  for (int x = 0; x < KERNEL_SIZE; x++) {
    for (int y = 0; y < KERNEL_SIZE; y++) {
      state->kernel_buttons[x][y].x = quad->x + x * step_x;
      state->kernel_buttons[x][y].y = quad->y + (y * step_y);
      state->kernel_buttons[x][y].w = step_x;
      state->kernel_buttons[x][y].h = step_y;
      if (state->kernel[x][y] == 0) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
      }
      SDL_RenderFillRect(renderer, &state->kernel_buttons[x][y]);
    }
  }
}


// float gaussianKernel(int i, int j) {
//   // Define discrete Gaussian kernel (example)
//   static float gaussianKernel[KERNEL_SIZE][KERNEL_SIZE] = {
//     {0.075, 0.125, 0.075},
//     {0.125, 0.200, 0.125},
//     {0.075, 0.125, 0.075}
//   };

//   return gaussianKernel[i][j];
// }

// float vonNeumannKernel(int i, int j) {
//   // Define discrete Von Neumann kernel
//   static float vonNeumannKernel[KERNEL_SIZE][KERNEL_SIZE] = {
//     {0, 1, 0},
//     {1, 1, 1},
//     {0, 1, 0}
//   };

//   return vonNeumannKernel[i][j];
// }

// float mooreKernel(int i, int j) {
//   // Define discrete Moore kernel
//   static float mooreKernel[KERNEL_SIZE][KERNEL_SIZE] = {
//     {1, 1, 1},
//     {1, 1, 1},
//     {1, 1, 1}
//   };

//   return mooreKernel[i][j];
// }

// float conwayKernel(int i, int j) {
//   // Define discrete Moore kernel
//   static float conwayKernel[KERNEL_SIZE][KERNEL_SIZE] = {
//     {1, 1, 1},
//     {1, 0, 1},
//     {1, 1, 1}
//   };

//   return conwayKernel[i][j];
// }
