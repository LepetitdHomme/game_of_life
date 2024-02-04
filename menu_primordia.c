#include "includes/common.h"

int updating_primordia_graph(state_t *state) {
  int click_h;
  float value;

  for (int x = 0; x < NUM_GROWTH_PRIMORDIA ; x++) {
    if (mouse_on_button(state->primordia_graph_buttons[x], state)) {
      value = state->primordia_graph_buttons[x].y + state->primordia_graph_buttons[x].h / 2 - state->mouse_pos_y;
      value = (float)value / ((float)state->primordia_graph_buttons[x].h / 2.0);

      // facilitates graph click
      if (value <= -0.8) {
        value = -1.0;
      } else if (value >= -0.2 && value <= 0.2) {
        value = 0.0;
      } else if (value >= 0.8) {
        value = 1.0;
      }
      //

      state->growth_primordia[x] = value;
      return 1;
    }
  }
  return 0;
}

/* Values of growth are -1.0, 0.0 or 1.0 => top y of quad, middle or bottom => to screen y coord */
int growth_to_quad_to_y(float growth, SDL_Rect quad) {
  return quad.y + quad.h / 2.0 - (growth * (float)quad.h / 2.0);
}

void    update_primordia_buttons(SDL_Renderer *renderer, state_t *state, SDL_Rect *render_quad) {
  int step_x = render_quad->w / NUM_GROWTH_PRIMORDIA;

  SDL_SetRenderDrawColor(renderer, 16, 16, 16, 255);
  for (int x = 0; x < NUM_GROWTH_PRIMORDIA; x++) {
    state->primordia_graph_buttons[x].x = render_quad->x + x * step_x;
    state->primordia_graph_buttons[x].y = render_quad->y;
    state->primordia_graph_buttons[x].w = step_x;
    state->primordia_graph_buttons[x].h = render_quad->h;
    SDL_RenderDrawRect(renderer, &state->primordia_graph_buttons[x]);
  }
}

void    draw_primordia_menu(SDL_Renderer *renderer, menu_t *menu, state_t *state, SDL_Rect *render_quad) {
  render_quad->y += 40;
  render_quad->x = state->menu_pos_x + 5;
  render_quad->w = MENU_WIDTH - 10;
  render_quad->h = 60;
  int i,j,c,d,tmp_i,tmp_j,e;
  SDL_Rect point;
  SDL_Rect text;
  SDL_Color color = { 255, 255, 255 };

  // text
  char growth_text[] = "Growth[-1.0,1.0]";
  text.x = state->menu_pos_x + 5;
  text.y = render_quad->y;
  text.w = MENU_WIDTH - 10;
  text.h = 20;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer, &text);
  text.w = strlen(growth_text) * VISIBLE_TEXT_SIZE;
  render_text(renderer, menu, growth_text, &text, color);

  // graph
  render_quad->y += 25;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer, render_quad);

  update_primordia_buttons(renderer, state, render_quad);
  // display legend ?

  int step = render_quad->w / NUM_GROWTH_PRIMORDIA;

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
    // Draw thick point
    point.x = i - 2;
    point.y = j - 2;
    point.w = 5;
    point.h = 5;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &point);
  }
}
