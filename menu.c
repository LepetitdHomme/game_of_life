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
	state->cycle_running = FALSE;
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

/* TODO: Lacks dynamism */
void draw_menu(SDL_Renderer *renderer, menu_t *menu, state_t *state) {
	/* animate menu */
	if (state->menu_opened == TRUE && state->menu_pos_x < 0) {
		state->menu_pos_x += MENU_ANIMATION_SPEED;
	} else if (state->menu_opened == FALSE && state->menu_pos_x > -MENU_WIDTH) {
		state->menu_pos_x -= MENU_ANIMATION_SPEED;
	}

	/* Menu not displayed => display menu button */
	if (state->menu_pos_x <= -MENU_WIDTH) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &state->menu_button);
		return ;
	}

	/** Menu display **/
	
	/* background */
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // activates alpha blending for transparency
	SDL_SetRenderDrawColor(renderer, 32, 32, 32, 100);
  SDL_Rect menuRect = { state->menu_pos_x, 0, MENU_WIDTH, WINDOW_HEIGHT };
  SDL_RenderFillRect(renderer, &menuRect);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE); // deactivates alpha blending
	SDL_Color color = { 255, 255, 255 };

	/* title */
	SDL_Rect render_quad = {state->menu_pos_x + 10, 10, MENU_WIDTH - 20, 30};
	char title[] = "Game of life";
	render_text(renderer, menu, title, &render_quad, color);
	
	update_color(&color, 127, 127, 127);
	// display instruction 1
	render_quad.h = 15;
	render_quad.y += 40;
	char instruction1[] = "Menu <Escape>";
	render_quad.w = strlen(instruction1) * VISIBLE_TEXT_SIZE;
	render_text(renderer, menu, instruction1, &render_quad, color);

	// display instruction 2
	render_quad.y += 20;
	char instruction2[] = "Pause <Space>";
	render_quad.w = strlen(instruction2) * VISIBLE_TEXT_SIZE;
	render_text(renderer, menu, instruction2, &render_quad, color);

	// display instruction 3
	render_quad.y += 20;
	char instruction3[] = "Create <left click>";
	render_quad.w = strlen(instruction3) * VISIBLE_TEXT_SIZE;
	render_text(renderer, menu, instruction3, &render_quad, color);

	/* Cycle count */
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

  /* Cells count(?lenia) */
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
}
