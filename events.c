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

int mouse_on_button(SDL_Rect button, state_t *state) {
  if (state->mouse_pos_x >= button.x && state->mouse_pos_x < button.x + button.w
    && state->mouse_pos_y >= button.y && state->mouse_pos_y < button.y + button.h) {
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
      if (!state->menu_opened && mouse_on_button(state->menu_button, state)) {
        open_menu(state);
      } else if (state->menu_opened) {
        if (mouse_on_button(state->reset_button, state)) {
          reset_game(state, grid);
        } else if (mouse_on_button(state->pause_button, state)) {
          toggle_pause(state);
        } else if (mouse_on_button(state->conway_button, state) && state->current_rule != CONWAY) {
          state->current_rule = CONWAY;
          reset_game(state, grid);
        } else if (mouse_on_button(state->primordia_button, state) && state->current_rule != PRIMORDIA) {
          state->current_rule = PRIMORDIA;
          reset_game(state, grid);
        } else if (mouse_on_button(state->lenia_button, state) && state->current_rule != LENIA) {
          state->current_rule = LENIA;
          reset_game(state, grid);
        } else if (state->current_rule == PRIMORDIA && update_primordia_graph(state)) {
          // do nothing ?
        } else {
          state->holding_left_mouse = TRUE;
        }
      } else {
        state->holding_left_mouse = TRUE;
      }
    }
    return;
  }

  if (event->type == SDL_MOUSEBUTTONUP) {
    if (event->button.button == SDL_BUTTON_LEFT) {
      if ((state->menu_opened && event->button.x > MENU_WIDTH) || !state->menu_opened) {
        grid[event->button.x/SCALE][event->button.y/SCALE] = 1;
      }
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
        state->menu_pos_x = -MENU_WIDTH;
      }
    }
  }
}
