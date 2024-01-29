#include "includes/common.h"

void handle_event(state_t *state, float (*grid)[GRID_H], SDL_Event *event) {
  if (event->type == SDL_QUIT) {
    state->quit = TRUE;
  }

  /* MOUSE */
  if (event->type == SDL_MOUSEBUTTONDOWN) {
    if (event->button.button == SDL_BUTTON_LEFT) {
      state->holding_left_mouse = TRUE;
    }
  }

  if (event->type == SDL_MOUSEBUTTONUP) {
    if (event->button.button == SDL_BUTTON_LEFT) {
      grid[event->button.x/SCALE][event->button.y/SCALE] = 1;
    }
    state->holding_left_mouse = FALSE;
  }

  if (event->type == SDL_MOUSEMOTION && state->holding_left_mouse == 1) {
    SDL_GetMouseState(&state->mouse_pos_x,&state->mouse_pos_y);
    grid[state->mouse_pos_x/SCALE][state->mouse_pos_y/SCALE] = 1;
  }

  /* KEYS */
  if (event->type == SDL_KEYDOWN) {
    /* runs or pauses life cycle */
    if (event->key.keysym.sym == SDLK_SPACE) {
      if(state->cycle_running == TRUE) {
        printf("cycle stopped\n");
        state->cycle_running = FALSE;
      } else {
        printf("cycle running\n");
        state->cycle_running = TRUE;
      }
    }
  }
}
