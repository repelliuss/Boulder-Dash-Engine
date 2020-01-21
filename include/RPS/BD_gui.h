#ifndef BD_GUI_H
#define BD_GUI_H

	typedef struct windowInfo WindowInfo;
	typedef struct game Game;
	typedef struct permTextures PermTextures;
	typedef struct level Level;
	typedef struct settings Settings;
	typedef enum windowModes WindowModes;

	typedef enum guiStartGame {
		GUI_START_NEW_GAME,
		GUI_START_LOAD_SAVE,
		GUI_START_COUNT,
		GUI_START_NOTHING
	}GuiStartGame;

	typedef enum guiSettings {
		GUI_SETTINGS_FPS_LOCK,
		GUI_SETTINGS_SHOW_FPS,
		GUI_SETTINGS_WINDOW_MODE,
		GUI_SETTINGS_VOLUME,
		GUI_SETTINGS_CAMERA_SPEED,
		GUI_SETTINGS_COUNT,
		GUI_SETTINGS_NOTHING
	}GuiSettings;

	typedef enum guiVolume {
		GUI_VOLUME_MUTE,
		GUI_VOLUME_MUSIC,
		GUI_VOLUME_SFX,
		GUI_VOLUME_UNMUTE,
		GUI_VOLUME_COUNT,
		GUI_VOLUME_NOTHING
	}GuiVolume;

	enum fonts {
		FONT_MENU,
		FONT_FPS,
		FONT_COUNT,
		FONT_SIZE = 72,
		FONT_SIZE_FPS = 72
	};

	enum sizes {
		SIZE_TIME = 3,
		SIZE_SCORE = 4
	};

	enum rectsHud {
		RECT_TEXT_TIME,
		RECT_TEXT_SCORE,
		RECT_TEXT_DIAMOND,
		RECT_LAYER_TIME,
		RECT_LAYER_SCORE,
		RECT_LAYER_DIAMOND,
		RECT_HUD_COUNT,
		RECT_TEXT_COUNT = 3,
		RECT_LAYER_COUNT = 3
	};

	typedef struct menu {
		double pause_time;
	}Menu;

	typedef struct hud {
		TTF_Font *fonts[FONT_COUNT];
		SDL_Rect rects[RECT_HUD_COUNT];
	}Hud;

	void free_fonts(TTF_Font **fonts);
	void free_fonts_wsize(TTF_Font **fonts, const int size);
	SDL_Texture* get_text(SDL_Renderer *renderer, TTF_Font *font, char *text, SDL_Color *color);
	void update_volume_settings(Game *const game, const Key key, const int layer_place);
	void change_to_old_values_volume(Game *const game, const int layer_place, const bool old_situation, const int old_value);
	void set_old_values_volume(Game *const game, const int layer_place, bool *old_situation, int *old_value);
	void set_volume_settings_arrows(SDL_Rect *const des_left, SDL_Rect *const des_right, const int layer_place, SDL_Rect *const rects);
	void set_volume_settings_layer(SDL_Rect *const des, const int layer_place, SDL_Rect *const rects);
	void open_volume_settings(Game *const game);
	void update_settings(Game *const game, const Key key, const int layer_place);
	void change_to_old_values(Game *const game, const int layer_place, const bool old_situation, const int old_value, const WindowModes old_mode);
	void set_old_values(Game *const game, const int layer_place, bool *old_situation, int *old_value, WindowModes *old_mode);
	void set_settings_arrows(SDL_Rect *const des_left, SDL_Rect *const des_right, const int layer_place, SDL_Rect *const rects);
	void set_settings_layer(SDL_Rect *const des, const int layer_place, SDL_Rect *const rects);
	void open_settings(Game *const game);
	void set_menu_layer(SDL_Rect *const des, const int layer_place, SDL_Rect *const rects);
	void open_menu(Game *const game);
	double handle_menu(Game *const game);
	void set_are_you_sure_layer(SDL_Rect *const des, const int layer_place, SDL_Rect *const rects);
	bool open_are_you_sure(Game *const game, SDL_Texture *texture_warning, SDL_Rect *des_warning, const bool show_asu);
	void update_perm_rects(SDL_Rect *perm_rects, const WindowInfo *const info_window);
	void update_hud_rects(SDL_Rect *hud_rects, const WindowInfo *const info_window);
	void get_rects_perm(SDL_Rect *rects, const WindowInfo *const info_window);
	void get_rects_hud(SDL_Rect *rects, const WindowInfo *const info_window);
	void update_level_screen_ids(SDL_Renderer *renderer, const int place_character_level, SDL_Texture **text_level_id, SDL_Texture **text_world_id,
									TTF_Font *font, int *const level_id_digit, int *const world_id_digit);
	bool open_level_screen(Game *const game);
	void set_game_mode_layer(SDL_Rect *const des, const int layer_place, SDL_Rect *const rects);
	bool open_game_mode_screen(Game *const game);
	void set_start_game_layer(SDL_Rect *const des, const int layer_place, SDL_Rect *const rects);
	bool open_new_game_screen(Game *const game);
	bool open_start_screen(Game *const game);
	void init_fonts(TTF_Font **fonts);
	void init_hud(Hud *const hud, const WindowInfo *const info_window);

#endif
