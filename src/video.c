#include <RPS/BD.h>

SDL_Window* build_window(void) {

	SDL_Window *window = SDL_CreateWindow("Boulder Dash", 
											SDL_WINDOWPOS_CENTERED,
											SDL_WINDOWPOS_CENTERED,
											WINDOW_WIDTH,
											WINDOW_HEIGHT,
											SDL_WINDOW_RESIZABLE |
											SDL_WINDOW_FULLSCREEN_DESKTOP);
	SDL_Surface *surface_icon = NULL;

	if(!window) {
		show_error();
		return NULL;
	}

	surface_icon = IMG_Load("Resources/Images/icon.png");
	if(surface_icon == NULL) {
		show_image_error();
	}

	SDL_SetWindowIcon(window, surface_icon);

	SDL_FreeSurface(surface_icon);

	return window;
}

SDL_Renderer* build_renderer(SDL_Window *window) {

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer) {
		show_error();
		return NULL;
	}
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	return renderer;
}

void init_textures(SDL_Texture **textures, const int size) {

	int i = 0;

	for(i = 0; i < size; ++i) {
		textures[i] = NULL;
	}
}

void init_fade(Fade *const fade, Uint64 *timer_start) {

	fade->time = 0.0;
	fade->last_time = 0.0;
	fade->fade_time = 0;
	fade->alpha = 0;
	fade->state = FADE_STATE_NO_FADE;
	fade->full_cycle = FALSE;
	fade->timer_start = timer_start;
}

void get_window_size(SDL_Window *const window, WindowInfo *const info_window) {

	SDL_GetWindowSize(window, &(info_window->width), &(info_window->height));
}

void load_textures(Game *const game) {

	load_textures_map(game->video.textures.map, game->video.renderer, &(game->level));
	load_textures_hud_fonts(game);
}

void load_textures_map(SDL_Texture **textures_map, SDL_Renderer *renderer, const Level *const level) {

	if(textures_map[TEXTURE_MAP_TILESET] == NULL) {
		textures_map[TEXTURE_MAP_TILESET] = get_tileset(renderer, level);
	}
}

void load_textures_hud_fonts(Game *const game) {

	load_textures_hud_time(&(game->video.textures.hud[TEXTURE_TEXT_TIME]), game->video.renderer, game->video.hud.fonts[FONT_MENU], &(game->level));
	load_textures_hud_score(&(game->video.textures.hud[TEXTURE_TEXT_SCORE]), game->video.renderer, game->video.hud.fonts[FONT_MENU], &(game->player));
	load_textures_hud_diamond(&(game->video.textures.hud[TEXTURE_TEXT_DIAMOND]), game->video.renderer, game->video.hud.fonts[FONT_MENU], &(game->level.gate));
}

void load_textures_hud_time(SDL_Texture **texture, SDL_Renderer *renderer, TTF_Font *font, const Level *const level) {

	SDL_Color white = { .r = 255, 
						.g = 255, 
						.b = 255,
						.a = 255
					};
	int time = 0;
	char str_time[4];

	time = (int)level->time;

	convert_time_to_string(time, str_time);

	free_textures(texture, 1);

	*texture = get_text(renderer, font, str_time, &white);
}

void load_textures_hud_score(SDL_Texture **texture, SDL_Renderer *renderer, TTF_Font *font, const Player *const player) {

	SDL_Color white = { .r = 255, 
						.g = 255, 
						.b = 255,
						.a = 255
					};
	int score = 0;
	char str_score[5];

	score = player->score.point;

	convert_score_to_string(score, str_score);

	free_textures(texture, 1);

	*texture = get_text(renderer, font, str_score, &white);
	
}

void load_textures_hud_diamond(SDL_Texture **texture, SDL_Renderer *renderer, TTF_Font *font, const Gate *const gate) {

	SDL_Color white = { .r = 255, 
						.g = 255, 
						.b = 255,
						.a = 255
					};
	int diamond = 0;
	char str_diamond[4];

	diamond = gate->diamonds_to_open;

	/*same length as time*/
	convert_time_to_string(diamond, str_diamond);

	free_textures(texture, 1);

	*texture = get_text(renderer, font, str_diamond, &white);
}

void load_textures_perm(SDL_Texture **textures, SDL_Renderer *renderer, TTF_Font **fonts) {

	SDL_Color white = {
						.r = 255,
						.g = 255,
						.b = 255,
						.a = 255
					};
	SDL_Surface *surface = NULL;

	textures[TEXTURE_PERM_PAUSE] = get_text(renderer, fonts[FONT_MENU], "PAUSE", &white);

	surface = get_surface("Resources/Images/start_screen.png");
	textures[TEXTURE_PERM_START_SCREEN] = get_texture(renderer, surface);
	SDL_FreeSurface(surface);

	textures[TEXTURE_PERM_START] = get_text(renderer, fonts[FONT_MENU], "Press \"Enter\" to start!!!", &white);
	textures[TEXTURE_PERM_QUIT] = get_text(renderer, fonts[FONT_MENU], "Press \"ESC\" to quit...", &white);

	surface = get_surface("Resources/Images/miscellaneous.png");
	textures[TEXTURE_PERM_MISC] = get_texture(renderer, surface);
	SDL_FreeSurface(surface);

	textures[TEXTURE_PERM_GO] = get_text(renderer, fonts[FONT_MENU], "Press \"Enter\" to go", &white);
	textures[TEXTURE_PERM_WORLD] = get_text(renderer, fonts[FONT_MENU], "World", &white);
	textures[TEXTURE_PERM_LEVEL] = get_text(renderer, fonts[FONT_MENU], "Level", &white);

	textures[TEXTURE_PERM_LEVEL_SELECT] = get_text(renderer, fonts[FONT_MENU], "LEVEL SELECT", &white);

	textures[TEXTURE_PERM_CHAR_X] = get_text(renderer, fonts[FONT_MENU], "x", &white);

	textures[TEXTURE_PERM_PLAYER_LIVE] = get_text(renderer, fonts[FONT_MENU], "3", &white);

	textures[TEXTURE_PERM_SETTINGS] = get_text(renderer, fonts[FONT_MENU], "SETTINGS", &white);

	textures[TEXTURE_PERM_RESTART] = get_text(renderer, fonts[FONT_MENU], "RESTART (LIFE -1)", &white);

	textures[TEXTURE_PERM_LEVEL_SCREEN] = get_text(renderer, fonts[FONT_MENU], "LEVEL SCREEN (LIFE -1)", &white);

	textures[TEXTURE_PERM_SAVE_GAME] = get_text(renderer, fonts[FONT_MENU], "SAVE GAME", &white);

	textures[TEXTURE_PERM_LOAD_SAVE] = get_text(renderer, fonts[FONT_MENU], "LOAD SAVE", &white);

	textures[TEXTURE_PERM_QUIT_GAME] = get_text(renderer, fonts[FONT_MENU], "QUIT GAME", &white);

	textures[TEXTURE_PERM_WIN] = get_text(renderer, fonts[FONT_MENU], "!!! YOU WON !!!", &white);

	textures[TEXTURE_PERM_LOSE] = get_text(renderer, fonts[FONT_MENU], "... you lost ...", &white);

	textures[TEXTURE_PERM_FPS_LOCK] = get_text(renderer, fonts[FONT_MENU], "FPS LOCK", &white);

	textures[TEXTURE_PERM_SHOW_FPS] = get_text(renderer, fonts[FONT_MENU], "SHOW FPS", &white);

	textures[TEXTURE_PERM_WINDOW_MODE] = get_text(renderer, fonts[FONT_MENU], "WINDOW MODE", &white);

	textures[TEXTURE_PERM_VOLUME] = get_text(renderer, fonts[FONT_MENU], "VOLUME", &white);

	textures[TEXTURE_PERM_ON] = get_text(renderer, fonts[FONT_MENU], "ON", &white);

	textures[TEXTURE_PERM_OFF] = get_text(renderer, fonts[FONT_MENU], "OFF", &white);

	textures[TEXTURE_PERM_240] = get_text(renderer, fonts[FONT_MENU], "240", &white);

	textures[TEXTURE_PERM_160] = get_text(renderer, fonts[FONT_MENU], "160", &white);

	textures[TEXTURE_PERM_144] = get_text(renderer, fonts[FONT_MENU], "144", &white);

	textures[TEXTURE_PERM_120] = get_text(renderer, fonts[FONT_MENU], "120", &white);

	textures[TEXTURE_PERM_75] = get_text(renderer, fonts[FONT_MENU], "75", &white);

	textures[TEXTURE_PERM_60] = get_text(renderer, fonts[FONT_MENU], "60", &white);

	textures[TEXTURE_PERM_30] = get_text(renderer, fonts[FONT_MENU], "30", &white);

	textures[TEXTURE_PERM_FULLSCREEN] = get_text(renderer, fonts[FONT_MENU], "FULLSCREEN", &white);

	textures[TEXTURE_PERM_BORDERLESS] = get_text(renderer, fonts[FONT_MENU], "BORDERLESS", &white);

	textures[TEXTURE_PERM_WINDOWED] = get_text(renderer, fonts[FONT_MENU], "WINDOWED", &white);

	textures[TEXTURE_PERM_CAMERA_SPEED] = get_text(renderer, fonts[FONT_MENU], "CAMERA SPEED", &white);

	textures[TEXTURE_PERM_100] = get_text(renderer, fonts[FONT_MENU], "100", &white);

	textures[TEXTURE_PERM_90] = get_text(renderer, fonts[FONT_MENU], "90", &white);

	textures[TEXTURE_PERM_80] = get_text(renderer, fonts[FONT_MENU], "80", &white);

	textures[TEXTURE_PERM_70] = get_text(renderer, fonts[FONT_MENU], "70", &white);

	textures[TEXTURE_PERM_50] = get_text(renderer, fonts[FONT_MENU], "50", &white);

	textures[TEXTURE_PERM_40] = get_text(renderer, fonts[FONT_MENU], "40", &white);

	textures[TEXTURE_PERM_20] = get_text(renderer, fonts[FONT_MENU], "20", &white);

	textures[TEXTURE_PERM_10] = get_text(renderer, fonts[FONT_MENU], "10", &white);

	textures[TEXTURE_PERM_0] = get_text(renderer, fonts[FONT_MENU], "0", &white);

	textures[TEXTURE_PERM_MUTE] = get_text(renderer, fonts[FONT_MENU], "MUTE", &white);

	textures[TEXTURE_PERM_MUSIC_VOLUME] = get_text(renderer, fonts[FONT_MENU], "MUSIC VOLUME", &white);

	textures[TEXTURE_PERM_SFX_VOLUME] = get_text(renderer, fonts[FONT_MENU], "SFX VOLUME", &white);

	textures[TEXTURE_PERM_YES] = get_text(renderer, fonts[FONT_MENU], "YES", &white);

	textures[TEXTURE_PERM_NO] = get_text(renderer, fonts[FONT_MENU], "NO", &white);

	textures[TEXTURE_PERM_OVERWRITE] = get_text(renderer, fonts[FONT_MENU], "THIS OPERATION OVERWRITES!", &white);

	textures[TEXTURE_PERM_ASU] = get_text(renderer, fonts[FONT_MENU], "ARE YOU SURE?", &white);

	textures[TEXTURE_PERM_PROGRESS] = get_text(renderer, fonts[FONT_MENU], "YOU WILL LOSE UNSAVED PROGRESS!", &white);

	textures[TEXTURE_PERM_FAIL_SAVE] = get_text(renderer, fonts[FONT_MENU], "FAILED TO SAVE!", &white);

	textures[TEXTURE_PERM_FAIL_LOAD] = get_text(renderer, fonts[FONT_MENU], "FAILED TO LOAD!", &white);

	textures[TEXTURE_PERM_GAME_RESTART] = get_text(renderer, fonts[FONT_MENU], "Would you like to restart game?", &white);

	textures[TEXTURE_PERM_NEW_GAME] = get_text(renderer, fonts[FONT_MENU], "NEW GAME", &white);

	textures[TEXTURE_PERM_EASY] = get_text(renderer, fonts[FONT_MENU], "EASY", &white);	

	textures[TEXTURE_PERM_NORMAL] = get_text(renderer, fonts[FONT_MENU], "NORMAL", &white);	

	textures[TEXTURE_PERM_HARD] = get_text(renderer, fonts[FONT_MENU], "HARD", &white);	

	textures[TEXTURE_PERM_IMPOSSIBLE] = get_text(renderer, fonts[FONT_MENU], "IMPOSSIBLE (NO SAVE)", &white);

	textures[TEXTURE_PERM_CANT_SAVE] = get_text(renderer, fonts[FONT_MENU], "You can't save in IMPOSSIBLE mode", &white);	
}

SDL_Texture* get_tileset(SDL_Renderer *renderer, const Level *const level) {

	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;
	char *f_location = NULL;

	f_location = get_level_tileset(level->levelID);

	surface = IMG_Load(f_location);
	if(surface == NULL) {
		show_error();
	}
	else {
		/*colorkey changes a rgb color to a transparent pyxel*/
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, level->color_key.r, level->color_key.g, level->color_key.b));
	}

	texture = get_texture(renderer, surface);

	SDL_FreeSurface(surface);
	free(f_location);

	return texture;
}

SDL_Texture* get_texture(SDL_Renderer *renderer, SDL_Surface *surface) {

	SDL_Texture *texture = NULL;

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(texture == NULL) {
		show_error();
	}

	return texture;
}

SDL_Surface* get_surface(char *f_location) {

	SDL_Surface *surface = NULL;

	surface = IMG_Load(f_location);
	if(surface == NULL) {
		show_error();
	}

	return surface;
}

void render_settings_val(Game *const game) {

	if(game->settings.fps.lock == FALSE) {
		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_OFF],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_FPS_LOCK_VAL]));
	}
	else {
		switch(game->settings.fps.per_second) {
			case 240:
				SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_240],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_FPS_LOCK_VAL]));
				break;
			case 160:
				SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_160],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_FPS_LOCK_VAL]));
				break;
			case 144:
				SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_144],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_FPS_LOCK_VAL]));
				break;
			case 120:
				SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_120],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_FPS_LOCK_VAL]));
				break;
			case 75:
				SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_75],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_FPS_LOCK_VAL]));
				break;
			case 60:
				SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_60],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_FPS_LOCK_VAL]));
				break;
			case 30:
				SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_30],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_FPS_LOCK_VAL]));
				break;
		}
	}

	if(game->settings.fps.show == FALSE) {
		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_OFF],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_SHOW_FPS_VAL]));
	}
	else {
		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_ON],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_SHOW_FPS_VAL]));	
	}

	switch(game->screen.info_window.mode) {
		case WINDOW_MODE_WINDOWED:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_WINDOWED],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_WINDOW_MODE_VAL]));
			break;
		case WINDOW_MODE_BORDERLESS:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_BORDERLESS],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_WINDOW_MODE_VAL]));
			break;
		case WINDOW_MODE_FULLSCREEN:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_FULLSCREEN],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_WINDOW_MODE_VAL]));
			break;
	}

	switch((int)(game->screen.camera.speed * 100)) {
		case 100:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_100],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_CAMERA_SPEED_VAL]));
			break;
		case 90:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_90],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_CAMERA_SPEED_VAL]));
			break;
		case 80:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_80],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_CAMERA_SPEED_VAL]));
			break;
		case 70:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_70],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_CAMERA_SPEED_VAL]));
			break;
		case 60:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_60],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_CAMERA_SPEED_VAL]));
			break;
		case 50:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_50],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_CAMERA_SPEED_VAL]));
			break;
		case 40:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_40],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_CAMERA_SPEED_VAL]));
			break;
		case 30:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_30],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_CAMERA_SPEED_VAL]));
			break;
		case 20:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_20],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_CAMERA_SPEED_VAL]));
			break;
		case 10:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_10],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_CAMERA_SPEED_VAL]));
			break;
	}
}

void render_volume_settings_val(Game *const game) {

	if(game->audio.mute == FALSE) {
		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_OFF],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_MUTE_VAL]));
	}
	else {
		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_ON],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_MUTE_VAL]));	
	}

	switch(game->audio.fake_volume_music) {
		case 100:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_100],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_MUSIC_VOLUME_VAL]));
			break;
		case 90:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_90],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_MUSIC_VOLUME_VAL]));
			break;
		case 80:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_80],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_MUSIC_VOLUME_VAL]));
			break;
		case 70:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_70],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_MUSIC_VOLUME_VAL]));
			break;
		case 60:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_60],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_MUSIC_VOLUME_VAL]));
			break;
		case 50:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_50],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_MUSIC_VOLUME_VAL]));
			break;
		case 40:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_40],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_MUSIC_VOLUME_VAL]));
			break;
		case 30:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_30],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_MUSIC_VOLUME_VAL]));
			break;
		case 20:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_20],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_MUSIC_VOLUME_VAL]));
			break;
		case 10:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_10],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_MUSIC_VOLUME_VAL]));
			break;
		case 0:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_0],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_MUSIC_VOLUME_VAL]));
			break;
	}

	switch(game->audio.fake_volume_sfx) {
		case 100:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_100],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_SFX_VOLUME_VAL]));
			break;
		case 90:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_90],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_SFX_VOLUME_VAL]));
			break;
		case 80:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_80],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_SFX_VOLUME_VAL]));
			break;
		case 70:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_70],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_SFX_VOLUME_VAL]));
			break;
		case 60:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_60],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_SFX_VOLUME_VAL]));
			break;
		case 50:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_50],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_SFX_VOLUME_VAL]));
			break;
		case 40:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_40],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_SFX_VOLUME_VAL]));
			break;
		case 30:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_30],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_SFX_VOLUME_VAL]));
			break;
		case 20:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_20],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_SFX_VOLUME_VAL]));
			break;
		case 10:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_10],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_SFX_VOLUME_VAL]));
			break;
		case 0:
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_0],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_SFX_VOLUME_VAL]));
			break;
	}
}

void render_player_live(Game *const game) {

	SDL_Color white = {
						.r = 255,
						.g = 255,
						.b = 255,
						.a = 255,
	};

	char str_player_live[3];
	int player_live_digit = 1;

	player_live_digit = get_digit_count(game->player.lives);

	sprintf(str_player_live, "%d", game->player.lives);

	game->video.perm_textures.rects[RECT_PERM_DES_PAUSE_CHARACTER].x = (game->screen.info_window.width - TILE_WIDTH - game->video.perm_textures.rects[RECT_PERM_DES_CHAR_X].w -
																			game->video.perm_textures.rects[RECT_PERM_DES_PLAYER_LIVE].w * player_live_digit) / 2;

	game->video.perm_textures.rects[RECT_PERM_DES_CHAR_X].x = game->video.perm_textures.rects[RECT_PERM_DES_PAUSE_CHARACTER].x + game->video.perm_textures.rects[RECT_PERM_DES_PAUSE_CHARACTER].w + 5;

	game->video.perm_textures.rects[RECT_PERM_DES_PLAYER_LIVE].x = game->video.perm_textures.rects[RECT_PERM_DES_PAUSE_CHARACTER].x +
																	game->video.perm_textures.rects[RECT_PERM_DES_PAUSE_CHARACTER].w + game->video.perm_textures.rects[RECT_PERM_DES_CHAR_X].w + 5;

	if(game->video.perm_textures.textures[TEXTURE_PERM_PLAYER_LIVE] != NULL) {
		free_textures(&game->video.perm_textures.textures[TEXTURE_PERM_PLAYER_LIVE], 1);
		game->video.perm_textures.textures[TEXTURE_PERM_PLAYER_LIVE] = get_text(game->video.renderer, game->video.hud.fonts[FONT_MENU], str_player_live, &white);
	}

	SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_MISC],
					&(game->video.perm_textures.rects[RECT_PERM_SRC_CHARACTER]), &game->video.perm_textures.rects[RECT_PERM_DES_PAUSE_CHARACTER]);

	SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_CHAR_X], NULL, &game->video.perm_textures.rects[RECT_PERM_DES_CHAR_X]);

	SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_PLAYER_LIVE], NULL, &game->video.perm_textures.rects[RECT_PERM_DES_PLAYER_LIVE]);
}

void render_game(Game *const game) {

	if(game->video.effects.fade.state != FADE_STATE_NO_FADE) {
		handle_fade(&(game->video.effects.fade), &(game->video.textures.map[TEXTURE_MAP_TILESET]), 1);
	}

	SDL_RenderClear(game->video.renderer);

	render_map(&game->video, &game->map, &game->screen);

	if(game->video.effects.fade.state == FADE_STATE_NO_FADE && game->video.effects.fade.alpha == 255) {		/*don't render texts when fade effect is on and changing level*/
		render_hud(game->video.renderer, &(game->video.textures), game->video.hud.rects);
	}

	if(game->settings.fps.show == TRUE) {
		render_fps(game);
	}
	
	SDL_RenderPresent(game->video.renderer);
}

/*fade time, fade state, fade full cycle should be already handled to work properly*/
void handle_fade(Fade *const fade, SDL_Texture **textures, const int count) {

	Uint64 timer_current;
	double rate;
	double alpha;

	timer_current = SDL_GetPerformanceCounter();
	fade->last_time = get_time_seconds(fade->timer_start, &timer_current);
	fade->time += fade->last_time;

	rate = calculate_rate(fade->time, fade->fade_time);

	switch(fade->state) {
		case FADE_STATE_FADING_IN:

			alpha = (int)(255 * rate);

			if(alpha > 255.0) {
				fade->alpha = 255;
			}
			else {
				fade->alpha = (Uint8)(alpha);
			}

			handle_fade_helper(fade->alpha, textures, count);
			break;
		case FADE_STATE_FADING_OUT:

			alpha = (int)(255 - (255 * rate));

			if(alpha < 0.0) {
				fade->alpha = 0;
			}
			else {
				fade->alpha = (Uint8)(alpha);
			}

			handle_fade_helper(fade->alpha, textures, count);
		default:
			break;
	}
}

void handle_fade_helper(const Uint8 alpha, SDL_Texture **textures, const int count) {

	int i;

	for(i = 0; i < count; ++i) {
		if(SDL_SetTextureAlphaMod(textures[i], alpha) < 0) {
			show_error();
		}
	}
}

void handle_fade_timer(Fade *const fade, const double delta_time) {

	if(fade->state == FADE_STATE_FADING_IN && fade->alpha >= 255) {
		if(fade->full_cycle == FALSE) {
			fade->state = FADE_STATE_NO_FADE;
			fade->time = 0.0;
			fade->last_time = 0.0;
			fade->fade_time = 0.0;
		}
		else {
			fade->full_cycle = FALSE;
			fade->state = FADE_STATE_FADING_OUT;
			fade->time = 0.0;
			fade->time -= fade->last_time;
			fade->time += delta_time;
			fade->last_time = 0.0;
		}
	}
	else if(fade->state == FADE_STATE_FADING_OUT && fade->alpha == 0) {
		if(fade->full_cycle == FALSE) {
			fade->state = FADE_STATE_NO_FADE;
			fade->time = 0.0;
			fade->last_time = 0.0;
			fade->fade_time = 0.0;
		}
		else {
			fade->full_cycle = FALSE;
			fade->state = FADE_STATE_FADING_IN;
			fade->time = 0.0;
			fade->time -= fade->last_time;
			fade->time += delta_time;
			fade->last_time = 0.0;
		}
	}
	else {
		fade->time -= fade->last_time;
		fade->time += delta_time;
		fade->last_time = 0.0;
	}
}

void set_effect_fade_out(Fade *const fade) {

	fade->state = FADE_STATE_FADING_OUT;
	fade->alpha = 255;
	fade->fade_time = DEFAULT_FADE_TIME;
	fade->full_cycle = FALSE;
}

void set_effect_fade_in(Fade *const fade) {

	fade->state = FADE_STATE_FADING_IN;
	fade->alpha = 0;
	fade->fade_time = DEFAULT_FADE_TIME;
	fade->full_cycle = FALSE;	
}

void render_map(Video *const video, Map *const map, Screen *const screen) {

	
	StackMovables *root[STACK_COUNT];

	init_stack_array(root, STACK_COUNT);

	render_background(video->renderer, video->textures.map[TEXTURE_MAP_TILESET], map->tile_map, &(map->info_tile_map), &(screen->info_window));

	/*rendering the static layer here*/
	render_statics(video->renderer, video->textures.map[TEXTURE_MAP_TILESET], map->tile_map, &(map->info_tile_map), &(screen->camera), root);

	/*rendering the movable layer*/
	render_movables(root[STACK_WATER], video->renderer, video->textures.map[TEXTURE_MAP_TILESET], map->tile_map);
	render_movables(root[STACK_STATIC_WATER], video->renderer, video->textures.map[TEXTURE_MAP_TILESET], map->tile_map);
	render_movables(root[STACK_STONES], video->renderer, video->textures.map[TEXTURE_MAP_TILESET], map->tile_map);
	render_movables(root[STACK_DIAMONDS], video->renderer, video->textures.map[TEXTURE_MAP_TILESET], map->tile_map);
	render_movables(root[STACK_SPIDERS], video->renderer, video->textures.map[TEXTURE_MAP_TILESET], map->tile_map);
	render_movables(root[STACK_MONSTERS], video->renderer, video->textures.map[TEXTURE_MAP_TILESET], map->tile_map);
	render_movables(root[STACK_CHARACTER], video->renderer, video->textures.map[TEXTURE_MAP_TILESET], map->tile_map);
}

void render_background(SDL_Renderer *renderer, SDL_Texture *texture, TileMap **const map, 
						const TileMapInfo *const info_map, const WindowInfo *const info_window) {

	SDL_Rect src_rect, des_rect;
	int x_pos, y_pos;

	find_src_rect(&src_rect, TILE_DIRT);

	des_rect.w = TILE_WIDTH;
	des_rect.h = TILE_HEIGHT;

	/*rendering the background layer of window, outside of the map*/
	for(y_pos = map[0][0].des_rect.y - TILE_HEIGHT; y_pos > (-TILE_HEIGHT); y_pos -= TILE_HEIGHT) {
		des_rect.y = y_pos;
		for(x_pos = map[0][0].des_rect.x - TILE_WIDTH; x_pos > (-TILE_WIDTH); x_pos -= TILE_WIDTH) {
			des_rect.x = x_pos;
			SDL_RenderCopy(renderer, texture, &src_rect, &des_rect);
		}
	}

	for(y_pos = map[0][0].des_rect.y - TILE_HEIGHT; y_pos > (-TILE_HEIGHT); y_pos -= TILE_HEIGHT) {
		des_rect.y = y_pos;
		for(x_pos = map[0][0].des_rect.x; x_pos < map[0][info_map->width - 1].des_rect.x + TILE_WIDTH; x_pos += TILE_WIDTH) {
			des_rect.x = x_pos;
			SDL_RenderCopy(renderer, texture, &src_rect, &des_rect);
		}
	}

	for(y_pos = map[0][0].des_rect.y - TILE_HEIGHT; y_pos > (-TILE_HEIGHT); y_pos -= TILE_HEIGHT) {
		des_rect.y = y_pos;
		for(x_pos = map[info_map->height - 1][info_map->width - 1].des_rect.x + TILE_WIDTH; x_pos < info_window->width + TILE_WIDTH; x_pos += TILE_WIDTH) {
			des_rect.x = x_pos;
			SDL_RenderCopy(renderer, texture, &src_rect, &des_rect);
		}
	}

	for(y_pos = map[0][0].des_rect.y; y_pos < map[info_map->height - 1][0].des_rect.y + TILE_HEIGHT; y_pos += TILE_HEIGHT) {
		des_rect.y = y_pos;
		for(x_pos = map[0][0].des_rect.x - TILE_WIDTH; x_pos > (-TILE_WIDTH); x_pos -= TILE_WIDTH) {
			des_rect.x = x_pos;
			SDL_RenderCopy(renderer, texture, &src_rect, &des_rect);
		}
	}

	for(y_pos = map[0][0].des_rect.y; y_pos < map[info_map->height - 1][0].des_rect.y + TILE_HEIGHT; y_pos += TILE_HEIGHT) {
		des_rect.y = y_pos;
		for(x_pos = map[0][info_map->width - 1].des_rect.x + TILE_WIDTH; x_pos < info_window->width + TILE_WIDTH; x_pos += TILE_WIDTH) {
			des_rect.x = x_pos;
			SDL_RenderCopy(renderer, texture, &src_rect, &des_rect);
		}
	}

	for(y_pos = map[info_map->height - 1][0].des_rect.y + TILE_HEIGHT; y_pos < info_window->height + TILE_HEIGHT; y_pos += TILE_HEIGHT) {
		des_rect.y = y_pos;
		for(x_pos = map[info_map->height - 1][0].des_rect.x - TILE_WIDTH; x_pos > (-TILE_WIDTH); x_pos -= TILE_WIDTH) {
			des_rect.x = x_pos;
			SDL_RenderCopy(renderer, texture, &src_rect, &des_rect);
		}
	}

	for(y_pos = map[info_map->height - 1][0].des_rect.y + TILE_HEIGHT; y_pos < info_window->height + TILE_HEIGHT; y_pos += TILE_HEIGHT) {
		des_rect.y = y_pos;
		for(x_pos = map[info_map->height - 1][0].des_rect.x; x_pos < map[info_map->height - 1][info_map->width - 1].des_rect.x + TILE_WIDTH; x_pos += TILE_WIDTH) {
			des_rect.x = x_pos;
			SDL_RenderCopy(renderer, texture, &src_rect, &des_rect);
		}
	}

	for(y_pos = map[info_map->height - 1][info_map->width - 1].des_rect.y + TILE_HEIGHT; y_pos < info_window->height + TILE_HEIGHT; y_pos += TILE_HEIGHT) {
		des_rect.y = y_pos;
		for(x_pos = map[info_map->height - 1][info_map->width - 1].des_rect.x + TILE_WIDTH; x_pos < info_window->width + TILE_WIDTH; x_pos += TILE_WIDTH) {
			des_rect.x = x_pos;
			SDL_RenderCopy(renderer, texture, &src_rect, &des_rect);
		}
	}
}

void render_statics(SDL_Renderer *renderer, SDL_Texture *texture, TileMap **const map, const TileMapInfo *const info_map,
						const Camera *const camera, StackMovables *root[STACK_COUNT]) {

	SDL_Rect src_rect;
	int x_pos, y_pos;
	SDL_Rect des_char_occupied;

	des_char_occupied.w = TILE_WIDTH;
	des_char_occupied.h = TILE_HEIGHT;

	find_src_rect(&src_rect, TILE_BACKGROUND);

	for(y_pos = 0; y_pos < info_map->height; ++y_pos) {
		for(x_pos = 0; x_pos < info_map->width; ++x_pos) {
			if(map[y_pos][x_pos].is_movable == TRUE) {

				/*render background for tiles with color key*/
				if(map[y_pos][x_pos].tile != TILE_BORDER &&
					map[y_pos][x_pos].tile != TILE_DIRT &&
					map[y_pos][x_pos].tile != TILE_BACKGROUND &&
					map[y_pos][x_pos].tile != TILE_WATER) {

					SDL_RenderCopy(renderer, texture, &(src_rect), &(map[y_pos][x_pos].des_rect));
				}
			
				/*water needs special treatments so i render water differently from others*/
				if(map[y_pos][x_pos].tile != TILE_WATER) {
					SDL_RenderCopy(renderer, texture, &(map[y_pos][x_pos].src_rect), &(map[y_pos][x_pos].des_rect));
				}
				else {

					

					/*different from the others, water is not moving but it flows so it kinda spreads,
						so where it spreads from is still water, to get smoother animation to give flowing impression,
							water tiles that are not moving is rendered top of moving ones*/
					push_movables(&root[STACK_STATIC_WATER], x_pos, y_pos);
				}
			}
			else {
				/*adding the movable layer to stack*/

				switch(map[y_pos][x_pos].tile) {
					case TILE_CHARACTER:
						smoothen_character_occupied(&(map[y_pos][x_pos]));
						offset_with_camera(&des_char_occupied, &(map[y_pos][x_pos].future_des_rect), camera);
						SDL_RenderCopy(renderer, texture, &(src_rect), &(des_char_occupied));
						push_movables(&root[STACK_CHARACTER], x_pos, y_pos);
						break;
					case TILE_STONE:
						push_movables(&root[STACK_STONES], x_pos, y_pos);
						break;
					case TILE_DIAMOND:
						push_movables(&root[STACK_DIAMONDS], x_pos, y_pos);
						break;
					case TILE_SPIDER:
						push_movables(&root[STACK_SPIDERS], x_pos, y_pos);
						break;
					case TILE_MONSTER:
						push_movables(&root[STACK_MONSTERS], x_pos, y_pos);
						break;
					case TILE_WATER:
						push_movables(&root[STACK_WATER], x_pos, y_pos);
						break;
					default:
						break;
				}

				offset_with_camera(&(map[y_pos][x_pos].occupied_des_rect), &(map[y_pos][x_pos].occupied_base_des_rect), camera);
				SDL_RenderCopy(renderer, texture, &(map[y_pos][x_pos].occupied_src_rect), &(map[y_pos][x_pos].occupied_des_rect));

			}
		}
	}
}

void render_movables(StackMovables *root, SDL_Renderer *renderer, SDL_Texture *texture, TileMap **const map) {
	
	while(root != NULL) {
		SDL_RenderCopy(renderer, texture, &(map[root->y_pos][root->x_pos].src_rect),
						&(map[root->y_pos][root->x_pos].des_rect));
		pop_movables(&root);
	}	
}

void render_hud(SDL_Renderer *renderer, Texture *textures, SDL_Rect *rects_hud) {

	SDL_Rect layer_src_rect;

	layer_src_rect.x = 0;
	layer_src_rect.y = 1048;
	layer_src_rect.w = 282;
	layer_src_rect.h = 104;

	SDL_RenderCopy(renderer, textures->map[TEXTURE_MAP_TILESET], &layer_src_rect, &rects_hud[RECT_LAYER_TIME]);
	SDL_RenderCopy(renderer, textures->hud[TEXTURE_TEXT_TIME], NULL, &rects_hud[RECT_TEXT_TIME]);

	layer_src_rect.x = 282;
	layer_src_rect.y = 1048;
	layer_src_rect.w = 358;
	layer_src_rect.h = 104;

	SDL_RenderCopy(renderer, textures->map[TEXTURE_MAP_TILESET], &layer_src_rect, &rects_hud[RECT_LAYER_SCORE]);
	SDL_RenderCopy(renderer, textures->hud[TEXTURE_TEXT_SCORE], NULL, &rects_hud[RECT_TEXT_SCORE]);

	layer_src_rect.x = 0;
	layer_src_rect.y = 953;
	layer_src_rect.w = 282;
	layer_src_rect.h = 95;

	SDL_RenderCopy(renderer, textures->map[TEXTURE_MAP_TILESET], &layer_src_rect, &rects_hud[RECT_LAYER_DIAMOND]);
	SDL_RenderCopy(renderer, textures->hud[TEXTURE_TEXT_DIAMOND], NULL, &rects_hud[RECT_TEXT_DIAMOND]);
}

void render_fps(Game *const game) {

	SDL_Color white = {
						.r = 255,
						.g = 255,
						.b = 255,
						.a = 255
	};

	int fps = (int)(1.0 / game->time.delta_time);
	char str_fps[6];
	int fps_digit_count;

	sprintf(str_fps, "%d", fps);

	free_textures(&game->video.perm_textures.textures[TEXTURE_PERM_FPS], 1);

	game->video.perm_textures.textures[TEXTURE_PERM_FPS] = get_text(game->video.renderer, game->video.hud.fonts[FONT_FPS], str_fps, &white);

	fps_digit_count = get_digit_count(fps);

	game->video.perm_textures.rects[RECT_PERM_DES_FPS].w = 32 * fps_digit_count;

	SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_FPS],
					NULL, &game->video.perm_textures.rects[RECT_PERM_DES_FPS]);	
}

void show_text_timed_screen(Game *const game, SDL_Texture *texture, SDL_Rect *rect, const double time) {

	double current_time = 0.0;

	while(current_time < time) {

		game->time.timer_start = SDL_GetPerformanceCounter();

		do_events_gui(game);

		SDL_RenderClear(game->video.renderer);

		SDL_RenderCopy(game->video.renderer, texture, NULL, rect);

		SDL_RenderPresent(game->video.renderer);

		current_time += game->time.delta_time;

		game->time.timer_stop = SDL_GetPerformanceCounter();
		game->time.delta_time = get_delta_time(&game->time.timer_start, &game->time.timer_stop);
	}
}

void free_textures(SDL_Texture **textures, const int size) {

	int i;

	for(i = 0; i < size; ++i) {
		if(textures[i] != NULL) {
			SDL_DestroyTexture(textures[i]);
			textures[i] = NULL;
		}
	}
}
