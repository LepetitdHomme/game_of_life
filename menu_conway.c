#include "includes/common.h"

int update_conway_graph(state_t *state) {
  for (int x = 0; x < NUM_GROWTH_CONWAY ; x++) {
    for (int y = 0 ; y < 2 ; y++) {
      if (mouse_on_button(state->survive_conway_graph_buttons[x][y], state)) {
        if (y == 0) {
          state->survive_conway[x] = 1;
        } else {
          state->survive_conway[x] = 0;
        }
        return 1;
      } else if (mouse_on_button(state->born_conway_graph_buttons[x][y], state)) {
        if (y == 0) {
          state->born_conway[x] = 1;
        } else {
          state->born_conway[x] = 0;
        }
        return 1;
      }
    }
  }
  return 0;
}

void update_survive_conway_buttons(SDL_Renderer *renderer, state_t *state, SDL_Rect *quad) {
  int step_x = quad->w / NUM_GROWTH_CONWAY;
  int step_y = quad->h / 2;

  SDL_SetRenderDrawColor(renderer, 16, 16, 16, 255);
  for (int x = 0; x < NUM_GROWTH_CONWAY; x++) {
    for (int y = 0; y < 2; y++) {
      state->survive_conway_graph_buttons[x][y].x = quad->x + x * step_x;
      state->survive_conway_graph_buttons[x][y].y = quad->y + (y * step_y);
      state->survive_conway_graph_buttons[x][y].w = step_x;
      state->survive_conway_graph_buttons[x][y].h = step_y;
      SDL_RenderDrawRect(renderer, &state->survive_conway_graph_buttons[x][y]);
    }
  }
}

void update_born_conway_buttons(SDL_Renderer *renderer, state_t *state, SDL_Rect *quad) {
  int step_x = quad->w / NUM_GROWTH_CONWAY;
  int step_y = quad->h / 2;

  SDL_SetRenderDrawColor(renderer, 16, 16, 16, 255);
  for (int x = 0; x < NUM_GROWTH_CONWAY; x++) {
    for (int y = 0; y < 2; y++) {
      state->born_conway_graph_buttons[x][y].x = quad->x + x * step_x;
      state->born_conway_graph_buttons[x][y].y = quad->y + (y * step_y);
      state->born_conway_graph_buttons[x][y].w = step_x;
      state->born_conway_graph_buttons[x][y].h = step_y;
      SDL_RenderDrawRect(renderer, &state->born_conway_graph_buttons[x][y]);
    }
  }
}

void draw_survive(SDL_Renderer *renderer, menu_t *menu, state_t *state, SDL_Rect *quad) {
  quad->y += 40;
  quad->x = state->menu_pos_x + 5;
  quad->w = MENU_WIDTH - 10;
  quad->h = 60;
  int i,j,c,d,tmp_i,tmp_j,e;
  SDL_Rect point;
  SDL_Rect text;
  SDL_Color color = { 255, 255, 255 };

  // text
  char survive[] = "Survive";
  text.x = state->menu_pos_x + 5;
  text.y = quad->y;
  text.w = MENU_WIDTH - 10;
  text.h = 20;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer, &text);
  text.w = strlen(survive) * VISIBLE_TEXT_SIZE;
  render_text(renderer, menu, survive, &text, color);

  // graph
  quad->y += 25;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer, quad);

  update_survive_conway_buttons(renderer, state, quad);
  // display legend ?

  int step = quad->w / NUM_GROWTH_CONWAY;
  int step_y = quad->h / 2;
  for (int x = 0 ; x < NUM_GROWTH_CONWAY ; x++) {
    i = quad->x + (x * step);

    if (state->survive_conway[x] == 0) {
      j = quad->y + quad->h;
    } else {
      j = quad->y;
    }

    if (x > 0) {
      SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
      SDL_RenderDrawLine(renderer, tmp_i, tmp_j, i, j);
    }
    tmp_i = i;
    tmp_j = j;

    // Draw thick point
    point.x = i - 2;
    point.y = j - 2;
    point.w = 5;
    point.h = 5;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &point);
  }
}

void draw_born(SDL_Renderer *renderer, menu_t *menu, state_t *state, SDL_Rect *quad) {
  quad->y += 80; // this is getting out of hand => what if WINDOW_HEIGHT is reduced
  quad->x = state->menu_pos_x + 5;
  quad->w = MENU_WIDTH - 10;
  quad->h = 60;
  int i,j,c,d,tmp_i,tmp_j,e;
  SDL_Rect point;
  SDL_Rect text;
  SDL_Color color = { 255, 255, 255 };

  // text
  char born[] = "Born";
  text.x = state->menu_pos_x + 5;
  text.y = quad->y;
  text.w = MENU_WIDTH - 10;
  text.h = 20;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer, &text);
  text.w = strlen(born) * VISIBLE_TEXT_SIZE;
  render_text(renderer, menu, born, &text, color);

  // graph
  quad->y += 25;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer, quad);

  update_born_conway_buttons(renderer, state, quad);
  // display legend ?

  int step = quad->w / NUM_GROWTH_CONWAY;
  int step_y = quad->h / 2;
  for (int x = 0 ; x < NUM_GROWTH_CONWAY ; x++) {
    i = quad->x + (x * step);

    if (state->born_conway[x] == 0) {
      j = quad->y + quad->h;
    } else {
      j = quad->y;
    }

    if (x > 0) {
      SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
      SDL_RenderDrawLine(renderer, tmp_i, tmp_j, i, j);
    }
    tmp_i = i;
    tmp_j = j;

    // Draw thick point
    point.x = i - 2;
    point.y = j - 2;
    point.w = 5;
    point.h = 5;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &point);
  }
}

void  draw_conway_menu(SDL_Renderer *renderer, menu_t *menu, state_t *state, SDL_Rect *quad) {
  draw_survive(renderer, menu, state, quad);
  draw_born(renderer, menu, state, quad);
}
