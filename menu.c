#include "includes/common.h"

void init_menu(sdl_t *sdl, menu_t *menu) {
  // Prepare menu text rendering
  SDL_Color textColor = {255, 255, 255};

  SDL_Surface *textSurface = TTF_RenderText_Solid(sdl->font, "Game of life", textColor);
  menu->texture_title = SDL_CreateTextureFromSurface(sdl->renderer, textSurface);
  SDL_FreeSurface(textSurface);

  textSurface = TTF_RenderText_Solid(sdl->font, "Menu <Escape>", textColor);
  menu->texture_instruction_1 = SDL_CreateTextureFromSurface(sdl->renderer, textSurface);
  SDL_FreeSurface(textSurface);

  textSurface = TTF_RenderText_Solid(sdl->font, "Pause <Space>", textColor);
  menu->texture_instruction_2 = SDL_CreateTextureFromSurface(sdl->renderer, textSurface);
  SDL_FreeSurface(textSurface);

  textSurface = TTF_RenderText_Solid(sdl->font, "Create <left click>", textColor);
  menu->texture_instruction_3 = SDL_CreateTextureFromSurface(sdl->renderer, textSurface);
  SDL_FreeSurface(textSurface);
}

void free_menu(menu_t *menu) {
	SDL_DestroyTexture(menu->texture_title);
	SDL_DestroyTexture(menu->texture_instruction_1);
	SDL_DestroyTexture(menu->texture_instruction_1);
	SDL_DestroyTexture(menu->texture_instruction_1);
}

void open_menu(state_t *state) {
	state->menu_opened = TRUE;
	state->cycle_running = FALSE;
}

void draw_menu(SDL_Renderer *renderer, menu_t *menu, state_t *state) {
	/* animate menu */
	if (state->menu_opened == TRUE && state->menu_pos_x < 0) {
		state->menu_pos_x += MENU_ANIMATION_SPEED;
	} else if (state->menu_opened == FALSE && state->menu_pos_x > -MENU_WIDTH) {
		state->menu_pos_x -= MENU_ANIMATION_SPEED;
	}

	if (state->menu_pos_x <= -MENU_WIDTH) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &state->menu_button);
	} else {
		// displays menu background
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // activates alpha blending for transparency
		SDL_SetRenderDrawColor(renderer, 32, 32, 32, 100);
	  SDL_Rect menuRect = { state->menu_pos_x, 0, MENU_WIDTH, WINDOW_HEIGHT };
	  SDL_RenderFillRect(renderer, &menuRect);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE); // deactivates alpha blending

		/* ugly as F => how to make size proportional to text if text is already a texture ? */
		// display title
		SDL_Rect render_quad = {state->menu_pos_x + 10, 10, MENU_WIDTH - 20, 30};
		SDL_RenderCopy(renderer, menu->texture_title, NULL, &render_quad);
		
		render_quad.x = state->menu_pos_x + 15;
		render_quad.w = MENU_WIDTH - 50;
		render_quad.h = 20;
		// display instruction 1
		render_quad.y += 40;
		SDL_RenderCopy(renderer, menu->texture_instruction_1, NULL, &render_quad);
		// display instruction 2
		render_quad.y += 40;
		SDL_RenderCopy(renderer, menu->texture_instruction_2, NULL, &render_quad);
		// display instruction 3
		render_quad.y += 40;
		SDL_RenderCopy(renderer, menu->texture_instruction_3, NULL, &render_quad);		
	}
}
