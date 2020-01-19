#include <RPS/BD.h>

void show_error(void) {

	SDL_Log("%s\n", SDL_GetError());
	SDL_ClearError();
}

void show_image_error(void) {

	SDL_Log("%s\n", IMG_GetError());
}

void show_ttf_error(void) {

	SDL_Log("%s\n", TTF_GetError());
}

void show_mix_error(void) {

	SDL_Log("%s\n", Mix_GetError());
}
