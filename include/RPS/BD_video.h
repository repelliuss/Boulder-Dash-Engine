#ifndef BD_VIDEO_H
#define BD_VIDEO_H

	typedef struct game Game;
	typedef struct tileMap TileMap;
	typedef struct tileMapInfo TileMapInfo;
	typedef struct camera Camera;
	typedef struct level Level;
	typedef struct player Player;
	typedef struct gate Gate;
	typedef struct map Map;
	typedef struct screen Screen;

	enum videoInfos {
		WINDOW_WIDTH = 1920,			/*default window sizes*/
		WINDOW_HEIGHT = 1080
	};

	enum textureMap {
		TEXTURE_MAP_TILESET,
		TEXTURE_MAP_COUNT
	};

	enum textureHud {
		TEXTURE_TEXT_TIME,
		TEXTURE_TEXT_SCORE,
		TEXTURE_TEXT_DIAMOND,
		TEXTURE_HUD_COUNT,
		TEXTURE_TEXT_COUNT = 3,
	};

	enum texturePerm {
		TEXTURE_PERM_PAUSE,
		TEXTURE_PERM_START_SCREEN,
		TEXTURE_PERM_START,
		TEXTURE_PERM_QUIT,
		TEXTURE_PERM_MISC,
		TEXTURE_PERM_GO,
		TEXTURE_PERM_WORLD,
		TEXTURE_PERM_LEVEL,
		TEXTURE_PERM_LEVEL_SELECT,
		TEXTURE_PERM_CHAR_X,
		TEXTURE_PERM_PLAYER_LIVE,
		TEXTURE_PERM_WIN,
		TEXTURE_PERM_LOSE,
		TEXTURE_PERM_SETTINGS,
		TEXTURE_PERM_RESTART,
		TEXTURE_PERM_LEVEL_SCREEN,
		TEXTURE_PERM_SAVE_GAME,
		TEXTURE_PERM_LOAD_SAVE,
		TEXTURE_PERM_QUIT_GAME,
		TEXTURE_PERM_FPS_LOCK,
		TEXTURE_PERM_SHOW_FPS,
		TEXTURE_PERM_WINDOW_MODE,
		TEXTURE_PERM_VOLUME,
		TEXTURE_PERM_DEV_MODE,
		TEXTURE_PERM_CAMERA_SPEED,
		TEXTURE_PERM_ON,
		TEXTURE_PERM_OFF,
		TEXTURE_PERM_240,
		TEXTURE_PERM_160,
		TEXTURE_PERM_144,
		TEXTURE_PERM_120,
		TEXTURE_PERM_75,
		TEXTURE_PERM_60,
		TEXTURE_PERM_30,
		TEXTURE_PERM_FULLSCREEN,
		TEXTURE_PERM_BORDERLESS,
		TEXTURE_PERM_WINDOWED,
		TEXTURE_PERM_FPS,
		TEXTURE_PERM_100,
		TEXTURE_PERM_90,
		TEXTURE_PERM_80,
		TEXTURE_PERM_70,
		TEXTURE_PERM_50,
		TEXTURE_PERM_40,
		TEXTURE_PERM_20,
		TEXTURE_PERM_10,
		TEXTURE_PERM_0,
		TEXTURE_PERM_MUTE,
		TEXTURE_PERM_MUSIC_VOLUME,
		TEXTURE_PERM_SFX_VOLUME,
		TEXTURE_PERM_YES,
		TEXTURE_PERM_NO,
		TEXTURE_PERM_ASU,
		TEXTURE_PERM_OVERWRITE,
		TEXTURE_PERM_PROGRESS,
		TEXTURE_PERM_FAIL_SAVE,
		TEXTURE_PERM_FAIL_LOAD,
		TEXTURE_PERM_GAME_RESTART,
		TEXTURE_PERM_NEW_GAME,
		TEXTURE_PERM_EASY,
		TEXTURE_PERM_NORMAL,
		TEXTURE_PERM_HARD,
		TEXTURE_PERM_IMPOSSIBLE,
		TEXTURE_PERM_CANT_SAVE,
		TEXTURE_PERM_COUNT
	};

	enum rectsPerm {
		RECT_PERM_PAUSE,
		RECT_PERM_START,
		RECT_PERM_QUIT,
		RECT_PERM_SRC_CHARACTER,
		RECT_PERM_SRC_GREEN_SQUARE,
		RECT_PERM_SRC_GREEN_RECTANGLE,
		RECT_PERM_SRC_RED_SQUARE,
		RECT_PERM_SRC_RED_RECTANGLE,
		RECT_PERM_DES_SQUARE,
		RECT_PERM_DES_RECTANGLE,
		RECT_PERM_DES_CHARACTER,
		RECT_PERM_DES_WORLD,
		RECT_PERM_DES_WORLD_ID,
		RECT_PERM_DES_LEVEL,
		RECT_PERM_DES_LEVEL_ID,
		RECT_PERM_DES_GO,
		RECT_PERM_LEVEL_SELECT,
		RECT_PERM_DES_PAUSE_CHARACTER,
		RECT_PERM_DES_CHAR_X,
		RECT_PERM_DES_PLAYER_LIVE,
		RECT_PERM_DES_WIN,
		RECT_PERM_DES_LOSE,
		RECT_PERM_DES_SETTINGS,
		RECT_PERM_DES_LEVEL_SCREEN,
		RECT_PERM_DES_RESTART,
		RECT_PERM_DES_SAVE_GAME,
		RECT_PERM_DES_LOAD_SAVE,
		RECT_PERM_DES_QUIT_GAME,
		RECT_PERM_SRC_SELECT_LAYER,
		RECT_PERM_DES_FPS_LOCK,
		RECT_PERM_DES_SHOW_FPS,
		RECT_PERM_DES_WINDOW_MODE,
		RECT_PERM_DES_VOLUME,
		RECT_PERM_DES_DEV_MODE,
		RECT_PERM_DES_FPS_LOCK_VAL,
		RECT_PERM_DES_SHOW_FPS_VAL,
		RECT_PERM_DES_WINDOW_MODE_VAL,
		RECT_PERM_DES_VOLUME_VAL,
		RECT_PERM_DES_DEV_MODE_VAL,
		RECT_PERM_SRC_ARROW_LEFT,
		RECT_PERM_SRC_ARROW_RIGHT,
		RECT_PERM_DES_FPS,
		RECT_PERM_DES_CAMERA_SPEED,
		RECT_PERM_DES_CAMERA_SPEED_VAL,
		RECT_PERM_DES_MUTE,
		RECT_PERM_DES_MUTE_VAL,
		RECT_PERM_DES_MUSIC_VOLUME,
		RECT_PERM_DES_MUSIC_VOLUME_VAL,
		RECT_PERM_DES_SFX_VOLUME,
		RECT_PERM_DES_SFX_VOLUME_VAL,
		RECT_PERM_DES_YES,
		RECT_PERM_DES_NO,
		RECT_PERM_DES_ASU,
		RECT_PERM_DES_OVERWRITE,
		RECT_PERM_DES_PROGRESS,
		RECT_PERM_DES_FAIL_SAVE,
		RECT_PERM_DES_FAIL_LOAD,
		RECT_PERM_DES_GAME_RESTART,
		RECT_PERM_DES_NEW_GAME,
		RECT_PERM_DES_NEW_LOAD_SAVE,
		RECT_PERM_DES_EASY,
		RECT_PERM_DES_NORMAL,
		RECT_PERM_DES_HARD,
		RECT_PERM_DES_IMPOSSIBLE,
		RECT_PERM_DES_CANT_SAVE,
		RECT_PERM_COUNT
	};

	enum fadeTime {
		DEFAULT_FADE_TIME = 1
	};

	typedef enum fadeState {
		FADE_STATE_NO_FADE,
		FADE_STATE_FADING_IN,
		FADE_STATE_FADING_OUT,
		FADE_STATE_COUNT
	}FadeState;

	typedef struct point2D {
		int x, y;
	}Point2D;

	typedef struct dPoint2D {
		double x, y;
	}DPoint2D;

	typedef struct permTextures {
		SDL_Texture *textures[TEXTURE_PERM_COUNT];
		SDL_Rect rects[RECT_PERM_COUNT];
	}PermTextures;

	typedef struct texture {
		SDL_Texture *map[TEXTURE_MAP_COUNT];	/*main textures for maps*/
		SDL_Texture *hud[TEXTURE_HUD_COUNT];
	}Texture;

	typedef struct fade {
		double time;
		double last_time;
		double fade_time;
		Uint8 alpha;
		FadeState state;
		bool full_cycle;
		struct timespec *timer_start;
	}Fade;

	typedef struct effects {
		Fade fade;
	}Effects;

	typedef struct video {
		SDL_Renderer *renderer;				
		Texture textures;
		Hud hud;
		PermTextures perm_textures;
		Effects effects;
	}Video;
	
	void free_textures(SDL_Texture **textures, const int size);
	void show_text_timed_screen(Game *const game, SDL_Texture *texture, SDL_Rect *rect, const double time);
	void handle_fade_timer(Fade *const fade, const double delta_time);
	void render_fps(Game *const game);
	void render_hud(SDL_Renderer *renderer, Texture *textures, SDL_Rect *rects_hud);
	void render_movables(StackMovables *root, SDL_Renderer *renderer, SDL_Texture *texture, TileMap **const map);
	void render_statics(SDL_Renderer *renderer, SDL_Texture *texture, TileMap **const map, const TileMapInfo *const info_map,
							const Camera *const camera, StackMovables *root[STACK_COUNT]);
	void render_background(SDL_Renderer *renderer, SDL_Texture *texture, TileMap **const map, 
						const TileMapInfo *const info_map, const WindowInfo *const info_window);
	void render_map(Video *const video, Map *const map, Screen *const screen);
	void set_effect_fade_in(Fade *const fade);
	void set_effect_fade_out(Fade *const fade);
	void handle_fade_helper(const Uint8 alpha, SDL_Texture **textures, const int count);
	void handle_fade(Fade *const fade, SDL_Texture **textures, const int count);
	void render_game(Game *const game);
	void render_player_live(Game *const game);
	void render_volume_settings_val(Game *const game);
	void render_settings_val(Game *const game);
	SDL_Surface* get_surface(char *f_location);
	SDL_Texture* get_tileset(SDL_Renderer *renderer, const Level *const level);
	SDL_Texture* get_texture(SDL_Renderer *renderer, SDL_Surface *surface);
	void load_textures_perm(SDL_Texture **textures, SDL_Renderer *renderer, TTF_Font **fonts);
	void load_textures_hud_diamond(SDL_Texture **texture, SDL_Renderer *renderer, TTF_Font *font, const Gate *const gate);
	void load_textures_hud_score(SDL_Texture **texture, SDL_Renderer *renderer, TTF_Font *font, const Player *const player);
	void load_textures_hud_time(SDL_Texture **texture, SDL_Renderer *renderer, TTF_Font *font, const Level *const level);
	void load_textures_hud_fonts(Game *const game);
	void load_textures_map(SDL_Texture **textures_map, SDL_Renderer *renderer, const Level *const level);
	void load_textures(Game *const game);
	void init_fade(Fade *const fade, struct timespec *timer_start);
	void init_textures(SDL_Texture **textures, const int size);
	void get_window_size(SDL_Window *const window, WindowInfo *const info_window);
	SDL_Renderer* build_renderer(SDL_Window *window);
	SDL_Window* build_window(void);

#endif