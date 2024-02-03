#include "includes/common.h"

void init_menu(sdl_t *sdl, menu_t *menu) {
	menu->font = TTF_OpenFont("assets/metropolis.regular.otf", 50); // not really readable under 50 ?
  if (menu->font == NULL) {
    printf("Failed to open font ! SDL_ttf error: %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }
}

void free_menu(menu_t *menu) {
	TTF_CloseFont(menu->font);
}

void open_menu(state_t *state) {
	state->menu_opened = TRUE;
	// state->cycle_running = FALSE;
}

void update_color(SDL_Color *color, Uint8 r, Uint8 g, Uint8 b) {
	color->r = r;
	color->g = g;
	color->b = b;
}

void render_text(SDL_Renderer *renderer, menu_t *menu, char *text, SDL_Rect *rect, SDL_Color color) {
	SDL_Surface *surface = TTF_RenderUTF8_Blended(menu->font, text, color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, texture, NULL, rect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void draw_rule_button(SDL_Renderer *renderer, menu_t *menu, state_t *state, SDL_Rect *render_quad) {
	SDL_Color color = { 255, 255, 255 };

	/* display all rules */
	// button conway
	render_quad->x = state->menu_pos_x + 20;
  render_quad->y += 50;
	char conway[] = "Conway";
  render_quad->w = strlen(conway) * VISIBLE_TEXT_SIZE;
  if (state->current_rule != CONWAY) {
  	update_color(&color, 127, 127, 127);
  }
  render_text(renderer, menu, conway, render_quad, color);
  SDL_Rect rect_conway = { render_quad->x - 10, render_quad->y - 10, MENU_WIDTH / 2 - 20, render_quad->h + 20 };
  state->conway_button.x = rect_conway.x;
  state->conway_button.y = rect_conway.y;
  state->conway_button.w = rect_conway.w;
  state->conway_button.h = rect_conway.h;
  if (state->current_rule == CONWAY) {
  	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  	SDL_RenderDrawRect(renderer, &rect_conway);
  }

	// button primordia
	render_quad->x = state->menu_pos_x + MENU_WIDTH / 2 + 10;
  char primordia[] = "Primordia";
  render_quad->w = strlen(primordia) * VISIBLE_TEXT_SIZE;
  if (state->current_rule == PRIMORDIA) {
  	update_color(&color, 255, 255, 255);
  } else {
  	update_color(&color, 127, 127, 127);
  }
  render_text(renderer, menu, primordia, render_quad, color);
  SDL_Rect rect_primordia = { render_quad->x - 10, render_quad->y - 10, MENU_WIDTH / 2 - 10, render_quad->h + 20 };
  state->primordia_button.x = rect_primordia.x;
  state->primordia_button.y = rect_primordia.y;
  state->primordia_button.w = rect_primordia.w;
  state->primordia_button.h = rect_primordia.h;
  if (state->current_rule == PRIMORDIA) {
  	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  	SDL_RenderDrawRect(renderer, &rect_primordia);
  }

  // next line

  // button lenia
  render_quad->y += 40;
	render_quad->x = state->menu_pos_x + 20;
  char lenia[] = "Lenia";
  render_quad->w = strlen(lenia) * VISIBLE_TEXT_SIZE;
  if (state->current_rule == LENIA) {
  	update_color(&color, 255, 255, 255);
  } else {
  	update_color(&color, 127, 127, 127);
  }
  render_text(renderer, menu, lenia, render_quad, color);
  SDL_Rect rect_lenia = { render_quad->x - 10, render_quad->y - 10, MENU_WIDTH / 2 - 20, render_quad->h + 20 };
  state->lenia_button.x = rect_lenia.x;
  state->lenia_button.y = rect_lenia.y;
  state->lenia_button.w = rect_lenia.w;
  state->lenia_button.h = rect_lenia.h;
  if (state->current_rule == LENIA) {
  	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  	SDL_RenderDrawRect(renderer, &rect_lenia);
  }
}

/* TODO: Lacks dynamism */
/* Behold fool ! leave at the door any convention expectation you may have */
void draw_menu(SDL_Renderer *renderer, menu_t *menu, state_t *state) {
	if (state->menu_opened == TRUE && state->menu_pos_x < 0) {
		state->menu_pos_x = 0;
	}

	/* Menu not displayed => display the display menu button */
	if (state->menu_pos_x <= -MENU_WIDTH) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &state->menu_button);
		return ;
	}

	/** Menu display **/
	
	/* background */
	if (state->current_rule == CONWAY) {
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // activates alpha blending for transparency
	}
	SDL_SetRenderDrawColor(renderer, 32, 32, 32, 216);
  SDL_Rect menuRect = { state->menu_pos_x, 0, MENU_WIDTH, WINDOW_HEIGHT };
  SDL_RenderFillRect(renderer, &menuRect);
	if (state->current_rule == CONWAY) {
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE); // deactivates alpha blending
	}
	SDL_Color color = { 255, 255, 255 };

	/* display title */
	SDL_Rect render_quad = {state->menu_pos_x + 10, 10, MENU_WIDTH - 20, 30};
	char title[] = "Game of life";
	render_text(renderer, menu, title, &render_quad, color);
	
	/* display instruction 1 */
	update_color(&color, 127, 127, 127);
	render_quad.h = 15;
	render_quad.y += 40;
	char instruction1[] = "Menu <Escape>";
	render_quad.w = strlen(instruction1) * VISIBLE_TEXT_SIZE;
	render_text(renderer, menu, instruction1, &render_quad, color);

	/* display instruction 2 */
	render_quad.y += 20;
	char instruction2[] = "Pause <Space>";
	render_quad.w = strlen(instruction2) * VISIBLE_TEXT_SIZE;
	render_text(renderer, menu, instruction2, &render_quad, color);

	/* display instruction 3 */
	render_quad.y += 20;
	char instruction3[] = "Create <left click>";
	render_quad.w = strlen(instruction3) * VISIBLE_TEXT_SIZE;
	render_text(renderer, menu, instruction3, &render_quad, color);

	/* display Cycle count */
	update_color(&color, 255, 255, 255);
	render_quad.y += 40;
	char cycle[] = "Cycle:";
	render_quad.w = strlen(cycle) * VISIBLE_TEXT_SIZE;
	render_text(renderer, menu, cycle, &render_quad, color);

	update_color(&color, 0, 255, 255);
	render_quad.x = state->menu_pos_x + MENU_WIDTH - 100;
  char counterText[18]; /* TODO: risky */
  snprintf(counterText, sizeof(counterText), "%d", state->cycle_count);
  render_quad.w = strlen(counterText) * VISIBLE_TEXT_SIZE;
  render_text(renderer, menu, counterText, &render_quad, color);

  /* display Cells count(?lenia) */
	update_color(&color, 255, 255, 255);
	render_quad.x = state->menu_pos_x + 10;
	render_quad.y += 20;
	char alive[] = "Alive:";
	render_quad.w = strlen(alive) * VISIBLE_TEXT_SIZE;
	render_text(renderer, menu, alive, &render_quad, color);

	update_color(&color, 0, 255, 255);
	render_quad.x = state->menu_pos_x + MENU_WIDTH - 100;
  char counterText2[18]; /* TODO: risky */
  snprintf(counterText2, sizeof(counterText), "%d", state->cells_count);
  render_quad.w = strlen(counterText2) * VISIBLE_TEXT_SIZE;
  render_text(renderer, menu, counterText2, &render_quad, color);

  /* display Reset button */
  update_color(&color, 127, 127, 127);
  render_quad.x = state->menu_pos_x + 20;
  render_quad.y += 40;
  char reset[] = "Reset";
  render_quad.w = strlen(reset) * VISIBLE_TEXT_SIZE;
  render_text(renderer, menu, reset, &render_quad, color);
  SDL_Rect rect_reset = {render_quad.x - 10,render_quad.y - 10,MENU_WIDTH / 2 - 20,render_quad.h + 20};
  state->reset_button.x = rect_reset.x;
  state->reset_button.y = rect_reset.y;
  state->reset_button.w = rect_reset.w;
  state->reset_button.h = rect_reset.h;
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderDrawRect(renderer, &rect_reset);

  /* display Pause button */
  update_color(&color, 127, 127, 127);
  render_quad.x = state->menu_pos_x + MENU_WIDTH / 2 + 10;
  char message[10];
  if (state->cycle_running) {
  	strcpy(message, "Pause");
  } else {
  	strcpy(message, "Play");
  }
  render_quad.w = strlen(message) * VISIBLE_TEXT_SIZE;
  render_text(renderer, menu, message, &render_quad, color);
  SDL_Rect rect_pause = {render_quad.x - 10,render_quad.y - 10,MENU_WIDTH / 2 - 10,render_quad.h + 20};
  state->pause_button.x = rect_pause.x;
  state->pause_button.y = rect_pause.y;
  state->pause_button.w = rect_pause.w;
  state->pause_button.h = rect_pause.h;
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderDrawRect(renderer, &rect_pause);

  /* display RULE */
  draw_rule_button(renderer, menu, state, &render_quad);
  if (state->current_rule == PRIMORDIA) {
		draw_primordia_menu(renderer, menu, state, &render_quad);
  }
}
