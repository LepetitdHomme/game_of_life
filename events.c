#include "includes/common.h"

void  toggle_pause(state_t *state) {
  if(state->cycle_running == TRUE) {
    // printf("cycle stopped\n");
    state->cycle_running = FALSE;
  } else {
    // printf("cycle running\n");
    state->cycle_running = TRUE;
  }  
}

int mouse_on_button(int mouse_x, int mouse_y, SDL_Rect button) {
  if (mouse_x >= button.x && mouse_x < button.x + button.w
    && mouse_y >= button.y && mouse_y < button.y + button.h) {
    return 1;
  } else {
    return 0;
  }
}

void handle_event(state_t *state, float (*grid)[GRID_H], SDL_Event *event) {
  if (event->type == SDL_QUIT) {
    state->quit = TRUE;
  }

  /* MOUSE */
  SDL_GetMouseState(&state->mouse_pos_x,&state->mouse_pos_y); /* ensure not to call this multiple times */

  if (event->type == SDL_MOUSEBUTTONDOWN) {
    if (event->button.button == SDL_BUTTON_LEFT) {
      if (mouse_on_button(state->mouse_pos_x, state->mouse_pos_y, state->menu_button)) {
        open_menu(state);
      } else {
        state->holding_left_mouse = TRUE;
      }
    }
    return;
  }

  if (event->type == SDL_MOUSEBUTTONUP) {
    if (event->button.button == SDL_BUTTON_LEFT) {
      grid[event->button.x/SCALE][event->button.y/SCALE] = 1;
    }
    state->holding_left_mouse = FALSE;
    return;
  }

  if (event->type == SDL_MOUSEMOTION && state->holding_left_mouse == 1) {
    int x = state->mouse_pos_x / SCALE;
    int y = state->mouse_pos_y / SCALE;
    if (is_in_grid(x, y)) {
      grid[x][y] = 1;
    }
    return;
  }

  /* KEYS */
  if (event->type == SDL_KEYDOWN) {
    /* runs or pauses life cycle */
    if (event->key.keysym.sym == SDLK_SPACE) {
      toggle_pause(state);
    }

    /* Ensure pause / Menu */
    if (event->key.keysym.sym == SDLK_ESCAPE) { // KEY UP instead ?
      if (state->menu_opened == FALSE) {
        open_menu(state);
      } else {
        state->menu_opened = FALSE;
      }
    }
  }
}
