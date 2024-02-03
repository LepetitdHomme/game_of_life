#include "includes/common.h"

int update_primordia_graph(state_t *state) {
  for (int x = 0; x < NUM_GROWTH_PRIMORDIA ; x++) {
    for (int y = 0 ; y < 3 ; y++) {
      if (mouse_on_button(state->primordia_graph_buttons[x][y], state)) {
        state->growth_primordia[x] = 1.0 - y; // 1.0 ; 0.0 ; -1.0
        return 1;
      }
    }
  }
  return 0;
}

/* Values of growth are -1.0, 0.0 or 1.0 => top y of quad, middle or bottom => to screen y coord */
int growth_to_quad_to_y(float growth, SDL_Rect quad) {
  int y;

  if (growth < 0.0) {
    y = quad.y + quad.h;
  } else if (growth == 0.0) {
    y = quad.y + quad.h / 2;
  } else {
    y = quad.y;
  }

  return y;
}

void    update_primordia_buttons(SDL_Renderer *renderer, state_t *state, SDL_Rect *render_quad) {
  int step_x = render_quad->w / NUM_GROWTH_PRIMORDIA;
  int step_y = render_quad->h / 3;

  SDL_SetRenderDrawColor(renderer, 16, 16, 16, 255);
  for (int x = 0; x < NUM_GROWTH_PRIMORDIA; x++) {
    for (int y = 0; y < 3; y++) {
      state->primordia_graph_buttons[x][y].x = render_quad->x + x * step_x;
      state->primordia_graph_buttons[x][y].y = render_quad->y + (y * step_y);
      state->primordia_graph_buttons[x][y].w = step_x;
      state->primordia_graph_buttons[x][y].h = step_y;
      SDL_RenderDrawRect(renderer, &state->primordia_graph_buttons[x][y]);
    }
  }
}

void    draw_primordia_menu(SDL_Renderer *renderer, menu_t *menu, state_t *state, SDL_Rect *render_quad) {
  render_quad->y += 40;
  render_quad->x = state->menu_pos_x + 5;
  render_quad->w = MENU_WIDTH - 10;
  render_quad->h = 60;
  int i,j,c,d,tmp_i,tmp_j,e;

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer, render_quad);

  update_primordia_buttons(renderer, state, render_quad);
  // display legend ?

  int step = render_quad->w / NUM_GROWTH_PRIMORDIA;
  int step_y = render_quad->h / 3;
  for (int x = 0 ; x < NUM_GROWTH_PRIMORDIA ; x++) {
    i = render_quad->x + (x * step);
    j = growth_to_quad_to_y(state->growth_primordia[x], *render_quad);

    // Draw line between n and n - 1 point
    if (x > 0) {
      SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
      SDL_RenderDrawLine(renderer, tmp_i, tmp_j, i, j);
    }
    tmp_i = i;
    tmp_j = j;

    // Draw thick point
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int c = i - 2; c < i + 2 ; c++) {
      for (int d = j - 2 ; d < j + 2 ; d++) {
        SDL_RenderDrawPoint(renderer, c, d);
      }
    }
  }
}
