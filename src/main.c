#include <RPS/BD.h>

int main(void) {

	int flags = IMG_INIT_PNG;
	int initted_flags;

	if(strcmp(SDL_GetPlatform(), "Linux") == 0) {
		
		/*prevents circumvent failure of SDL_Init() when not using SDL_main() as an entry point*/
		SDL_SetMainReady();

		if(SDL_Init(  SDL_INIT_VIDEO 
					| SDL_INIT_TIMER
					| SDL_INIT_AUDIO
					| SDL_INIT_EVENTS) != 0) {

			show_error();
			exit(EXIT_FAILURE);
		}

		initted_flags = IMG_Init(flags);
		if((initted_flags & flags) != flags) {
			fprintf(stderr, "%s", "IMG_Init: Failed to init sdl image.");
			show_image_error();
			SDL_Quit();
			exit(EXIT_FAILURE);
		}

		if(TTF_Init() == -1) {
			fprintf(stderr, "%s", "TTF_Init: Failed to init sdl ttf.");
			show_ttf_error();
			IMG_Quit();
			SDL_Quit();
			exit(EXIT_FAILURE);
		}

		Mix_Init(0);

		srand(time(NULL));

		build_game(); /*continues with "basics.c"*/

		Mix_Quit();
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();

		return 0; 
	}
	else {
		fprintf(stderr, "Boulder Dash doesn't support %s. Boulder dash developed for Linux environment.\n", SDL_GetPlatform());
	}

	return 1;
}
