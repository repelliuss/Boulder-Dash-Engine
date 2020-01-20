#include <RPS/BD.h>

void init_hud(Hud *const hud, const WindowInfo *const info_window) {

	init_fonts(hud->fonts);
	get_rects_hud(hud->rects, info_window);
}

void init_fonts(TTF_Font **fonts) {

	int i;

	for(i = 0; i < FONT_COUNT; ++i) {
		fonts[i] = NULL;
	}

	fonts[FONT_MENU] = TTF_OpenFont("Resources/Fonts/menu.ttf", FONT_SIZE);
	if(fonts[FONT_MENU] == NULL) {
		show_ttf_error();
	}

	fonts[FONT_FPS] = TTF_OpenFont("Resources/Fonts/menu.ttf", FONT_SIZE_FPS);
	if(fonts[FONT_FPS] == NULL) {
		show_ttf_error();
	}
}

void get_rects_hud(SDL_Rect *rects, const WindowInfo *const info_window) {

	rects[RECT_LAYER_SCORE].w = 358;
	rects[RECT_LAYER_SCORE].h = 104;
	rects[RECT_LAYER_SCORE].x = (info_window->width - rects[RECT_LAYER_SCORE].w) / 2;

	rects[RECT_LAYER_SCORE].y = (info_window->height - rects[RECT_LAYER_SCORE].h) / 2 -
									((info_window->height - rects[RECT_LAYER_SCORE].h) / 2 - 25);


	rects[RECT_TEXT_SCORE].w = FONT_SIZE * SIZE_SCORE / 1.5;
	rects[RECT_TEXT_SCORE].h = FONT_SIZE / 1.5;	
	rects[RECT_TEXT_SCORE].x = rects[RECT_LAYER_SCORE].x + 89;
	rects[RECT_TEXT_SCORE].y = rects[RECT_LAYER_SCORE].y + 33;


	rects[RECT_LAYER_TIME].w = 282;
	rects[RECT_LAYER_TIME].h = 104;

	rects[RECT_LAYER_TIME].x = (info_window->width - rects[RECT_LAYER_TIME].w) / 2 - 
									((info_window->width - rects[RECT_LAYER_TIME].w) / 2 - 75);

	rects[RECT_LAYER_TIME].y = (info_window->height - rects[RECT_LAYER_TIME].h) / 2 -
									((info_window->height - rects[RECT_LAYER_TIME].h) / 2 - 25);


	rects[RECT_TEXT_TIME].w = FONT_SIZE * SIZE_TIME / 1.5;
	rects[RECT_TEXT_TIME].h = FONT_SIZE / 1.5;
	rects[RECT_TEXT_TIME].x = rects[RECT_LAYER_TIME].x + 95;
	rects[RECT_TEXT_TIME].y = rects[RECT_LAYER_TIME].y + 33; 


	rects[RECT_LAYER_DIAMOND].w = 282;
	rects[RECT_LAYER_DIAMOND].h = 95;

	rects[RECT_LAYER_DIAMOND].x = (info_window->width - rects[RECT_LAYER_DIAMOND].w) / 2 - 
									((info_window->width - rects[RECT_LAYER_DIAMOND].w) / 2 - 75);

	rects[RECT_LAYER_DIAMOND].y = (info_window->height - rects[RECT_LAYER_DIAMOND].h) / 2 -
									((info_window->height - rects[RECT_LAYER_DIAMOND].h) / 2 - 75) + 50;	

	rects[RECT_TEXT_DIAMOND].w = FONT_SIZE * SIZE_TIME / 1.5;
	rects[RECT_TEXT_DIAMOND].h = FONT_SIZE / 1.5;
	rects[RECT_TEXT_DIAMOND].x = rects[RECT_LAYER_DIAMOND].x + 95;
	rects[RECT_TEXT_DIAMOND].y = rects[RECT_LAYER_DIAMOND].y + 30;							
}

void get_rects_perm(SDL_Rect *rects, const WindowInfo *const info_window) {

	rects[RECT_PERM_PAUSE].x = (info_window->width - FONT_SIZE * 5) / 2;
	rects[RECT_PERM_PAUSE].y = 120;
	rects[RECT_PERM_PAUSE].w = FONT_SIZE * 5;
	rects[RECT_PERM_PAUSE].h = FONT_SIZE;

	rects[RECT_PERM_START].w = FONT_SIZE * 25 / 1.5;
	rects[RECT_PERM_START].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_START].x = (info_window->width - rects[RECT_PERM_START].w) / 2;
	rects[RECT_PERM_START].y = (info_window->height - rects[RECT_PERM_START].h) / 2 + 150;

	rects[RECT_PERM_QUIT].w = FONT_SIZE * 23 / 1.5;
	rects[RECT_PERM_QUIT].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_QUIT].x = rects[RECT_PERM_START].x + 48;
	rects[RECT_PERM_QUIT].y = rects[RECT_PERM_START].y + 100;

	rects[RECT_PERM_SRC_CHARACTER].w = TILE_WIDTH;
	rects[RECT_PERM_SRC_CHARACTER].h = TILE_HEIGHT;
	rects[RECT_PERM_SRC_CHARACTER].x = 236;
	rects[RECT_PERM_SRC_CHARACTER].y = 0;

	rects[RECT_PERM_SRC_GREEN_SQUARE].w = 16;
	rects[RECT_PERM_SRC_GREEN_SQUARE].h = 16;
	rects[RECT_PERM_SRC_GREEN_SQUARE].x = 200;
	rects[RECT_PERM_SRC_GREEN_SQUARE].y = 0;

	rects[RECT_PERM_SRC_GREEN_RECTANGLE].w = 198;
	rects[RECT_PERM_SRC_GREEN_RECTANGLE].h = 8;
	rects[RECT_PERM_SRC_GREEN_RECTANGLE].x = 12;
	rects[RECT_PERM_SRC_GREEN_RECTANGLE].y = 71;

	rects[RECT_PERM_SRC_RED_SQUARE].w = 16;
	rects[RECT_PERM_SRC_RED_SQUARE].h = 16;
	rects[RECT_PERM_SRC_RED_SQUARE].x = 200;
	rects[RECT_PERM_SRC_RED_SQUARE].y = 17;

	rects[RECT_PERM_SRC_RED_RECTANGLE].w = 198;
	rects[RECT_PERM_SRC_RED_RECTANGLE].h = 8;
	rects[RECT_PERM_SRC_RED_RECTANGLE].x = 12;
	rects[RECT_PERM_SRC_RED_RECTANGLE].y = 81;

	rects[RECT_PERM_DES_SQUARE].w = 16;
	rects[RECT_PERM_DES_SQUARE].h = 16;
	rects[RECT_PERM_DES_SQUARE].x = 100;
	rects[RECT_PERM_DES_SQUARE].y = (info_window->height - TILE_HEIGHT) / 2 + 50;	/*Up 50 pyxel from middle horizontal line*/

	rects[RECT_PERM_DES_RECTANGLE].h = 8;
	rects[RECT_PERM_DES_RECTANGLE].x = rects[RECT_PERM_DES_SQUARE].x + 16;
	rects[RECT_PERM_DES_RECTANGLE].y = (info_window->height - TILE_HEIGHT) / 2 + 50 + 4;	/*4 is rectangle height / 4 */

	rects[RECT_PERM_DES_CHARACTER].w = TILE_WIDTH;
	rects[RECT_PERM_DES_CHARACTER].h = TILE_HEIGHT;
	rects[RECT_PERM_DES_CHARACTER].y = (info_window->height - TILE_HEIGHT) / 2 - 50;

	rects[RECT_PERM_DES_WORLD].w = FONT_SIZE * 5 / 2;
	rects[RECT_PERM_DES_WORLD].h = FONT_SIZE / 2;
	rects[RECT_PERM_DES_WORLD].x = 100;
	rects[RECT_PERM_DES_WORLD].y = info_window->height - 100 - rects[RECT_PERM_DES_WORLD].h;

	rects[RECT_PERM_DES_WORLD_ID].h = rects[RECT_PERM_DES_WORLD].h;
	rects[RECT_PERM_DES_WORLD_ID].x = rects[RECT_PERM_DES_WORLD].x + rects[RECT_PERM_DES_WORLD].w + 5;
	rects[RECT_PERM_DES_WORLD_ID].y = rects[RECT_PERM_DES_WORLD].y;

	rects[RECT_PERM_DES_LEVEL].w = FONT_SIZE * 5 / 2;
	rects[RECT_PERM_DES_LEVEL].h = rects[RECT_PERM_DES_WORLD].h;
	rects[RECT_PERM_DES_LEVEL].y = rects[RECT_PERM_DES_WORLD].y;

	rects[RECT_PERM_DES_LEVEL_ID].h = rects[RECT_PERM_DES_WORLD].h;
	rects[RECT_PERM_DES_LEVEL_ID].y = rects[RECT_PERM_DES_WORLD].y;

	rects[RECT_PERM_DES_GO].w = FONT_SIZE * 19 / 1.5;
	rects[RECT_PERM_DES_GO].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_GO].x = (info_window->width - rects[RECT_PERM_DES_GO].w) / 2;
	rects[RECT_PERM_DES_GO].y = rects[RECT_PERM_DES_SQUARE].y + 150;

	rects[RECT_PERM_LEVEL_SELECT].w = FONT_SIZE * 12 / 1.5;
	rects[RECT_PERM_LEVEL_SELECT].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_LEVEL_SELECT].x = (info_window->width - rects[RECT_PERM_LEVEL_SELECT].w) / 2;
	rects[RECT_PERM_LEVEL_SELECT].y = 100;

	rects[RECT_PERM_DES_PAUSE_CHARACTER].w = TILE_WIDTH;
	rects[RECT_PERM_DES_PAUSE_CHARACTER].h = TILE_HEIGHT;
	rects[RECT_PERM_DES_PAUSE_CHARACTER].x = (info_window->width - TILE_WIDTH) / 2;
	rects[RECT_PERM_DES_PAUSE_CHARACTER].y = rects[RECT_PERM_PAUSE].y - rects[RECT_PERM_DES_PAUSE_CHARACTER].h - 36;

	rects[RECT_PERM_DES_CHAR_X].w = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_CHAR_X].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_CHAR_X].x = rects[RECT_PERM_DES_PAUSE_CHARACTER].x + rects[RECT_PERM_DES_PAUSE_CHARACTER].w + 5;
	rects[RECT_PERM_DES_CHAR_X].y = rects[RECT_PERM_PAUSE].y - rects[RECT_PERM_DES_CHAR_X].h - 36;

	rects[RECT_PERM_DES_PLAYER_LIVE].w = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_PLAYER_LIVE].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_PLAYER_LIVE].x = rects[RECT_PERM_DES_PAUSE_CHARACTER].x + rects[RECT_PERM_DES_PAUSE_CHARACTER].w + rects[RECT_PERM_DES_CHAR_X].w + 5;
	rects[RECT_PERM_DES_PLAYER_LIVE].y = rects[RECT_PERM_PAUSE].y - rects[RECT_PERM_DES_CHAR_X].h - 36;

	rects[RECT_PERM_DES_WIN].w = FONT_SIZE * 15 / 1.5;
	rects[RECT_PERM_DES_WIN].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_WIN].x = (info_window->width - rects[RECT_PERM_DES_WIN].w) / 2;
	rects[RECT_PERM_DES_WIN].y = (info_window->height - rects[RECT_PERM_DES_WIN].h) / 2;

	rects[RECT_PERM_DES_LOSE].w = FONT_SIZE * 16 / 1.5;
	rects[RECT_PERM_DES_LOSE].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_LOSE].x = (info_window->width - rects[RECT_PERM_DES_LOSE].w) / 2;
	rects[RECT_PERM_DES_LOSE].y = (info_window->height - rects[RECT_PERM_DES_LOSE].h) / 2;

	rects[RECT_PERM_DES_SETTINGS].w = FONT_SIZE * 8 / 1.5;
	rects[RECT_PERM_DES_SETTINGS].h = FONT_SIZE / 1.5;

	rects[RECT_PERM_DES_RESTART].w = FONT_SIZE * 17 / 1.5;
	rects[RECT_PERM_DES_RESTART].h = FONT_SIZE / 1.5;

	rects[RECT_PERM_DES_LEVEL_SCREEN].w = FONT_SIZE * 22 / 1.5;
	rects[RECT_PERM_DES_LEVEL_SCREEN].h = FONT_SIZE / 1.5;

	rects[RECT_PERM_DES_SAVE_GAME].w = FONT_SIZE * 9 / 1.5;
	rects[RECT_PERM_DES_SAVE_GAME].h = FONT_SIZE / 1.5;

	rects[RECT_PERM_DES_LOAD_SAVE].w = FONT_SIZE * 9 / 1.5;
	rects[RECT_PERM_DES_LOAD_SAVE].h = FONT_SIZE / 1.5;

	rects[RECT_PERM_DES_QUIT_GAME].w = FONT_SIZE * 9 / 1.5;
	rects[RECT_PERM_DES_QUIT_GAME].h = FONT_SIZE / 1.5;

	rects[RECT_PERM_DES_SETTINGS].x = (info_window->width - rects[RECT_PERM_DES_SETTINGS].w) / 2;
	rects[RECT_PERM_DES_SETTINGS].y = rects[RECT_PERM_PAUSE].y + 175;

	rects[RECT_PERM_DES_RESTART].x = (info_window->width - rects[RECT_PERM_DES_RESTART].w) / 2;
	rects[RECT_PERM_DES_RESTART].y = rects[RECT_PERM_DES_SETTINGS].y + rects[RECT_PERM_DES_SETTINGS].h + 50;

	rects[RECT_PERM_DES_LEVEL_SCREEN].x = (info_window->width - rects[RECT_PERM_DES_LEVEL_SCREEN].w) / 2;
	rects[RECT_PERM_DES_LEVEL_SCREEN].y = rects[RECT_PERM_DES_RESTART].y + rects[RECT_PERM_DES_RESTART].h + 50;
	
	rects[RECT_PERM_DES_SAVE_GAME].x = (info_window->width - rects[RECT_PERM_DES_SAVE_GAME].w) / 2;
	rects[RECT_PERM_DES_SAVE_GAME].y = rects[RECT_PERM_DES_LEVEL_SCREEN].y + rects[RECT_PERM_DES_LEVEL_SCREEN].h + 50;
	
	rects[RECT_PERM_DES_LOAD_SAVE].x = (info_window->width - rects[RECT_PERM_DES_LOAD_SAVE].w) / 2;
	rects[RECT_PERM_DES_LOAD_SAVE].y = rects[RECT_PERM_DES_SAVE_GAME].y + rects[RECT_PERM_DES_SAVE_GAME].h + 50;

	rects[RECT_PERM_DES_QUIT_GAME].x = (info_window->width - rects[RECT_PERM_DES_QUIT_GAME].w) / 2;
	rects[RECT_PERM_DES_QUIT_GAME].y = rects[RECT_PERM_DES_LOAD_SAVE].y + rects[RECT_PERM_DES_LOAD_SAVE].h + 50;

	rects[RECT_PERM_SRC_SELECT_LAYER].w = 179;
	rects[RECT_PERM_SRC_SELECT_LAYER].h = 68;
	rects[RECT_PERM_SRC_SELECT_LAYER].x = 12;
	rects[RECT_PERM_SRC_SELECT_LAYER].y = 0;

	rects[RECT_PERM_DES_FPS_LOCK].w = FONT_SIZE * 8 / 1.5;
	rects[RECT_PERM_DES_FPS_LOCK].h = FONT_SIZE / 1.5;

	rects[RECT_PERM_DES_SHOW_FPS].w = FONT_SIZE * 8 / 1.5;
	rects[RECT_PERM_DES_SHOW_FPS].h = FONT_SIZE / 1.5;

	rects[RECT_PERM_DES_WINDOW_MODE].w = FONT_SIZE * 11 / 1.5;
	rects[RECT_PERM_DES_WINDOW_MODE].h = FONT_SIZE / 1.5;

	rects[RECT_PERM_DES_VOLUME].w = FONT_SIZE * 6 / 1.5;
	rects[RECT_PERM_DES_VOLUME].h = FONT_SIZE / 1.5;

	rects[RECT_PERM_DES_DEV_MODE].w = FONT_SIZE * 8 / 1.5;
	rects[RECT_PERM_DES_DEV_MODE].h = FONT_SIZE / 1.5;

	rects[RECT_PERM_DES_CAMERA_SPEED].w = FONT_SIZE * 12 / 1.5;
	rects[RECT_PERM_DES_CAMERA_SPEED].h = FONT_SIZE / 1.5;

	rects[RECT_PERM_DES_FPS_LOCK].x = 200;
	rects[RECT_PERM_DES_FPS_LOCK].y = (info_window->height - (FONT_SIZE / 1.5 *6) - (50 * 5)) / 2;

	rects[RECT_PERM_DES_SHOW_FPS].x = rects[RECT_PERM_DES_FPS_LOCK].x;
	rects[RECT_PERM_DES_SHOW_FPS].y = rects[RECT_PERM_DES_FPS_LOCK].y + rects[RECT_PERM_DES_FPS_LOCK].h + 50;

	rects[RECT_PERM_DES_WINDOW_MODE].x = rects[RECT_PERM_DES_SHOW_FPS].x;
	rects[RECT_PERM_DES_WINDOW_MODE].y = rects[RECT_PERM_DES_SHOW_FPS].y + rects[RECT_PERM_DES_SHOW_FPS].h + 50;

	rects[RECT_PERM_DES_VOLUME].x = rects[RECT_PERM_DES_WINDOW_MODE].x;
	rects[RECT_PERM_DES_VOLUME].y = rects[RECT_PERM_DES_WINDOW_MODE].y + rects[RECT_PERM_DES_WINDOW_MODE].h + 50;

	rects[RECT_PERM_DES_DEV_MODE].x = rects[RECT_PERM_DES_VOLUME].x;
	rects[RECT_PERM_DES_DEV_MODE].y = rects[RECT_PERM_DES_VOLUME].y + rects[RECT_PERM_DES_VOLUME].h + 50;

	rects[RECT_PERM_DES_CAMERA_SPEED].x = rects[RECT_PERM_DES_DEV_MODE].x;
	rects[RECT_PERM_DES_CAMERA_SPEED].y = rects[RECT_PERM_DES_DEV_MODE].y + rects[RECT_PERM_DES_DEV_MODE].h + 50;

	rects[RECT_PERM_DES_FPS_LOCK_VAL].w = FONT_SIZE * 3 / 1.5;
	rects[RECT_PERM_DES_FPS_LOCK_VAL].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_FPS_LOCK_VAL].x = rects[RECT_PERM_DES_FPS_LOCK].x + rects[RECT_PERM_DES_FPS_LOCK].w + 500;
	rects[RECT_PERM_DES_FPS_LOCK_VAL].y = rects[RECT_PERM_DES_FPS_LOCK].y;

	rects[RECT_PERM_DES_SHOW_FPS_VAL].w = FONT_SIZE * 3 / 1.5;
	rects[RECT_PERM_DES_SHOW_FPS_VAL].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_SHOW_FPS_VAL].x = rects[RECT_PERM_DES_FPS_LOCK_VAL].x;
	rects[RECT_PERM_DES_SHOW_FPS_VAL].y = rects[RECT_PERM_DES_FPS_LOCK_VAL].y + rects[RECT_PERM_DES_FPS_LOCK_VAL].h + 50;

	rects[RECT_PERM_DES_WINDOW_MODE_VAL].w = FONT_SIZE * 10 / 1.5;
	rects[RECT_PERM_DES_WINDOW_MODE_VAL].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_WINDOW_MODE_VAL].x = rects[RECT_PERM_DES_SHOW_FPS_VAL].x;
	rects[RECT_PERM_DES_WINDOW_MODE_VAL].y = rects[RECT_PERM_DES_SHOW_FPS_VAL].y + rects[RECT_PERM_DES_SHOW_FPS_VAL].h + 50;

	rects[RECT_PERM_DES_VOLUME_VAL].w = FONT_SIZE * 3 / 1.5;
	rects[RECT_PERM_DES_VOLUME_VAL].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_VOLUME_VAL].x = rects[RECT_PERM_DES_WINDOW_MODE_VAL].x;
	rects[RECT_PERM_DES_VOLUME_VAL].y = rects[RECT_PERM_DES_WINDOW_MODE_VAL].y + rects[RECT_PERM_DES_WINDOW_MODE_VAL].h + 50;

	rects[RECT_PERM_DES_DEV_MODE_VAL].w = FONT_SIZE * 3 / 1.5;
	rects[RECT_PERM_DES_DEV_MODE_VAL].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_DEV_MODE_VAL].x = rects[RECT_PERM_DES_VOLUME_VAL].x;
	rects[RECT_PERM_DES_DEV_MODE_VAL].y = rects[RECT_PERM_DES_VOLUME_VAL].y + rects[RECT_PERM_DES_VOLUME_VAL].h + 50;

	rects[RECT_PERM_DES_CAMERA_SPEED_VAL].w = FONT_SIZE * 3 / 1.5;
	rects[RECT_PERM_DES_CAMERA_SPEED_VAL].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_CAMERA_SPEED_VAL].x = rects[RECT_PERM_DES_DEV_MODE_VAL].x;
	rects[RECT_PERM_DES_CAMERA_SPEED_VAL].y = rects[RECT_PERM_DES_DEV_MODE_VAL].y + rects[RECT_PERM_DES_DEV_MODE_VAL].h + 50;

	rects[RECT_PERM_SRC_ARROW_LEFT].w = 17;
	rects[RECT_PERM_SRC_ARROW_LEFT].h = 14;
	rects[RECT_PERM_SRC_ARROW_LEFT].x = 216;
	rects[RECT_PERM_SRC_ARROW_LEFT].y = 71;

	rects[RECT_PERM_SRC_ARROW_RIGHT].w = 17;
	rects[RECT_PERM_SRC_ARROW_RIGHT].h = 14;
	rects[RECT_PERM_SRC_ARROW_RIGHT].x = 236;
	rects[RECT_PERM_SRC_ARROW_RIGHT].y = 71;

	rects[RECT_PERM_DES_FPS].w = -1;
	rects[RECT_PERM_DES_FPS].h = 32;
	rects[RECT_PERM_DES_FPS].x = 4;
	rects[RECT_PERM_DES_FPS].y = 4;

	rects[RECT_PERM_DES_MUTE].w = FONT_SIZE * 4 / 1.5;
	rects[RECT_PERM_DES_MUTE].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_MUTE].x = 200;
	rects[RECT_PERM_DES_MUTE].y = (info_window->height / 2.5);

	rects[RECT_PERM_DES_MUSIC_VOLUME].w = FONT_SIZE * 12 / 1.5;
	rects[RECT_PERM_DES_MUSIC_VOLUME].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_MUSIC_VOLUME].x = rects[RECT_PERM_DES_MUTE].x;
	rects[RECT_PERM_DES_MUSIC_VOLUME].y = rects[RECT_PERM_DES_MUTE].y + rects[RECT_PERM_DES_MUTE].h + 50;

	rects[RECT_PERM_DES_SFX_VOLUME].w = FONT_SIZE * 10 / 1.5;
	rects[RECT_PERM_DES_SFX_VOLUME].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_SFX_VOLUME].x = rects[RECT_PERM_DES_MUSIC_VOLUME].x;
	rects[RECT_PERM_DES_SFX_VOLUME].y = rects[RECT_PERM_DES_MUSIC_VOLUME].y + rects[RECT_PERM_DES_MUSIC_VOLUME].h + 50;

	rects[RECT_PERM_DES_MUTE_VAL].w = FONT_SIZE * 3 / 1.5;
	rects[RECT_PERM_DES_MUTE_VAL].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_MUTE_VAL].x = rects[RECT_PERM_DES_MUTE].x + rects[RECT_PERM_DES_MUTE].w + 700;
	rects[RECT_PERM_DES_MUTE_VAL].y = rects[RECT_PERM_DES_MUTE].y;


	rects[RECT_PERM_DES_MUSIC_VOLUME_VAL].w = FONT_SIZE * 3 / 1.5;
	rects[RECT_PERM_DES_MUSIC_VOLUME_VAL].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_MUSIC_VOLUME_VAL].x = rects[RECT_PERM_DES_MUTE_VAL].x;
	rects[RECT_PERM_DES_MUSIC_VOLUME_VAL].y = rects[RECT_PERM_DES_MUTE_VAL].y + rects[RECT_PERM_DES_MUTE_VAL].h + 50;

	rects[RECT_PERM_DES_SFX_VOLUME_VAL].w = FONT_SIZE * 3 / 1.5;
	rects[RECT_PERM_DES_SFX_VOLUME_VAL].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_SFX_VOLUME_VAL].x = rects[RECT_PERM_DES_MUSIC_VOLUME_VAL].x;
	rects[RECT_PERM_DES_SFX_VOLUME_VAL].y = rects[RECT_PERM_DES_MUSIC_VOLUME_VAL].y + rects[RECT_PERM_DES_MUSIC_VOLUME_VAL].h + 50;

	rects[RECT_PERM_DES_NO].w = FONT_SIZE * 2 / 1.5;
	rects[RECT_PERM_DES_NO].h = FONT_SIZE / 1.5;

	rects[RECT_PERM_DES_YES].w = FONT_SIZE * 3 / 1.5;
	rects[RECT_PERM_DES_YES].h = FONT_SIZE / 1.5;

	rects[RECT_PERM_DES_NO].x = (info_window->width - rects[RECT_PERM_DES_NO].w - rects[RECT_PERM_DES_YES].w - 250) / 2;
	rects[RECT_PERM_DES_NO].y = (info_window->height - rects[RECT_PERM_DES_NO].h) / 2 + 150;

	rects[RECT_PERM_DES_YES].x = rects[RECT_PERM_DES_NO].x + rects[RECT_PERM_DES_NO].w + 250;
	rects[RECT_PERM_DES_YES].y = rects[RECT_PERM_DES_NO].y;

	rects[RECT_PERM_DES_ASU].w = FONT_SIZE * 13 / 1.5;
	rects[RECT_PERM_DES_ASU].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_ASU].x = (info_window->width - rects[RECT_PERM_DES_ASU].w) / 2;
	rects[RECT_PERM_DES_ASU].y = (info_window->height - rects[RECT_PERM_DES_ASU].h) / 2;

	rects[RECT_PERM_DES_OVERWRITE].w = FONT_SIZE  * 26 / 1.5;
	rects[RECT_PERM_DES_OVERWRITE].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_OVERWRITE].x = (info_window->width - rects[RECT_PERM_DES_OVERWRITE].w) / 2;
	rects[RECT_PERM_DES_OVERWRITE].y = (info_window->height - rects[RECT_PERM_DES_OVERWRITE].h) / 2 - 50 - (FONT_SIZE / 1.5);

	rects[RECT_PERM_DES_PROGRESS].w = FONT_SIZE  * 31 / 1.5;
	rects[RECT_PERM_DES_PROGRESS].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_PROGRESS].x = (info_window->width - rects[RECT_PERM_DES_PROGRESS].w) / 2;
	rects[RECT_PERM_DES_PROGRESS].y = (info_window->height - rects[RECT_PERM_DES_PROGRESS].h) / 2 - 50 - (FONT_SIZE / 1.5);

	rects[RECT_PERM_DES_FAIL_SAVE].w = FONT_SIZE * 15 / 1.5;
	rects[RECT_PERM_DES_FAIL_SAVE].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_FAIL_SAVE].x = (info_window->width - rects[RECT_PERM_DES_FAIL_SAVE].w) / 2;
	rects[RECT_PERM_DES_FAIL_SAVE].y = (info_window->height - rects[RECT_PERM_DES_FAIL_SAVE].h) / 2;

	rects[RECT_PERM_DES_FAIL_LOAD].w = FONT_SIZE * 15 / 1.5;
	rects[RECT_PERM_DES_FAIL_LOAD].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_FAIL_LOAD].x = (info_window->width - rects[RECT_PERM_DES_FAIL_LOAD].w) / 2;
	rects[RECT_PERM_DES_FAIL_LOAD].y = (info_window->height - rects[RECT_PERM_DES_FAIL_LOAD].h) / 2;

	rects[RECT_PERM_DES_GAME_RESTART].w = FONT_SIZE * 31 / 1.5;
	rects[RECT_PERM_DES_GAME_RESTART].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_GAME_RESTART].x = (info_window->width - rects[RECT_PERM_DES_GAME_RESTART].w) / 2;
	rects[RECT_PERM_DES_GAME_RESTART].y = (info_window->height - rects[RECT_PERM_DES_GAME_RESTART].h) / 2;

	rects[RECT_PERM_DES_NEW_GAME].w = FONT_SIZE * 8 / 1.5;
	rects[RECT_PERM_DES_NEW_GAME].h = FONT_SIZE / 1.5;

	rects[RECT_PERM_DES_NEW_LOAD_SAVE].w = FONT_SIZE * 9 / 1.5;
	rects[RECT_PERM_DES_NEW_LOAD_SAVE].h = FONT_SIZE / 1.5;

	rects[RECT_PERM_DES_NEW_GAME].x = (info_window->width - rects[RECT_PERM_DES_NEW_GAME].w) / 2;
	rects[RECT_PERM_DES_NEW_GAME].y = (info_window->height - rects[RECT_PERM_DES_NEW_GAME].h - rects[RECT_PERM_DES_NEW_LOAD_SAVE].h - 50) / 2;

	rects[RECT_PERM_DES_NEW_LOAD_SAVE].x = (info_window->width - rects[RECT_PERM_DES_NEW_LOAD_SAVE].w) / 2;
	rects[RECT_PERM_DES_NEW_LOAD_SAVE].y = rects[RECT_PERM_DES_NEW_GAME].y + rects[RECT_PERM_DES_NEW_GAME].h + 50;

	rects[RECT_PERM_DES_EASY].w = FONT_SIZE * 4 / 1.5;
	rects[RECT_PERM_DES_EASY].h = FONT_SIZE / 1.5;

	rects[RECT_PERM_DES_NORMAL].w = FONT_SIZE * 6 / 1.5;
	rects[RECT_PERM_DES_NORMAL].h = FONT_SIZE / 1.5;

	rects[RECT_PERM_DES_HARD].w = FONT_SIZE * 4 / 1.5;
	rects[RECT_PERM_DES_HARD].h = FONT_SIZE / 1.5;

	rects[RECT_PERM_DES_IMPOSSIBLE].w = FONT_SIZE * 20 / 1.5;
	rects[RECT_PERM_DES_IMPOSSIBLE].h = FONT_SIZE / 1.5;

	rects[RECT_PERM_DES_EASY].x = (info_window->width - rects[RECT_PERM_DES_EASY].w) / 2;
	rects[RECT_PERM_DES_EASY].y = (info_window->height - rects[RECT_PERM_DES_EASY].h - rects[RECT_PERM_DES_NORMAL].h - rects[RECT_PERM_DES_HARD].h - rects[RECT_PERM_DES_IMPOSSIBLE].h - 50 * 3) / 2;

	rects[RECT_PERM_DES_NORMAL].x = (info_window->width - rects[RECT_PERM_DES_NORMAL].w) / 2;
	rects[RECT_PERM_DES_NORMAL].y = rects[RECT_PERM_DES_EASY].y + rects[RECT_PERM_DES_EASY].h + 50;

	rects[RECT_PERM_DES_HARD].x = (info_window->width - rects[RECT_PERM_DES_HARD].w) / 2;
	rects[RECT_PERM_DES_HARD].y = rects[RECT_PERM_DES_NORMAL].y + rects[RECT_PERM_DES_NORMAL].h + 50;

	rects[RECT_PERM_DES_IMPOSSIBLE].x = (info_window->width - rects[RECT_PERM_DES_IMPOSSIBLE].w) / 2;
	rects[RECT_PERM_DES_IMPOSSIBLE].y = rects[RECT_PERM_DES_HARD].y + rects[RECT_PERM_DES_HARD].h + 50;

	rects[RECT_PERM_DES_CANT_SAVE].w = FONT_SIZE  * 33 / 1.5;
	rects[RECT_PERM_DES_CANT_SAVE].h = FONT_SIZE / 1.5;
	rects[RECT_PERM_DES_CANT_SAVE].x = (info_window->width - rects[RECT_PERM_DES_CANT_SAVE].w) / 2;
	rects[RECT_PERM_DES_CANT_SAVE].y = (info_window->height - rects[RECT_PERM_DES_CANT_SAVE].h) / 2;
}

void update_hud_rects(SDL_Rect *hud_rects, const WindowInfo *const info_window) {

	hud_rects[RECT_LAYER_SCORE].x = (info_window->width - hud_rects[RECT_LAYER_SCORE].w) / 2;

	hud_rects[RECT_LAYER_SCORE].y = (info_window->height - hud_rects[RECT_LAYER_SCORE].h) / 2 -
									((info_window->height - hud_rects[RECT_LAYER_SCORE].h) / 2 - 25);

	hud_rects[RECT_TEXT_SCORE].x = hud_rects[RECT_LAYER_SCORE].x + 89;
	hud_rects[RECT_TEXT_SCORE].y = hud_rects[RECT_LAYER_SCORE].y + 33;

	hud_rects[RECT_LAYER_TIME].x = (info_window->width - hud_rects[RECT_LAYER_TIME].w) / 2 - 
									((info_window->width - hud_rects[RECT_LAYER_TIME].w) / 2 - 75);

	hud_rects[RECT_LAYER_TIME].y = (info_window->height - hud_rects[RECT_LAYER_TIME].h) / 2 -
									((info_window->height - hud_rects[RECT_LAYER_TIME].h) / 2 - 25);


	hud_rects[RECT_TEXT_TIME].x = hud_rects[RECT_LAYER_TIME].x + 95;
	hud_rects[RECT_TEXT_TIME].y = hud_rects[RECT_LAYER_TIME].y + 33;

	hud_rects[RECT_LAYER_DIAMOND].x = (info_window->width - hud_rects[RECT_LAYER_DIAMOND].w) / 2 - 
									((info_window->width - hud_rects[RECT_LAYER_DIAMOND].w) / 2 - 75);

	hud_rects[RECT_LAYER_DIAMOND].y = (info_window->height - hud_rects[RECT_LAYER_DIAMOND].h) / 2 -
									((info_window->height - hud_rects[RECT_LAYER_DIAMOND].h) / 2 - 75) + 50;

	hud_rects[RECT_TEXT_DIAMOND].x = hud_rects[RECT_LAYER_DIAMOND].x + 95;
	hud_rects[RECT_TEXT_DIAMOND].y = hud_rects[RECT_LAYER_DIAMOND].y + 30;
}

void update_perm_rects(SDL_Rect *perm_rects, const WindowInfo *const info_window) {

	/*START SCREEN RECTS*/

	perm_rects[RECT_PERM_START].x = (info_window->width - perm_rects[RECT_PERM_START].w) / 2;
	perm_rects[RECT_PERM_START].y = (info_window->height - perm_rects[RECT_PERM_START].h) / 2 + 150;

	perm_rects[RECT_PERM_QUIT].x = perm_rects[RECT_PERM_START].x + 48;
	perm_rects[RECT_PERM_QUIT].y = perm_rects[RECT_PERM_START].y + 100;


	/*LEVEL SCREEN RECTS*/

	perm_rects[RECT_PERM_DES_SQUARE].y = (info_window->height - TILE_HEIGHT) / 2 + 50;
	
	perm_rects[RECT_PERM_DES_RECTANGLE].y = (info_window->height - TILE_HEIGHT) / 2 + 50 + 4;	/*4 is rectangle height / 4 */

	perm_rects[RECT_PERM_DES_CHARACTER].y = (info_window->height - TILE_HEIGHT) / 2 - 50;

	perm_rects[RECT_PERM_DES_WORLD].y = info_window->height - 100 - perm_rects[RECT_PERM_DES_WORLD].h;

	perm_rects[RECT_PERM_DES_WORLD_ID].y = perm_rects[RECT_PERM_DES_WORLD].y;
	
	perm_rects[RECT_PERM_DES_LEVEL].y = perm_rects[RECT_PERM_DES_WORLD].y;
	
	perm_rects[RECT_PERM_DES_LEVEL_ID].y = perm_rects[RECT_PERM_DES_WORLD].y;

	perm_rects[RECT_PERM_DES_GO].y = perm_rects[RECT_PERM_DES_SQUARE].y + 150;
	perm_rects[RECT_PERM_DES_GO].x = (info_window->width - perm_rects[RECT_PERM_DES_GO].w) / 2;

	perm_rects[RECT_PERM_LEVEL_SELECT].x = (info_window->width - perm_rects[RECT_PERM_LEVEL_SELECT].w) / 2;


	/*PAUSE SCREEN RECTS*/

	perm_rects[RECT_PERM_PAUSE].x = (info_window->width - FONT_SIZE * 5) / 2;

	perm_rects[RECT_PERM_DES_PAUSE_CHARACTER].x = (info_window->width - TILE_WIDTH) / 2;
	perm_rects[RECT_PERM_DES_PAUSE_CHARACTER].y = perm_rects[RECT_PERM_PAUSE].y - perm_rects[RECT_PERM_DES_PAUSE_CHARACTER].h - 36;

	perm_rects[RECT_PERM_DES_CHAR_X].x = perm_rects[RECT_PERM_DES_PAUSE_CHARACTER].x + perm_rects[RECT_PERM_DES_PAUSE_CHARACTER].w + 5;
	perm_rects[RECT_PERM_DES_CHAR_X].y = perm_rects[RECT_PERM_PAUSE].y - perm_rects[RECT_PERM_DES_CHAR_X].h - 36;

	perm_rects[RECT_PERM_DES_PLAYER_LIVE].x = perm_rects[RECT_PERM_DES_PAUSE_CHARACTER].x + perm_rects[RECT_PERM_DES_PAUSE_CHARACTER].w + perm_rects[RECT_PERM_DES_CHAR_X].w + 5;
	perm_rects[RECT_PERM_DES_PLAYER_LIVE].y = perm_rects[RECT_PERM_PAUSE].y - perm_rects[RECT_PERM_DES_CHAR_X].h - 36;

	perm_rects[RECT_PERM_DES_SETTINGS].x = (info_window->width - perm_rects[RECT_PERM_DES_SETTINGS].w) / 2;
	perm_rects[RECT_PERM_DES_SETTINGS].y = perm_rects[RECT_PERM_PAUSE].y + 175;

	perm_rects[RECT_PERM_DES_RESTART].x = (info_window->width - perm_rects[RECT_PERM_DES_RESTART].w) / 2;
	perm_rects[RECT_PERM_DES_RESTART].y = perm_rects[RECT_PERM_DES_SETTINGS].y + perm_rects[RECT_PERM_DES_SETTINGS].h + 50;

	perm_rects[RECT_PERM_DES_LEVEL_SCREEN].x = (info_window->width - perm_rects[RECT_PERM_DES_LEVEL_SCREEN].w) / 2;
	perm_rects[RECT_PERM_DES_LEVEL_SCREEN].y = perm_rects[RECT_PERM_DES_RESTART].y + perm_rects[RECT_PERM_DES_RESTART].h + 50;

	perm_rects[RECT_PERM_DES_SAVE_GAME].x = (info_window->width - perm_rects[RECT_PERM_DES_SAVE_GAME].w) / 2;
	perm_rects[RECT_PERM_DES_SAVE_GAME].y = perm_rects[RECT_PERM_DES_LEVEL_SCREEN].y + perm_rects[RECT_PERM_DES_LEVEL_SCREEN].h + 50;

	perm_rects[RECT_PERM_DES_LOAD_SAVE].x = (info_window->width - perm_rects[RECT_PERM_DES_LOAD_SAVE].w) / 2;
	perm_rects[RECT_PERM_DES_LOAD_SAVE].y = perm_rects[RECT_PERM_DES_SAVE_GAME].y + perm_rects[RECT_PERM_DES_SAVE_GAME].h + 50;

	perm_rects[RECT_PERM_DES_QUIT_GAME].x = (info_window->width - perm_rects[RECT_PERM_DES_QUIT_GAME].w) / 2;
	perm_rects[RECT_PERM_DES_QUIT_GAME].y = perm_rects[RECT_PERM_DES_LOAD_SAVE].y + perm_rects[RECT_PERM_DES_LOAD_SAVE].h + 50;

	perm_rects[RECT_PERM_DES_WIN].x = (info_window->width - perm_rects[RECT_PERM_DES_WIN].w) / 2;
	perm_rects[RECT_PERM_DES_WIN].y = (info_window->height - perm_rects[RECT_PERM_DES_WIN].h) / 2;

	perm_rects[RECT_PERM_DES_LOSE].x = (info_window->width - perm_rects[RECT_PERM_DES_LOSE].w) / 2;
	perm_rects[RECT_PERM_DES_LOSE].y = (info_window->height - perm_rects[RECT_PERM_DES_LOSE].h) / 2;


	/*SETTINGS RECTS*/


	perm_rects[RECT_PERM_DES_FPS_LOCK].y = (info_window->height - (FONT_SIZE / 1.5 * 6) - (50 * 5)) / 2;

	perm_rects[RECT_PERM_DES_SHOW_FPS].x = perm_rects[RECT_PERM_DES_FPS_LOCK].x;
	perm_rects[RECT_PERM_DES_SHOW_FPS].y = perm_rects[RECT_PERM_DES_FPS_LOCK].y + perm_rects[RECT_PERM_DES_FPS_LOCK].h + 50;

	perm_rects[RECT_PERM_DES_WINDOW_MODE].x = perm_rects[RECT_PERM_DES_SHOW_FPS].x;
	perm_rects[RECT_PERM_DES_WINDOW_MODE].y = perm_rects[RECT_PERM_DES_SHOW_FPS].y + perm_rects[RECT_PERM_DES_SHOW_FPS].h + 50;

	perm_rects[RECT_PERM_DES_VOLUME].x = perm_rects[RECT_PERM_DES_WINDOW_MODE].x;
	perm_rects[RECT_PERM_DES_VOLUME].y = perm_rects[RECT_PERM_DES_WINDOW_MODE].y + perm_rects[RECT_PERM_DES_WINDOW_MODE].h + 50;

	perm_rects[RECT_PERM_DES_DEV_MODE].x = perm_rects[RECT_PERM_DES_VOLUME].x;
	perm_rects[RECT_PERM_DES_DEV_MODE].y = perm_rects[RECT_PERM_DES_VOLUME].y + perm_rects[RECT_PERM_DES_VOLUME].h + 50;

	perm_rects[RECT_PERM_DES_CAMERA_SPEED].x = perm_rects[RECT_PERM_DES_DEV_MODE].x;
	perm_rects[RECT_PERM_DES_CAMERA_SPEED].y = perm_rects[RECT_PERM_DES_DEV_MODE].y + perm_rects[RECT_PERM_DES_DEV_MODE].h + 50;

	perm_rects[RECT_PERM_DES_FPS_LOCK_VAL].x = perm_rects[RECT_PERM_DES_FPS_LOCK].x + perm_rects[RECT_PERM_DES_FPS_LOCK].w + 500;
	perm_rects[RECT_PERM_DES_FPS_LOCK_VAL].y = perm_rects[RECT_PERM_DES_FPS_LOCK].y;

	perm_rects[RECT_PERM_DES_SHOW_FPS_VAL].x = perm_rects[RECT_PERM_DES_FPS_LOCK_VAL].x;
	perm_rects[RECT_PERM_DES_SHOW_FPS_VAL].y = perm_rects[RECT_PERM_DES_FPS_LOCK_VAL].y + perm_rects[RECT_PERM_DES_FPS_LOCK_VAL].h + 50;

	perm_rects[RECT_PERM_DES_WINDOW_MODE_VAL].x = perm_rects[RECT_PERM_DES_SHOW_FPS_VAL].x;
	perm_rects[RECT_PERM_DES_WINDOW_MODE_VAL].y = perm_rects[RECT_PERM_DES_SHOW_FPS_VAL].y + perm_rects[RECT_PERM_DES_SHOW_FPS_VAL].h + 50;

	perm_rects[RECT_PERM_DES_VOLUME_VAL].x = perm_rects[RECT_PERM_DES_WINDOW_MODE_VAL].x;
	perm_rects[RECT_PERM_DES_VOLUME_VAL].y = perm_rects[RECT_PERM_DES_WINDOW_MODE_VAL].y + perm_rects[RECT_PERM_DES_WINDOW_MODE_VAL].h + 50;

	perm_rects[RECT_PERM_DES_DEV_MODE_VAL].x = perm_rects[RECT_PERM_DES_VOLUME_VAL].x;
	perm_rects[RECT_PERM_DES_DEV_MODE_VAL].y = perm_rects[RECT_PERM_DES_VOLUME_VAL].y + perm_rects[RECT_PERM_DES_VOLUME_VAL].h + 50;

	perm_rects[RECT_PERM_DES_CAMERA_SPEED_VAL].x = perm_rects[RECT_PERM_DES_DEV_MODE_VAL].x;
	perm_rects[RECT_PERM_DES_CAMERA_SPEED_VAL].y = perm_rects[RECT_PERM_DES_DEV_MODE_VAL].y + perm_rects[RECT_PERM_DES_DEV_MODE_VAL].h + 50;


	/*VOLUME SETTINGS*/

	perm_rects[RECT_PERM_DES_MUTE].y = (info_window->height / 2.5);

	perm_rects[RECT_PERM_DES_MUSIC_VOLUME].x = perm_rects[RECT_PERM_DES_MUTE].x;
	perm_rects[RECT_PERM_DES_MUSIC_VOLUME].y = perm_rects[RECT_PERM_DES_MUTE].y + perm_rects[RECT_PERM_DES_MUTE].h + 50;

	perm_rects[RECT_PERM_DES_SFX_VOLUME].x = perm_rects[RECT_PERM_DES_MUSIC_VOLUME].x;
	perm_rects[RECT_PERM_DES_SFX_VOLUME].y = perm_rects[RECT_PERM_DES_MUSIC_VOLUME].y + perm_rects[RECT_PERM_DES_MUSIC_VOLUME].h + 50;

	perm_rects[RECT_PERM_DES_MUTE_VAL].x = perm_rects[RECT_PERM_DES_MUTE].x + perm_rects[RECT_PERM_DES_MUTE].w + 700;
	perm_rects[RECT_PERM_DES_MUTE_VAL].y = perm_rects[RECT_PERM_DES_MUTE].y;

	perm_rects[RECT_PERM_DES_MUSIC_VOLUME_VAL].x = perm_rects[RECT_PERM_DES_MUTE_VAL].x;
	perm_rects[RECT_PERM_DES_MUSIC_VOLUME_VAL].y = perm_rects[RECT_PERM_DES_MUTE_VAL].y + perm_rects[RECT_PERM_DES_MUTE_VAL].h + 50;

	perm_rects[RECT_PERM_DES_SFX_VOLUME_VAL].x = perm_rects[RECT_PERM_DES_MUSIC_VOLUME_VAL].x;
	perm_rects[RECT_PERM_DES_SFX_VOLUME_VAL].y = perm_rects[RECT_PERM_DES_MUSIC_VOLUME_VAL].y + perm_rects[RECT_PERM_DES_MUSIC_VOLUME_VAL].h + 50;


	/*ARE YOU SURE*/

	perm_rects[RECT_PERM_DES_NO].x = (info_window->width - perm_rects[RECT_PERM_DES_NO].w - perm_rects[RECT_PERM_DES_YES].w - 250) / 2;
	perm_rects[RECT_PERM_DES_NO].y = (info_window->height - perm_rects[RECT_PERM_DES_NO].h) / 2 + 150;

	perm_rects[RECT_PERM_DES_YES].x = perm_rects[RECT_PERM_DES_NO].x + perm_rects[RECT_PERM_DES_NO].w + 250;
	perm_rects[RECT_PERM_DES_YES].y = perm_rects[RECT_PERM_DES_NO].y;

	/*WARNINGS*/

	perm_rects[RECT_PERM_DES_ASU].x = (info_window->width - perm_rects[RECT_PERM_DES_ASU].w) / 2;
	perm_rects[RECT_PERM_DES_ASU].y = (info_window->height - perm_rects[RECT_PERM_DES_ASU].h) / 2;

	perm_rects[RECT_PERM_DES_OVERWRITE].x = (info_window->width - perm_rects[RECT_PERM_DES_OVERWRITE].w) / 2;
	perm_rects[RECT_PERM_DES_OVERWRITE].y = (info_window->height - perm_rects[RECT_PERM_DES_OVERWRITE].h) / 2 - 50 - (FONT_SIZE / 1.5);

	perm_rects[RECT_PERM_DES_PROGRESS].x = (info_window->width - perm_rects[RECT_PERM_DES_PROGRESS].w) / 2;
	perm_rects[RECT_PERM_DES_PROGRESS].y = (info_window->height - perm_rects[RECT_PERM_DES_PROGRESS].h) / 2 - 50 - (FONT_SIZE / 1.5);


	/*NEW GAME*/

	perm_rects[RECT_PERM_DES_NEW_GAME].x = (info_window->width - perm_rects[RECT_PERM_DES_NEW_GAME].w) / 2;
	perm_rects[RECT_PERM_DES_NEW_GAME].y = (info_window->height - perm_rects[RECT_PERM_DES_NEW_GAME].h - perm_rects[RECT_PERM_DES_NEW_LOAD_SAVE].h - 50) / 2;

	perm_rects[RECT_PERM_DES_NEW_LOAD_SAVE].x = (info_window->width - perm_rects[RECT_PERM_DES_NEW_LOAD_SAVE].w) / 2;
	perm_rects[RECT_PERM_DES_NEW_LOAD_SAVE].y = perm_rects[RECT_PERM_DES_NEW_GAME].y + perm_rects[RECT_PERM_DES_NEW_GAME].h + 50;

	/*GAME MODE*/

	perm_rects[RECT_PERM_DES_EASY].x = (info_window->width - perm_rects[RECT_PERM_DES_EASY].w) / 2;
	perm_rects[RECT_PERM_DES_EASY].y = (info_window->height - perm_rects[RECT_PERM_DES_EASY].h - perm_rects[RECT_PERM_DES_NORMAL].h -
											perm_rects[RECT_PERM_DES_HARD].h - perm_rects[RECT_PERM_DES_IMPOSSIBLE].h - 50 * 3) / 2;

	perm_rects[RECT_PERM_DES_NORMAL].x = (info_window->width - perm_rects[RECT_PERM_DES_NORMAL].w) / 2;
	perm_rects[RECT_PERM_DES_NORMAL].y = perm_rects[RECT_PERM_DES_EASY].y + perm_rects[RECT_PERM_DES_EASY].h + 50;

	perm_rects[RECT_PERM_DES_HARD].x = (info_window->width - perm_rects[RECT_PERM_DES_HARD].w) / 2;
	perm_rects[RECT_PERM_DES_HARD].y = perm_rects[RECT_PERM_DES_NORMAL].y + perm_rects[RECT_PERM_DES_NORMAL].h + 50;

	perm_rects[RECT_PERM_DES_IMPOSSIBLE].x = (info_window->width - perm_rects[RECT_PERM_DES_IMPOSSIBLE].w) / 2;
	perm_rects[RECT_PERM_DES_IMPOSSIBLE].y = perm_rects[RECT_PERM_DES_HARD].y + perm_rects[RECT_PERM_DES_HARD].h + 50;
}

bool open_start_screen(Game *const game) {

	bool quit_loop = FALSE;
	bool check_quit_loop = FALSE;

	play_chunk(game->audio.sfx[AUDIO_SFX_START_SCREEN].chunk, game->audio.sfx[AUDIO_SFX_START_SCREEN].channel, -1);
	set_chunk_volume(game->audio.sfx[AUDIO_SFX_START_SCREEN].chunk, game->audio.vol_sfx);

	while(quit_loop == FALSE && game->is_running) {

		game->time.timer_start = SDL_GetPerformanceCounter();

		do_events_gui(game);

		if(game->video.effects.fade.state != FADE_STATE_NO_FADE) {
			handle_fade(&(game->video.effects.fade), &(game->video.perm_textures.textures[TEXTURE_PERM_START_SCREEN]), 1);
		}

		SDL_RenderClear(game->video.renderer);
		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_START_SCREEN], NULL, NULL);

		if(game->video.effects.fade.state == FADE_STATE_NO_FADE && check_quit_loop == TRUE) {
			quit_loop = TRUE;
		}

		if(game->video.effects.fade.state == FADE_STATE_NO_FADE && quit_loop == FALSE) {
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_START], NULL, &(game->video.perm_textures.rects[RECT_PERM_START]));
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_QUIT], NULL, &(game->video.perm_textures.rects[RECT_PERM_QUIT]));
		}

		SDL_RenderPresent(game->video.renderer);

		if(game->video.effects.fade.state == FADE_STATE_NO_FADE) {

			if(is_pressed(&(game->input.keyboard), KEY_ESC)) {
				game->input.key = KEY_ESC;
				quit_loop = TRUE;
			}
			else if(is_pressed(&(game->input.keyboard), KEY_ENTER)) {
				game->input.key = KEY_ENTER;
				play_chunk(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].channel, 0);
				set_chunk_volume(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.vol_sfx);
				set_effect_fade_out(&game->video.effects.fade);
				check_quit_loop = TRUE;
			}

			handle_keyboard_time(&(game->input.keyboard), game->time.delta_time);
		}
		else {
			handle_fade_timer(&(game->video.effects.fade), game->time.delta_time);
		}

		game->time.timer_stop = SDL_GetPerformanceCounter();
		game->time.delta_time = get_delta_time(&game->time.timer_start, &game->time.timer_stop);
	}

	SDL_SetTextureAlphaMod(game->video.perm_textures.textures[TEXTURE_PERM_START_SCREEN], 255);

	if(game->is_running == TRUE && game->input.key == KEY_ENTER) {
		return TRUE;
	}
	else {

		return FALSE;
	}

	return FALSE;
	
}

bool open_new_game_screen(Game *const game) {

	bool quit_loop = FALSE;
	SDL_Rect des_select_layer;
	int layer_place = 0;

	while(quit_loop == FALSE && game->is_running) {

		game->time.timer_start = SDL_GetPerformanceCounter();

		do_events_gui(game);

		set_start_game_layer(&des_select_layer, layer_place, game->video.perm_textures.rects);

		SDL_RenderClear(game->video.renderer);

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_NEW_GAME],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_NEW_GAME]));

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_MISC],
							&game->video.perm_textures.rects[RECT_PERM_SRC_SELECT_LAYER], &des_select_layer);

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_LOAD_SAVE],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_NEW_LOAD_SAVE]));

		SDL_RenderPresent(game->video.renderer);

		if(is_pressed(&(game->input.keyboard), KEY_ENTER)) {
			play_chunk(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].channel, 0);
			set_chunk_volume(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.vol_sfx);
			game->input.key = KEY_ENTER;

			if(layer_place == 0) {
				if(open_game_mode_screen(game)) {
					quit_loop = TRUE;
				}
			}
			else if(layer_place == 1) {
				if(load_save(game) == 0) {
					quit_loop = TRUE;
				}
				else {
					show_text_timed_screen(game, game->video.perm_textures.textures[TEXTURE_PERM_FAIL_LOAD], &game->video.perm_textures.rects[RECT_PERM_DES_FAIL_LOAD], 3.0);
				}
			}
		}
		else if(is_pressed(&(game->input.keyboard), KEY_UP) || is_pressed(&(game->input.keyboard), KEY_W)) {
			if(layer_place - 1 >= 0) {
				play_chunk(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].channel, 0);
				set_chunk_volume(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.vol_sfx);
				game->input.key = KEY_DOWN;
				--layer_place;
			}
		}
		else if(is_pressed(&(game->input.keyboard), KEY_DOWN) || is_pressed(&(game->input.keyboard), KEY_S)) {
			if(layer_place + 1 < 2) {
				play_chunk(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].channel, 0);
				set_chunk_volume(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.vol_sfx);
				game->input.key = KEY_UP;
				++layer_place;
			}
		}


		handle_keyboard_time(&(game->input.keyboard), game->time.delta_time);

		game->time.timer_stop = SDL_GetPerformanceCounter();
		game->time.delta_time = get_delta_time(&game->time.timer_start, &game->time.timer_stop);
	}

	Mix_HaltChannel(game->audio.sfx[AUDIO_SFX_START_SCREEN].channel);

	if(game->is_running) {
		return TRUE;
	}

	return FALSE;
}

void set_start_game_layer(SDL_Rect *const des, const int layer_place, SDL_Rect *const rects) {

	int width = 80;
	int height = 50;

	switch(layer_place) {

		case 0:
			des->w = rects[RECT_PERM_DES_NEW_GAME].w + width;
			des->h = rects[RECT_PERM_DES_NEW_GAME].h + height;
			des->x = rects[RECT_PERM_DES_NEW_GAME].x - width / 2;
			des->y = rects[RECT_PERM_DES_NEW_GAME].y - height / 2;
			break;

		case 1:
			des->w = rects[RECT_PERM_DES_NEW_LOAD_SAVE].w + width;
			des->h = rects[RECT_PERM_DES_NEW_LOAD_SAVE].h + height;
			des->x = rects[RECT_PERM_DES_NEW_LOAD_SAVE].x - width / 2;
			des->y = rects[RECT_PERM_DES_NEW_LOAD_SAVE].y - height / 2;
			break;
	}
}

bool open_game_mode_screen(Game *const game) {

	bool quit_loop = FALSE;
	SDL_Rect des_select_layer;
	int layer_place = 0;

	while(quit_loop == FALSE && game->is_running) {

		game->time.timer_start = SDL_GetPerformanceCounter();

		do_events_gui(game);

		set_game_mode_layer(&des_select_layer, layer_place, game->video.perm_textures.rects);

		SDL_RenderClear(game->video.renderer);

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_MISC],
							&game->video.perm_textures.rects[RECT_PERM_SRC_SELECT_LAYER], &des_select_layer);

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_EASY],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_EASY]));

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_NORMAL],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_NORMAL]));

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_HARD],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_HARD]));

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_IMPOSSIBLE],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_IMPOSSIBLE]));

		SDL_RenderPresent(game->video.renderer);

		if(is_pressed(&(game->input.keyboard), KEY_ESC)) {
			game->input.key = KEY_ESC;
			quit_loop = TRUE;
		}
		else if(is_pressed(&(game->input.keyboard), KEY_ENTER)) {
			play_chunk(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].channel, 0);
			set_chunk_volume(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.vol_sfx);
			game->input.key = KEY_ENTER;

			switch(layer_place) {
				case 0:
					game->mode = GAME_MODE_EASY;
					handle_game_mode(game);
					quit_loop = TRUE;
					break;
				case 1:
					game->mode = GAME_MODE_NORMAL;
					handle_game_mode(game);
					quit_loop = TRUE;
					break;
				case 2:
					game->mode = GAME_MODE_HARD;
					handle_game_mode(game);
					quit_loop = TRUE;
					break;
				case 3:
					game->mode = GAME_MODE_IMPOSSIBLE;
					handle_game_mode(game);
					quit_loop = TRUE;
					break;
			}
		}
		else if(is_pressed(&(game->input.keyboard), KEY_UP) || is_pressed(&(game->input.keyboard), KEY_W)) {
			if(layer_place - 1 >= 0) {
				play_chunk(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].channel, 0);
				set_chunk_volume(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.vol_sfx);
				game->input.key = KEY_DOWN;
				--layer_place;
			}
		}
		else if(is_pressed(&(game->input.keyboard), KEY_DOWN) || is_pressed(&(game->input.keyboard), KEY_S)) {
			if(layer_place + 1 < 4) {
				play_chunk(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].channel, 0);
				set_chunk_volume(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.vol_sfx);
				game->input.key = KEY_UP;
				++layer_place;
			}
		}


		handle_keyboard_time(&(game->input.keyboard), game->time.delta_time);

		game->time.timer_stop = SDL_GetPerformanceCounter();
		game->time.delta_time = get_delta_time(&game->time.timer_start, &game->time.timer_stop);
	}

	if(game->input.key == KEY_ENTER) {
		return TRUE;
	}

	return FALSE;
}

void set_game_mode_layer(SDL_Rect *const des, const int layer_place, SDL_Rect *const rects) {

	int width = 80;
	int height = 50;

	switch(layer_place) {

		case 0:
			des->w = rects[RECT_PERM_DES_EASY].w + width;
			des->h = rects[RECT_PERM_DES_EASY].h + height;
			des->x = rects[RECT_PERM_DES_EASY].x - width / 2;
			des->y = rects[RECT_PERM_DES_EASY].y - height / 2;
			break;

		case 1:
			des->w = rects[RECT_PERM_DES_NORMAL].w + width;
			des->h = rects[RECT_PERM_DES_NORMAL].h + height;
			des->x = rects[RECT_PERM_DES_NORMAL].x - width / 2;
			des->y = rects[RECT_PERM_DES_NORMAL].y - height / 2;
			break;

		case 2:
			des->w = rects[RECT_PERM_DES_HARD].w + width;
			des->h = rects[RECT_PERM_DES_HARD].h + height;
			des->x = rects[RECT_PERM_DES_HARD].x - width / 2;
			des->y = rects[RECT_PERM_DES_HARD].y - height / 2;
			break;

		case 3:
			des->w = rects[RECT_PERM_DES_IMPOSSIBLE].w + width;
			des->h = rects[RECT_PERM_DES_IMPOSSIBLE].h + height;
			des->x = rects[RECT_PERM_DES_IMPOSSIBLE].x - width / 2;
			des->y = rects[RECT_PERM_DES_IMPOSSIBLE].y - height / 2;
			break;
	}
}

bool open_level_screen(Game *const game) {

	SDL_Texture *text_world_id = NULL;
	SDL_Texture *text_level_id = NULL;
	int level_id_digit = 0, world_id_digit = 0;
	int place_character_level = game->level.levelID;
	int i;
	int texture_width;
	bool quit_loop = FALSE;
	bool check_quit_loop = FALSE;

	update_level_screen_ids(game->video.renderer, place_character_level, &text_level_id, &text_world_id, game->video.hud.fonts[FONT_MENU], &level_id_digit, &world_id_digit);
	
	game->video.perm_textures.rects[RECT_PERM_DES_WORLD_ID].w = FONT_SIZE * world_id_digit / 2;
	game->video.perm_textures.rects[RECT_PERM_DES_LEVEL].x = game->video.perm_textures.rects[RECT_PERM_DES_WORLD_ID].x + game->video.perm_textures.rects[RECT_PERM_DES_WORLD_ID].w + 5 + 50;
	game->video.perm_textures.rects[RECT_PERM_DES_LEVEL_ID].w = FONT_SIZE * level_id_digit / 2;
	game->video.perm_textures.rects[RECT_PERM_DES_LEVEL_ID].x = game->video.perm_textures.rects[RECT_PERM_DES_LEVEL].x + game->video.perm_textures.rects[RECT_PERM_DES_LEVEL].w + 5;

	play_chunk(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN].chunk, game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN].channel, -1);
	set_chunk_volume(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN].chunk, game->audio.vol_sfx);
	Mix_Pause(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN].channel);

	set_effect_fade_in(&game->video.effects.fade);

	while(quit_loop == FALSE && game->is_running) {

		game->time.timer_start = SDL_GetPerformanceCounter();

		do_events_gui(game);

		if(game->video.effects.fade.state != FADE_STATE_NO_FADE) {
			handle_fade(&(game->video.effects.fade), &(game->video.perm_textures.textures[TEXTURE_PERM_MISC]), 1);
		}
		
		texture_width = ((game->screen.info_window.width - 16 - 100) - 100 - 16) / (LEVEL_COUNT - 1);

		game->video.perm_textures.rects[RECT_PERM_DES_RECTANGLE].w = texture_width - 8;
		game->video.perm_textures.rects[RECT_PERM_DES_SQUARE].x = 100;
		game->video.perm_textures.rects[RECT_PERM_DES_RECTANGLE].x = game->video.perm_textures.rects[RECT_PERM_DES_SQUARE].x + 16;
		game->video.perm_textures.rects[RECT_PERM_DES_CHARACTER].x = game->video.perm_textures.rects[RECT_PERM_DES_SQUARE].x - ((TILE_WIDTH - 16) / 2) + (place_character_level * texture_width + place_character_level * 8);

		SDL_RenderClear(game->video.renderer);

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_MISC], &game->video.perm_textures.rects[RECT_PERM_SRC_GREEN_SQUARE], &game->video.perm_textures.rects[RECT_PERM_DES_SQUARE]);
		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_MISC], &game->video.perm_textures.rects[RECT_PERM_SRC_CHARACTER], &game->video.perm_textures.rects[RECT_PERM_DES_CHARACTER]);

		for(i = 1; i < LEVEL_COUNT; ++i) {

			game->video.perm_textures.rects[RECT_PERM_DES_SQUARE].x += texture_width + 8;

			if(game->level.is_unlocked[i] == TRUE) {
				SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_MISC], &game->video.perm_textures.rects[RECT_PERM_SRC_GREEN_SQUARE], &game->video.perm_textures.rects[RECT_PERM_DES_SQUARE]);
				SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_MISC], &game->video.perm_textures.rects[RECT_PERM_SRC_GREEN_RECTANGLE], &game->video.perm_textures.rects[RECT_PERM_DES_RECTANGLE]);
			}
			else {
				SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_MISC], &game->video.perm_textures.rects[RECT_PERM_SRC_RED_SQUARE], &game->video.perm_textures.rects[RECT_PERM_DES_SQUARE]);
				SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_MISC], &game->video.perm_textures.rects[RECT_PERM_SRC_RED_RECTANGLE], &game->video.perm_textures.rects[RECT_PERM_DES_RECTANGLE]);	
			}

			game->video.perm_textures.rects[RECT_PERM_DES_RECTANGLE].x = game->video.perm_textures.rects[RECT_PERM_DES_SQUARE].x + 16;
		}

		if(game->video.effects.fade.state == FADE_STATE_NO_FADE && check_quit_loop == TRUE) {
			quit_loop = TRUE;
		}

		if(game->video.effects.fade.state == FADE_STATE_NO_FADE && quit_loop == FALSE) {
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_WORLD], NULL, &game->video.perm_textures.rects[RECT_PERM_DES_WORLD]);
			SDL_RenderCopy(game->video.renderer, text_world_id, NULL, &game->video.perm_textures.rects[RECT_PERM_DES_WORLD_ID]);
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_LEVEL], NULL, &game->video.perm_textures.rects[RECT_PERM_DES_LEVEL]);
			SDL_RenderCopy(game->video.renderer, text_level_id, NULL, &game->video.perm_textures.rects[RECT_PERM_DES_LEVEL_ID]);
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_GO], NULL, &game->video.perm_textures.rects[RECT_PERM_DES_GO]);
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_LEVEL_SELECT], NULL, &game->video.perm_textures.rects[RECT_PERM_LEVEL_SELECT]);
		}

		SDL_RenderPresent(game->video.renderer);

		if(game->video.effects.fade.state == FADE_STATE_NO_FADE) {

			Mix_Resume(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN].channel);

			if(is_pressed(&game->input.keyboard, KEY_ENTER)) {
				game->input.key = KEY_ENTER;
				Mix_HaltChannel(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN].channel);
				play_chunk(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].channel, 0);
				set_chunk_volume(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.vol_sfx);
				set_effect_fade_out(&game->video.effects.fade);
				check_quit_loop = TRUE;
			}
			else if(is_pressed(&game->input.keyboard, KEY_D) || is_pressed(&game->input.keyboard, KEY_RIGHT)) {
				if(place_character_level + 1 < LEVEL_COUNT) {
					if(game->level.is_unlocked[place_character_level + 1] == TRUE) {
						play_chunk(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].channel, 0);
						set_chunk_volume(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.vol_sfx);
						++place_character_level;
						update_level_screen_ids(game->video.renderer, place_character_level, &text_level_id, &text_world_id, game->video.hud.fonts[FONT_MENU], &level_id_digit, &world_id_digit);
		
						game->video.perm_textures.rects[RECT_PERM_DES_WORLD_ID].w = FONT_SIZE * world_id_digit / 2;
						game->video.perm_textures.rects[RECT_PERM_DES_LEVEL].x = game->video.perm_textures.rects[RECT_PERM_DES_WORLD_ID].x + game->video.perm_textures.rects[RECT_PERM_DES_WORLD_ID].w + 5 + 50;
						game->video.perm_textures.rects[RECT_PERM_DES_LEVEL_ID].w = FONT_SIZE * level_id_digit / 2;
						game->video.perm_textures.rects[RECT_PERM_DES_LEVEL_ID].x = game->video.perm_textures.rects[RECT_PERM_DES_LEVEL].x + game->video.perm_textures.rects[RECT_PERM_DES_LEVEL].w + 5;
					}
				}
			}
			else if(is_pressed(&game->input.keyboard, KEY_A) || is_pressed(&game->input.keyboard, KEY_LEFT)) {
				if(place_character_level - 1 >= 0) {
					if(game->level.is_unlocked[place_character_level - 1] == TRUE) {
						play_chunk(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].channel, 0);
						set_chunk_volume(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.vol_sfx);
						--place_character_level;
						update_level_screen_ids(game->video.renderer, place_character_level, &text_level_id, &text_world_id, game->video.hud.fonts[FONT_MENU], &level_id_digit, &world_id_digit);
		
						game->video.perm_textures.rects[RECT_PERM_DES_WORLD_ID].w = FONT_SIZE * world_id_digit / 2;
						game->video.perm_textures.rects[RECT_PERM_DES_LEVEL].x = game->video.perm_textures.rects[RECT_PERM_DES_WORLD_ID].x + game->video.perm_textures.rects[RECT_PERM_DES_WORLD_ID].w + 5 + 50;
						game->video.perm_textures.rects[RECT_PERM_DES_LEVEL_ID].w = FONT_SIZE * level_id_digit / 2;
						game->video.perm_textures.rects[RECT_PERM_DES_LEVEL_ID].x = game->video.perm_textures.rects[RECT_PERM_DES_LEVEL].x + game->video.perm_textures.rects[RECT_PERM_DES_LEVEL].w + 5;
					}
				}
			}

			handle_keyboard_time(&game->input.keyboard, game->time.delta_time);
		}
		else {
			handle_fade_timer(&(game->video.effects.fade), game->time.delta_time);
		}

		game->time.timer_stop = SDL_GetPerformanceCounter();
		game->time.delta_time = get_delta_time(&game->time.timer_start, &game->time.timer_stop);
	}

	SDL_SetTextureAlphaMod(game->video.perm_textures.textures[TEXTURE_PERM_MISC], 255);

	if(game->is_running && game->input.key == KEY_ENTER) {
		free_textures(&text_level_id, 1);
		free_textures(&text_world_id, 1);
		game->level.levelID = place_character_level;
		return TRUE;
	}
	else {
		Mix_HaltChannel(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN].channel);
		free_textures(&text_level_id, 1);
		free_textures(&text_world_id, 1);
		return FALSE;
	}

	return FALSE;
}

void update_level_screen_ids(SDL_Renderer *renderer, const int place_character_level, SDL_Texture **text_level_id, SDL_Texture **text_world_id,
								TTF_Font *font, int *const level_id_digit, int *const world_id_digit) {

	SDL_Color white = {
						.r = 255,
						.g = 255,
						.b = 255,
						.a = 255
					};

	char str_level_id[3], str_world_id[3];
	int place_character_level_world;

	free_textures(text_level_id, 1);
	free_textures(text_world_id, 1);
	
	place_character_level_world = (int)get_world_id(place_character_level);

	sprintf(str_level_id, "%d", place_character_level + 1);
	sprintf(str_world_id, "%d", place_character_level_world + 1);

	*world_id_digit = get_digit_count(place_character_level_world);

	*level_id_digit = get_digit_count(place_character_level);

	*text_world_id = get_text(renderer, font, str_world_id, &white);
	*text_level_id = get_text(renderer, font, str_level_id, &white);
}

double handle_menu(Game *const game) {

	Uint64 timer_start, timer_stop;
	double pause_time = 0.0;

	timer_start = SDL_GetPerformanceCounter();

	open_menu(game);

	timer_stop = SDL_GetPerformanceCounter();

	pause_time = get_time_seconds(&timer_start, &timer_stop);

	return pause_time;
}

void open_menu(Game *const game) {

	bool quit_loop = FALSE;
	bool go_next_step = FALSE;
	SDL_Rect des_select_layer;
	int layer_place = 0;

	Mix_Pause(-1);

	while(quit_loop == FALSE && game->is_running) {

		game->time.timer_start = SDL_GetPerformanceCounter();

		do_events_gui(game);

		set_menu_layer(&des_select_layer, layer_place, game->video.perm_textures.rects);

		SDL_RenderClear(game->video.renderer);

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_PAUSE],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_PAUSE]));

		render_player_live(game);

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_MISC],
							&game->video.perm_textures.rects[RECT_PERM_SRC_SELECT_LAYER], &des_select_layer);

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_SETTINGS],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_SETTINGS]));

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_RESTART],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_RESTART]));

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_LEVEL_SCREEN],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_LEVEL_SCREEN]));

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_SAVE_GAME],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_SAVE_GAME]));

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_LOAD_SAVE],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_LOAD_SAVE]));

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_QUIT_GAME],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_QUIT_GAME]));

		SDL_RenderPresent(game->video.renderer);

		if(is_pressed(&(game->input.keyboard), KEY_ESC)) {
			game->input.key = KEY_ESC;
			quit_loop = TRUE;
		}
		else if(is_pressed(&(game->input.keyboard), KEY_ENTER)) {
			play_chunk(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].channel, 0);
			set_chunk_volume(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.vol_sfx);
			game->input.key = KEY_ENTER;
			if(layer_place != 3 && layer_place != 4) {
				handle_menu_events(game, layer_place, &quit_loop);
			}
			else {
				if(layer_place == 3) {
					go_next_step = open_are_you_sure(game, game->video.perm_textures.textures[TEXTURE_PERM_OVERWRITE], &game->video.perm_textures.rects[RECT_PERM_DES_OVERWRITE], TRUE);	
				}
				else {
					go_next_step = open_are_you_sure(game, game->video.perm_textures.textures[TEXTURE_PERM_PROGRESS], &game->video.perm_textures.rects[RECT_PERM_DES_PROGRESS], TRUE);
				}

				if(go_next_step == TRUE) {
					handle_menu_events(game, layer_place, &quit_loop);
				}
			}
		}
		else if(is_pressed(&(game->input.keyboard), KEY_UP) || is_pressed(&(game->input.keyboard), KEY_W)) {
			if(layer_place - 1 >= 0) {
				play_chunk(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].channel, 0);
				set_chunk_volume(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.vol_sfx);
				game->input.key = KEY_DOWN;
				--layer_place;
			}
		}
		else if(is_pressed(&(game->input.keyboard), KEY_DOWN) || is_pressed(&(game->input.keyboard), KEY_S)) {
			if(layer_place + 1 < 6) {
				play_chunk(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].channel, 0);
				set_chunk_volume(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.vol_sfx);
				game->input.key = KEY_UP;
				++layer_place;
			}
		}


		handle_keyboard_time(&(game->input.keyboard), game->time.delta_time);

		game->time.timer_stop = SDL_GetPerformanceCounter();
		game->time.delta_time = get_delta_time(&game->time.timer_start, &game->time.timer_stop);
	}
}

void set_menu_layer(SDL_Rect *const des, const int layer_place, SDL_Rect *const rects) {

	int width = 80;
	int height = 50;

	switch(layer_place) {

		case 0:
			des->w = rects[RECT_PERM_DES_SETTINGS].w + width;
			des->h = rects[RECT_PERM_DES_SETTINGS].h + height;
			des->x = rects[RECT_PERM_DES_SETTINGS].x - width / 2;
			des->y = rects[RECT_PERM_DES_SETTINGS].y - height / 2;
			break;

		case 1:
			des->w = rects[RECT_PERM_DES_RESTART].w + width;
			des->h = rects[RECT_PERM_DES_RESTART].h + height;
			des->x = rects[RECT_PERM_DES_RESTART].x - width / 2;
			des->y = rects[RECT_PERM_DES_RESTART].y - height / 2;
			break;

		case 2:
			des->w = rects[RECT_PERM_DES_LEVEL_SCREEN].w + width;
			des->h = rects[RECT_PERM_DES_LEVEL_SCREEN].h + height;
			des->x = rects[RECT_PERM_DES_LEVEL_SCREEN].x - width / 2;
			des->y = rects[RECT_PERM_DES_LEVEL_SCREEN].y - height / 2;
			break;

		case 3:
			des->w = rects[RECT_PERM_DES_SAVE_GAME].w + width;
			des->h = rects[RECT_PERM_DES_SAVE_GAME].h + height;
			des->x = rects[RECT_PERM_DES_SAVE_GAME].x - width / 2;
			des->y = rects[RECT_PERM_DES_SAVE_GAME].y - height / 2;
			break;

		case 4:
			des->w = rects[RECT_PERM_DES_LOAD_SAVE].w + width;
			des->h = rects[RECT_PERM_DES_LOAD_SAVE].h + height;
			des->x = rects[RECT_PERM_DES_LOAD_SAVE].x - width / 2;
			des->y = rects[RECT_PERM_DES_LOAD_SAVE].y - height / 2;
			break;

		case 5:
			des->w = rects[RECT_PERM_DES_QUIT_GAME].w + width;
			des->h = rects[RECT_PERM_DES_QUIT_GAME].h + height;
			des->x = rects[RECT_PERM_DES_QUIT_GAME].x - width / 2;
			des->y = rects[RECT_PERM_DES_QUIT_GAME].y - height / 2;
			break;
	}
}

bool open_are_you_sure(Game *const game, SDL_Texture *texture_warning, SDL_Rect *des_warning, const bool show_asu) {

	bool quit_loop = FALSE;
	int layer_place = 0;
	SDL_Rect des_select_layer;

	while(quit_loop == FALSE && game->is_running) {

		game->time.timer_start = SDL_GetPerformanceCounter();

		do_events_gui(game);

		set_are_you_sure_layer(&des_select_layer, layer_place, game->video.perm_textures.rects);

		SDL_RenderClear(game->video.renderer);

		if(texture_warning != NULL && des_warning != NULL) {
			SDL_RenderCopy(game->video.renderer, texture_warning, NULL, des_warning);
		}

		if(show_asu) {
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_ASU],
								NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_ASU]));
		}

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_MISC],
							&game->video.perm_textures.rects[RECT_PERM_SRC_SELECT_LAYER], &des_select_layer);

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_NO],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_NO]));

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_YES],
							NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_YES]));

		SDL_RenderPresent(game->video.renderer);


		if(is_pressed(&(game->input.keyboard), KEY_ESC)) {
			game->input.key = KEY_ESC;
			quit_loop = TRUE;
		}
		else if(is_pressed(&(game->input.keyboard), KEY_ENTER)) {
			game->input.key = KEY_ENTER;
			play_chunk(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].channel, 0);
			set_chunk_volume(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.vol_sfx);
			quit_loop = TRUE;
		}
		else if(is_pressed(&(game->input.keyboard), KEY_LEFT) || is_pressed(&(game->input.keyboard), KEY_A)) {
			if(layer_place - 1 >= 0) {
				play_chunk(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].channel, 0);
				set_chunk_volume(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.vol_sfx);
				--layer_place;
			}
		}
		else if(is_pressed(&(game->input.keyboard), KEY_RIGHT) || is_pressed(&(game->input.keyboard), KEY_D)) {
			if(layer_place + 1 < 2) {
				play_chunk(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].channel, 0);
				set_chunk_volume(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.vol_sfx);
				++layer_place;
			}
		}

		handle_keyboard_time(&(game->input.keyboard), game->time.delta_time);

		game->time.timer_stop = SDL_GetPerformanceCounter();
		game->time.delta_time = get_delta_time(&game->time.timer_start, &game->time.timer_stop);
	}

	if(game->is_running == TRUE && game->input.key != KEY_ESC) {
		if(game->input.key == KEY_ENTER && layer_place == 1) {
			return TRUE;
		}
	}

	return FALSE;
}

void set_are_you_sure_layer(SDL_Rect *const des, const int layer_place, SDL_Rect *const rects) {

	int width = 80;
	int height = 50;

	switch(layer_place) {

		case 0:
			des->w = rects[RECT_PERM_DES_NO].w + width;
			des->h = rects[RECT_PERM_DES_NO].h + height;
			des->x = rects[RECT_PERM_DES_NO].x - width / 2;
			des->y = rects[RECT_PERM_DES_NO].y - height / 2;
			break;

		case 1:
			des->w = rects[RECT_PERM_DES_YES].w + width;
			des->h = rects[RECT_PERM_DES_YES].h + height;
			des->x = rects[RECT_PERM_DES_YES].x - width / 2;
			des->y = rects[RECT_PERM_DES_YES].y - height / 2;
			break;
	}
}

void open_settings(Game *const game) {

	bool quit_loop = FALSE;
	SDL_Rect des_select_layer, des_arrow_left, des_arrow_right;
	int layer_place = 0;
	GuiSettings changing = GUI_SETTINGS_NOTHING;
	bool old_situation;
	int old_value;
	WindowModes old_mode;

	while(quit_loop == FALSE && game->is_running) {

		game->time.timer_start = SDL_GetPerformanceCounter();

		do_events_gui(game);

		SDL_RenderClear(game->video.renderer);

		if(changing == GUI_SETTINGS_NOTHING) {
			set_settings_layer(&des_select_layer, layer_place, game->video.perm_textures.rects);
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_MISC],
							&game->video.perm_textures.rects[RECT_PERM_SRC_SELECT_LAYER], &des_select_layer);
		}
		else {
			set_settings_arrows(&des_arrow_left,  &des_arrow_right, layer_place, game->video.perm_textures.rects);
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_MISC],
							&game->video.perm_textures.rects[RECT_PERM_SRC_ARROW_LEFT], &des_arrow_left);
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_MISC],
							&game->video.perm_textures.rects[RECT_PERM_SRC_ARROW_RIGHT], &des_arrow_right);
		}

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_FPS_LOCK],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_FPS_LOCK]));

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_SHOW_FPS],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_SHOW_FPS]));

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_WINDOW_MODE],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_WINDOW_MODE]));

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_VOLUME],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_VOLUME]));

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_DEV_MODE],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_DEV_MODE]));

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_CAMERA_SPEED],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_CAMERA_SPEED]));

		render_settings_val(game);

		SDL_RenderPresent(game->video.renderer);

		if(changing == GUI_SETTINGS_NOTHING) {
			if(is_pressed(&(game->input.keyboard), KEY_ESC)) {
				game->input.key = KEY_ESC;
				quit_loop = TRUE;
			}
			else if(is_pressed(&(game->input.keyboard), KEY_ENTER)) {
				if(layer_place != 3) {
					play_chunk(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].channel, 0);
					set_chunk_volume(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.vol_sfx);
					game->input.key = KEY_ENTER;
					changing = (GuiSettings)layer_place;
					set_old_values(game, layer_place, &old_situation, &old_value, &old_mode);
				}
				else {
					play_chunk(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].channel, 0);
					set_chunk_volume(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.vol_sfx);
					game->input.key = KEY_ENTER;
					open_volume_settings(game);
				}
			}
			else if(is_pressed(&(game->input.keyboard), KEY_UP) || is_pressed(&(game->input.keyboard), KEY_W)) {
				if(layer_place - 1 >= 0) {
					play_chunk(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].channel, 0);
					set_chunk_volume(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.vol_sfx);
					game->input.key = KEY_DOWN;
					--layer_place;
				}
			}
			else if(is_pressed(&(game->input.keyboard), KEY_DOWN) || is_pressed(&(game->input.keyboard), KEY_S)) {
				if(layer_place + 1 < 6) {
					play_chunk(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].channel, 0);
					set_chunk_volume(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.vol_sfx);
					game->input.key = KEY_UP;
					++layer_place;
				}
			}
		}
		else {
			if(is_pressed(&(game->input.keyboard), KEY_ESC)) {
				game->input.key = KEY_ESC;
				changing = GUI_SETTINGS_NOTHING;
				change_to_old_values(game, layer_place, old_situation, old_value, old_mode);
			}
			else if(is_pressed(&(game->input.keyboard), KEY_ENTER)) {
				play_chunk(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].channel, 0);
				set_chunk_volume(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.vol_sfx);
				changing = GUI_SETTINGS_NOTHING;
				game->input.key = KEY_ENTER;

				if(layer_place == 2) {
					if(old_mode != game->screen.info_window.mode) {
						game->settings.window.should_change = TRUE;
						handle_window_mode(game);
					}
				}
				else if(layer_place == 4) {
					if(old_situation == FALSE && game->settings.dev_mode.is_on == TRUE) {
						game->settings.dev_mode.is_saved = FALSE;
					}
					else if(old_situation == TRUE && game->settings.dev_mode.is_on == FALSE) {
						game->settings.dev_mode.is_loaded = FALSE;	
					}
				}
			}
			else if(is_pressed(&(game->input.keyboard), KEY_LEFT) || is_pressed(&(game->input.keyboard), KEY_A)) {
				game->input.key = KEY_LEFT;
				update_settings(game, game->input.key, layer_place);
			}
			else if(is_pressed(&(game->input.keyboard), KEY_RIGHT) || is_pressed(&(game->input.keyboard), KEY_D)) {
				game->input.key = KEY_RIGHT;
				update_settings(game, game->input.key, layer_place);
			}
		}

		handle_keyboard_time(&(game->input.keyboard), game->time.delta_time);

		game->time.timer_stop = SDL_GetPerformanceCounter();
		game->time.delta_time = get_delta_time(&game->time.timer_start, &game->time.timer_stop);
	}
}

void set_settings_layer(SDL_Rect *const des, const int layer_place, SDL_Rect *const rects) {

	int width = 80;
	int height = 50;

	switch(layer_place) {

		case 0:
			des->w = rects[RECT_PERM_DES_FPS_LOCK].w + width;
			des->h = rects[RECT_PERM_DES_FPS_LOCK].h + height;
			des->x = rects[RECT_PERM_DES_FPS_LOCK].x - width / 2;
			des->y = rects[RECT_PERM_DES_FPS_LOCK].y - height / 2;
			break;

		case 1:
			des->w = rects[RECT_PERM_DES_SHOW_FPS].w + width;
			des->h = rects[RECT_PERM_DES_SHOW_FPS].h + height;
			des->x = rects[RECT_PERM_DES_SHOW_FPS].x - width / 2;
			des->y = rects[RECT_PERM_DES_SHOW_FPS].y - height / 2;
			break;

		case 2:
			des->w = rects[RECT_PERM_DES_WINDOW_MODE].w + width;
			des->h = rects[RECT_PERM_DES_WINDOW_MODE].h + height;
			des->x = rects[RECT_PERM_DES_WINDOW_MODE].x - width / 2;
			des->y = rects[RECT_PERM_DES_WINDOW_MODE].y - height / 2;
			break;

		case 3:
			des->w = rects[RECT_PERM_DES_VOLUME].w + width;
			des->h = rects[RECT_PERM_DES_VOLUME].h + height;
			des->x = rects[RECT_PERM_DES_VOLUME].x - width / 2;
			des->y = rects[RECT_PERM_DES_VOLUME].y - height / 2;
			break;

		case 4:
			des->w = rects[RECT_PERM_DES_DEV_MODE].w + width;
			des->h = rects[RECT_PERM_DES_DEV_MODE].h + height;
			des->x = rects[RECT_PERM_DES_DEV_MODE].x - width / 2;
			des->y = rects[RECT_PERM_DES_DEV_MODE].y - height / 2;
			break;

		case 5:
			des->w = rects[RECT_PERM_DES_CAMERA_SPEED].w + width;
			des->h = rects[RECT_PERM_DES_CAMERA_SPEED].h + height;
			des->x = rects[RECT_PERM_DES_CAMERA_SPEED].x - width / 2;
			des->y = rects[RECT_PERM_DES_CAMERA_SPEED].y - height / 2;
			break;
	}
}

void set_settings_arrows(SDL_Rect *const des_left, SDL_Rect *const des_right, const int layer_place, SDL_Rect *const rects) {

	des_right->w = 17;
	des_right->h = 14;

	des_left->w = 17;
	des_left->h = 14;

	switch(layer_place) {

		case 0:
			des_right->x = rects[RECT_PERM_DES_FPS_LOCK_VAL].x - des_right->w - 10;
			des_right->y = rects[RECT_PERM_DES_FPS_LOCK_VAL].y + (rects[RECT_PERM_DES_FPS_LOCK_VAL].h / 2) - (des_right->h / 2);

			des_left->x = rects[RECT_PERM_DES_FPS_LOCK_VAL].x + rects[RECT_PERM_DES_FPS_LOCK_VAL].w + 10;
			des_left->y = rects[RECT_PERM_DES_FPS_LOCK_VAL].y + (rects[RECT_PERM_DES_FPS_LOCK_VAL].h / 2) - (des_left->h / 2);
			break;

		case 1:
			des_right->x = rects[RECT_PERM_DES_SHOW_FPS_VAL].x - des_right->w - 10;
			des_right->y = rects[RECT_PERM_DES_SHOW_FPS_VAL].y + (rects[RECT_PERM_DES_SHOW_FPS_VAL].h / 2) - (des_right->h / 2);

			des_left->x = rects[RECT_PERM_DES_SHOW_FPS_VAL].x + rects[RECT_PERM_DES_SHOW_FPS_VAL].w + 10;
			des_left->y = rects[RECT_PERM_DES_SHOW_FPS_VAL].y + (rects[RECT_PERM_DES_SHOW_FPS_VAL].h / 2) - (des_left->h / 2);
			break;

		case 2:
			des_right->x = rects[RECT_PERM_DES_WINDOW_MODE_VAL].x - des_right->w - 10;
			des_right->y = rects[RECT_PERM_DES_WINDOW_MODE_VAL].y + (rects[RECT_PERM_DES_WINDOW_MODE_VAL].h / 2) - (des_right->h / 2);

			des_left->x = rects[RECT_PERM_DES_WINDOW_MODE_VAL].x + rects[RECT_PERM_DES_WINDOW_MODE_VAL].w + 10;
			des_left->y = rects[RECT_PERM_DES_WINDOW_MODE_VAL].y + (rects[RECT_PERM_DES_WINDOW_MODE_VAL].h / 2) - (des_left->h / 2);
			break;

		case 4:
			des_right->x = rects[RECT_PERM_DES_DEV_MODE_VAL].x - des_right->w - 10;
			des_right->y = rects[RECT_PERM_DES_DEV_MODE_VAL].y + (rects[RECT_PERM_DES_DEV_MODE_VAL].h / 2) - (des_right->h / 2);

			des_left->x = rects[RECT_PERM_DES_DEV_MODE_VAL].x + rects[RECT_PERM_DES_DEV_MODE_VAL].w + 10;
			des_left->y = rects[RECT_PERM_DES_DEV_MODE_VAL].y + (rects[RECT_PERM_DES_DEV_MODE_VAL].h / 2) - (des_left->h / 2);
			break;

		case 5:
			des_right->x = rects[RECT_PERM_DES_CAMERA_SPEED_VAL].x - des_right->w - 10;
			des_right->y = rects[RECT_PERM_DES_CAMERA_SPEED_VAL].y + (rects[RECT_PERM_DES_CAMERA_SPEED_VAL].h / 2) - (des_right->h / 2);

			des_left->x = rects[RECT_PERM_DES_CAMERA_SPEED_VAL].x + rects[RECT_PERM_DES_CAMERA_SPEED_VAL].w + 10;
			des_left->y = rects[RECT_PERM_DES_CAMERA_SPEED_VAL].y + (rects[RECT_PERM_DES_CAMERA_SPEED_VAL].h / 2) - (des_left->h / 2);
			break;
	}
}

void set_old_values(Game *const game, const int layer_place, bool *old_situation, int *old_value, WindowModes *old_mode) {

	switch(layer_place) {
		case 0:
			(*old_situation) = game->settings.fps.lock;
			(*old_value) = game->settings.fps.per_second;
			break;
		case 1:
			(*old_situation) = game->settings.fps.show;
			break;
		case 2:
			(*old_mode) = game->screen.info_window.mode;
			break;
		case 4:
			(*old_situation) = game->settings.dev_mode.is_on;
			break;
		case 5:
			(*old_value) = (int)(game->screen.camera.speed * 100);
			break;
	}
}

void change_to_old_values(Game *const game, const int layer_place, const bool old_situation, const int old_value, const WindowModes old_mode) {

	switch(layer_place) {
		case 0:
			game->settings.fps.lock = old_situation;
			game->settings.fps.per_second = old_value;
			break;
		case 1:
			game->settings.fps.show = old_situation;
			break;
		case 2:
			game->screen.info_window.mode = old_mode;
			break;
		case 4:
			game->settings.dev_mode.is_on = old_situation;
			break;

		case 5:
			game->screen.camera.speed = old_value / 100.0;
			break;
	}
}

void update_settings(Game *const game, const Key key, const int layer_place) {

	switch(layer_place) {

		case 0:
			if(game->settings.fps.lock == FALSE) {
				game->settings.fps.lock = TRUE;
				if(key == KEY_LEFT) {
					game->settings.fps.per_second = 240;
				}
				else {
					game->settings.fps.per_second = 30;
				}
			}
			else {
				switch(game->settings.fps.per_second) {
					case 240:
						if(key == KEY_LEFT) game->settings.fps.per_second = 160;
						else {
							game->settings.fps.per_second = 30;
							game->settings.fps.lock = FALSE;
						}
						break;
					case 160:
						if(key == KEY_LEFT) game->settings.fps.per_second = 144;
						else game->settings.fps.per_second = 240;
						break;
					case 144:
						if(key == KEY_LEFT) game->settings.fps.per_second = 120;
						else game->settings.fps.per_second = 160;
						break;
					case 120:
						if(key == KEY_LEFT) game->settings.fps.per_second = 75;
						else game->settings.fps.per_second = 144;
						break;
					case 75:
						if(key == KEY_LEFT) game->settings.fps.per_second = 60;
						else game->settings.fps.per_second = 120;
						break;
					case 60:
						if(key == KEY_LEFT) game->settings.fps.per_second = 30;
						else game->settings.fps.per_second = 75;
						break;
					case 30:
						if(key == KEY_LEFT) {
							game->settings.fps.lock = FALSE;
							game->settings.fps.per_second = 240;
						}
						else game->settings.fps.per_second = 60;
						break; 
					default:
						break;
				}
			}
			break;
		case 1:
			if(game->settings.fps.show == FALSE) game->settings.fps.show = TRUE;
			else game->settings.fps.show = FALSE;
			break;
		case 2:
			if(game->screen.info_window.mode == WINDOW_MODE_WINDOWED) {
				if(key == KEY_LEFT) game->screen.info_window.mode = WINDOW_MODE_FULLSCREEN;
				else game->screen.info_window.mode = WINDOW_MODE_BORDERLESS;
			}
			else if(game->screen.info_window.mode == WINDOW_MODE_FULLSCREEN) {
					if(key == KEY_LEFT) game->screen.info_window.mode = WINDOW_MODE_BORDERLESS;
					else game->screen.info_window.mode = WINDOW_MODE_WINDOWED;
			}
			else if(game->screen.info_window.mode == WINDOW_MODE_BORDERLESS) {
					if(key == KEY_LEFT) game->screen.info_window.mode = WINDOW_MODE_WINDOWED;
					else game->screen.info_window.mode = WINDOW_MODE_FULLSCREEN;
			}
			break;
		case 4:
			if(game->settings.dev_mode.is_on == TRUE) {
				game->settings.dev_mode.is_on = FALSE;
			}
			else {
				game->settings.dev_mode.is_on = TRUE;
			}
			break;
		case 5:
			switch((int)(game->screen.camera.speed * 100)) {
				case 100:
					if(key == KEY_LEFT) game->screen.camera.speed = 0.9;
					else game->screen.camera.speed = 0.1;
					break;
				case 90:
					if(key == KEY_LEFT) game->screen.camera.speed = 0.8;
					else game->screen.camera.speed = 1.0;
					break;
				case 80:
					if(key == KEY_LEFT) game->screen.camera.speed = 0.7;
					else game->screen.camera.speed = 0.9;
					break;
				case 70:
					if(key == KEY_LEFT) game->screen.camera.speed = 0.6;
					else game->screen.camera.speed = 0.8;
					break;
				case 60:
					if(key == KEY_LEFT) game->screen.camera.speed = 0.5;
					else game->screen.camera.speed = 0.7;
					break;
				case 50:
					if(key == KEY_LEFT) game->screen.camera.speed = 0.4;
					else game->screen.camera.speed = 0.6;
					break;
				case 40:
					if(key == KEY_LEFT) game->screen.camera.speed = 0.3;
					else game->screen.camera.speed = 0.5;
					break;
				case 30:
					if(key == KEY_LEFT) game->screen.camera.speed = 0.2;
					else game->screen.camera.speed = 0.4;
					break;
				case 20:
					if(key == KEY_LEFT) game->screen.camera.speed = 0.1;
					else game->screen.camera.speed = 0.3;
					break;
				case 10:
					if(key == KEY_LEFT) game->screen.camera.speed = 1.0;
					else game->screen.camera.speed = 0.2;
					break;
			}
		default:
			break;
	}
}

void open_volume_settings(Game *const game) {

	bool quit_loop = FALSE;
	SDL_Rect des_select_layer, des_arrow_left, des_arrow_right;
	int layer_place = 0;
	GuiVolume changing = GUI_VOLUME_NOTHING;
	bool old_situation;
	int old_value;

	while(quit_loop == FALSE && game->is_running) {

		game->time.timer_start = SDL_GetPerformanceCounter();

		do_events_gui(game);

		SDL_RenderClear(game->video.renderer);

		if(changing == GUI_VOLUME_NOTHING) {
			set_volume_settings_layer(&des_select_layer, layer_place, game->video.perm_textures.rects);
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_MISC],
							&game->video.perm_textures.rects[RECT_PERM_SRC_SELECT_LAYER], &des_select_layer);
		}
		else {
			set_volume_settings_arrows(&des_arrow_left,  &des_arrow_right, layer_place, game->video.perm_textures.rects);
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_MISC],
							&game->video.perm_textures.rects[RECT_PERM_SRC_ARROW_LEFT], &des_arrow_left);
			SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_MISC],
							&game->video.perm_textures.rects[RECT_PERM_SRC_ARROW_RIGHT], &des_arrow_right);
		}

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_MUTE],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_MUTE]));

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_MUSIC_VOLUME],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_MUSIC_VOLUME]));

		SDL_RenderCopy(game->video.renderer, game->video.perm_textures.textures[TEXTURE_PERM_SFX_VOLUME],
						NULL, &(game->video.perm_textures.rects[RECT_PERM_DES_SFX_VOLUME]));

		render_volume_settings_val(game);

		SDL_RenderPresent(game->video.renderer);

		if(changing == GUI_VOLUME_NOTHING) {
			if(is_pressed(&(game->input.keyboard), KEY_ESC)) {
				game->input.key = KEY_ESC;
				quit_loop = TRUE;
			}
			else if(is_pressed(&(game->input.keyboard), KEY_ENTER)) {
				play_chunk(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].channel, 0);
				set_chunk_volume(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.vol_sfx);
				game->input.key = KEY_ENTER;
				changing = (GuiVolume)layer_place;
				set_old_values_volume(game, layer_place, &old_situation, &old_value);
			}
			else if(is_pressed(&(game->input.keyboard), KEY_UP) || is_pressed(&(game->input.keyboard), KEY_W)) {
				if(layer_place - 1 >= 0) {
					play_chunk(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].channel, 0);
					set_chunk_volume(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.vol_sfx);
					game->input.key = KEY_DOWN;
					--layer_place;
				}
			}
			else if(is_pressed(&(game->input.keyboard), KEY_DOWN) || is_pressed(&(game->input.keyboard), KEY_S)) {
				if(game->audio.mute == FALSE) {
					if(layer_place + 1 < 3) {
						play_chunk(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].channel, 0);
						set_chunk_volume(game->audio.sfx[AUDIO_SFX_LEVEL_SCREEN_MOVE].chunk, game->audio.vol_sfx);
						game->input.key = KEY_UP;
						++layer_place;
					}
				}
			}
		}
		else {
			if(is_pressed(&(game->input.keyboard), KEY_ESC)) {
				game->input.key = KEY_ESC;
				changing = GUI_VOLUME_NOTHING;
				change_to_old_values_volume(game, layer_place, old_situation, old_value);
			}
			else if(is_pressed(&(game->input.keyboard), KEY_ENTER)) {
				play_chunk(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].channel, 0);
				set_chunk_volume(game->audio.sfx[AUDIO_SFX_SCREEN_SELECT].chunk, game->audio.vol_sfx);
				changing = GUI_VOLUME_NOTHING;
				game->input.key = KEY_ENTER;

				if(layer_place == 0) {
					if(old_situation == TRUE && game->audio.mute == FALSE) {
						convert_fake_volume_real(&game->audio, GUI_VOLUME_UNMUTE);
					}
					else if(old_situation == FALSE && game->audio.mute == TRUE) {
						convert_fake_volume_real(&game->audio, GUI_VOLUME_MUTE);	
					}
				}	
				else {
					convert_fake_volume_real(&game->audio, (GuiVolume)(layer_place));
				}

				change_volume_sounds(&game->audio);
			}
			else if(is_pressed(&(game->input.keyboard), KEY_LEFT) || is_pressed(&(game->input.keyboard), KEY_A)) {
				game->input.key = KEY_LEFT;
				update_volume_settings(game, game->input.key, layer_place);
			}
			else if(is_pressed(&(game->input.keyboard), KEY_RIGHT) || is_pressed(&(game->input.keyboard), KEY_D)) {
				game->input.key = KEY_RIGHT;
				update_volume_settings(game, game->input.key, layer_place);
			}
		}

		handle_keyboard_time(&(game->input.keyboard), game->time.delta_time);

		game->time.timer_stop = SDL_GetPerformanceCounter();
		game->time.delta_time = get_delta_time(&game->time.timer_start, &game->time.timer_stop);
	}
}

void set_volume_settings_layer(SDL_Rect *const des, const int layer_place, SDL_Rect *const rects) {

	int width = 80;
	int height = 50;

	switch(layer_place) {

		case 0:
			des->w = rects[RECT_PERM_DES_MUTE].w + width;
			des->h = rects[RECT_PERM_DES_MUTE].h + height;
			des->x = rects[RECT_PERM_DES_MUTE].x - width / 2;
			des->y = rects[RECT_PERM_DES_MUTE].y - height / 2;
			break;

		case 1:
			des->w = rects[RECT_PERM_DES_MUSIC_VOLUME].w + width;
			des->h = rects[RECT_PERM_DES_MUSIC_VOLUME].h + height;
			des->x = rects[RECT_PERM_DES_MUSIC_VOLUME].x - width / 2;
			des->y = rects[RECT_PERM_DES_MUSIC_VOLUME].y - height / 2;
			break;

		case 2:
			des->w = rects[RECT_PERM_DES_SFX_VOLUME].w + width;
			des->h = rects[RECT_PERM_DES_SFX_VOLUME].h + height;
			des->x = rects[RECT_PERM_DES_SFX_VOLUME].x - width / 2;
			des->y = rects[RECT_PERM_DES_SFX_VOLUME].y - height / 2;
			break;
	}
}

void set_volume_settings_arrows(SDL_Rect *const des_left, SDL_Rect *const des_right, const int layer_place, SDL_Rect *const rects) {

	des_right->w = 17;
	des_right->h = 14;

	des_left->w = 17;
	des_left->h = 14;

	switch(layer_place) {

		case 0:
			des_right->x = rects[RECT_PERM_DES_MUTE_VAL].x - des_right->w - 10;
			des_right->y = rects[RECT_PERM_DES_MUTE_VAL].y + (rects[RECT_PERM_DES_MUTE_VAL].h / 2) - (des_right->h / 2);

			des_left->x = rects[RECT_PERM_DES_MUTE_VAL].x + rects[RECT_PERM_DES_MUTE_VAL].w + 10;
			des_left->y = rects[RECT_PERM_DES_MUTE_VAL].y + (rects[RECT_PERM_DES_MUTE_VAL].h / 2) - (des_left->h / 2);
			break;

		case 1:
			des_right->x = rects[RECT_PERM_DES_MUSIC_VOLUME_VAL].x - des_right->w - 10;
			des_right->y = rects[RECT_PERM_DES_MUSIC_VOLUME_VAL].y + (rects[RECT_PERM_DES_MUSIC_VOLUME_VAL].h / 2) - (des_right->h / 2);

			des_left->x = rects[RECT_PERM_DES_MUSIC_VOLUME_VAL].x + rects[RECT_PERM_DES_MUSIC_VOLUME_VAL].w + 10;
			des_left->y = rects[RECT_PERM_DES_MUSIC_VOLUME_VAL].y + (rects[RECT_PERM_DES_MUSIC_VOLUME_VAL].h / 2) - (des_left->h / 2);
			break;

		case 2:
			des_right->x = rects[RECT_PERM_DES_SFX_VOLUME_VAL].x - des_right->w - 10;
			des_right->y = rects[RECT_PERM_DES_SFX_VOLUME_VAL].y + (rects[RECT_PERM_DES_SFX_VOLUME_VAL].h / 2) - (des_right->h / 2);

			des_left->x = rects[RECT_PERM_DES_SFX_VOLUME_VAL].x + rects[RECT_PERM_DES_SFX_VOLUME_VAL].w + 10;
			des_left->y = rects[RECT_PERM_DES_SFX_VOLUME_VAL].y + (rects[RECT_PERM_DES_SFX_VOLUME_VAL].h / 2) - (des_left->h / 2);
			break;
	}
}

void set_old_values_volume(Game *const game, const int layer_place, bool *old_situation, int *old_value) {

	switch(layer_place) {
		case 0:
			(*old_situation) = game->audio.mute;
			break;
		case 1:
			(*old_value) = game->audio.fake_volume_music;
			break;
		case 2:
			(*old_value) = game->audio.fake_volume_sfx;
			break;
	}
}

void change_to_old_values_volume(Game *const game, const int layer_place, const bool old_situation, const int old_value) {

	switch(layer_place) {
		case 0:
			game->audio.mute = old_situation;
			break;
		case 1:
			game->audio.fake_volume_music = old_value;
			break;
		case 2:
			game->audio.fake_volume_sfx = old_value;
			break;
	}
}

void update_volume_settings(Game *const game, const Key key, const int layer_place) {

	switch(layer_place) {

		case 0:
			if(game->audio.mute == FALSE) game->audio.mute = TRUE;
			else game->audio.mute = FALSE;
			break;
		case 1:
			switch(game->audio.fake_volume_music) {
				case 100:
					if(key == KEY_LEFT) game->audio.fake_volume_music = 90;
					else game->audio.fake_volume_music = 0;
					break;
				case 90:
					if(key == KEY_LEFT) game->audio.fake_volume_music = 80;
					else game->audio.fake_volume_music= 100;
					break;
				case 80:
					if(key == KEY_LEFT) game->audio.fake_volume_music = 70;
					else game->audio.fake_volume_music = 90;
					break;
				case 70:
					if(key == KEY_LEFT) game->audio.fake_volume_music = 60;
					else game->audio.fake_volume_music = 80;
					break;
				case 60:
					if(key == KEY_LEFT) game->audio.fake_volume_music = 50;
					else game->audio.fake_volume_music = 70;
					break;
				case 50:
					if(key == KEY_LEFT) game->audio.fake_volume_music = 40;
					else game->audio.fake_volume_music = 60;
					break;
				case 40:
					if(key == KEY_LEFT) game->audio.fake_volume_music = 30;
					else game->audio.fake_volume_music = 50;
					break;
				case 30:
					if(key == KEY_LEFT) game->audio.fake_volume_music = 20;
					else game->audio.fake_volume_music = 40;
					break;
				case 20:
					if(key == KEY_LEFT) game->audio.fake_volume_music = 10;
					else game->audio.fake_volume_music = 30;
					break;
				case 10:
					if(key == KEY_LEFT) game->audio.fake_volume_music = 0;
					else game->audio.fake_volume_music = 20;
					break;
				case 0:
					if(key == KEY_LEFT) game->audio.fake_volume_music = 100;
					else game->audio.fake_volume_music = 10;
					break;
			}
			break;
		case 2:
			switch(game->audio.fake_volume_sfx) {
				case 100:
					if(key == KEY_LEFT) game->audio.fake_volume_sfx = 90;
					else game->audio.fake_volume_sfx = 0;
					break;
				case 90:
					if(key == KEY_LEFT) game->audio.fake_volume_sfx = 80;
					else game->audio.fake_volume_sfx= 100;
					break;
				case 80:
					if(key == KEY_LEFT) game->audio.fake_volume_sfx = 70;
					else game->audio.fake_volume_sfx = 90;
					break;
				case 70:
					if(key == KEY_LEFT) game->audio.fake_volume_sfx = 60;
					else game->audio.fake_volume_sfx = 80;
					break;
				case 60:
					if(key == KEY_LEFT) game->audio.fake_volume_sfx = 50;
					else game->audio.fake_volume_sfx = 70;
					break;
				case 50:
					if(key == KEY_LEFT) game->audio.fake_volume_sfx = 40;
					else game->audio.fake_volume_sfx = 60;
					break;
				case 40:
					if(key == KEY_LEFT) game->audio.fake_volume_sfx = 30;
					else game->audio.fake_volume_sfx = 50;
					break;
				case 30:
					if(key == KEY_LEFT) game->audio.fake_volume_sfx = 20;
					else game->audio.fake_volume_sfx = 40;
					break;
				case 20:
					if(key == KEY_LEFT) game->audio.fake_volume_sfx = 10;
					else game->audio.fake_volume_sfx = 30;
					break;
				case 10:
					if(key == KEY_LEFT) game->audio.fake_volume_sfx = 0;
					else game->audio.fake_volume_sfx = 20;
					break;
				case 0:
					if(key == KEY_LEFT) game->audio.fake_volume_sfx = 100;
					else game->audio.fake_volume_sfx = 10;
					break;
			}
			break;
		default:
			break;
	}
}

SDL_Texture* get_text(SDL_Renderer *renderer, TTF_Font *font, char *str, SDL_Color *color) {

	SDL_Surface *surface = NULL;
	SDL_Texture *text = NULL;

	surface = TTF_RenderText_Solid(font, str, *color);
	text = get_texture(renderer, surface);

	SDL_FreeSurface(surface);

	return text;
}

void free_fonts_wsize(TTF_Font **fonts, const int size) {

	int i;

	for(i = 0; i < size; ++i) {
		if(fonts[i] != NULL) {
			TTF_CloseFont(fonts[i]);
			fonts[i] = NULL;
		}
	}
}

void free_fonts(TTF_Font **fonts) {

	int i;

	for(i = 0; i < FONT_COUNT; ++i) {
		if(fonts[i] != NULL) {
			TTF_CloseFont(fonts[i]);
			fonts[i] = NULL;
		}
	}
}
