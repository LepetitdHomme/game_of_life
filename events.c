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

void reset_game(state_t *state, float (*grid)[GRID_H]) {
  switch (state->current_rule) {
    case PRIMORDIA:
      init_primordia(grid);
      break;
    case LENIA:
      init_lenia(grid);
      break;
    default:
      reinitialize_grid(grid);
  }
  state->cycle_running = 0;
  state->cycle_count = 0;
  state->cells_count = 0;
}

int mouse_on_button(SDL_Rect button, int mouse_x, int mouse_y) {
  if (mouse_x >= button.x && mouse_x < button.x + button.w
    && mouse_y >= button.y && mouse_y < button.y + button.h) {
    return 1;
  } else {
    return 0;
  }
}

/* Ugly returns instead of switch case */
void handle_event(state_t *state, float (*grid)[GRID_H], SDL_Event *event) {
  if (event->type == SDL_QUIT) {
    state->quit = TRUE;
  }

  /* MOUSE */
  SDL_GetMouseState(&state->mouse_pos_x,&state->mouse_pos_y); /* ensure not to call this multiple times */

  if (event->type == SDL_MOUSEBUTTONDOWN) {
    if (event->button.button == SDL_BUTTON_LEFT) {
      if (mouse_on_button(state->menu_button, state->mouse_pos_x, state->mouse_pos_y)) {
        open_menu(state);
      } else if (mouse_on_button(state->reset_button, state->mouse_pos_x, state->mouse_pos_y)) {
        reset_game(state, grid);
      } else if (mouse_on_button(state->pause_button, state->mouse_pos_x, state->mouse_pos_y)) {
        toggle_pause(state);
      } else if (mouse_on_button(state->conway_button, state->mouse_pos_x, state->mouse_pos_y)) {
        if (state->current_rule != CONWAY) {
          state->current_rule = CONWAY;
          reset_game(state, grid);
        }
      } else if (mouse_on_button(state->primordia_button, state->mouse_pos_x, state->mouse_pos_y)) {
        if (state->current_rule != PRIMORDIA) {
          state->current_rule = PRIMORDIA;
          reset_game(state, grid);
        }
      } else if (mouse_on_button(state->lenia_button, state->mouse_pos_x, state->mouse_pos_y)) {
        if (state->current_rule != LENIA) {
          state->current_rule = LENIA;
          reset_game(state, grid);
        }
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
