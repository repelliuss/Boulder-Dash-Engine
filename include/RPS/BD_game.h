#ifndef BD_GAME_H
#define BD_GAME_H

	enum scores {
		SCORE_DIAMOND = 5,
		SCORE_SPIDER = 10,
		SCORE_MONSTER = 20,
		SCORE_TIME = 1
	};

	typedef enum gameMode {
		GAME_MODE_EASY,
		GAME_MODE_NORMAL,
		GAME_MODE_HARD,
		GAME_MODE_IMPOSSIBLE
	}GameMode;

	typedef enum windowModes {
		WINDOW_MODE_WINDOWED,
		WINDOW_MODE_BORDERLESS,
		WINDOW_MODE_FULLSCREEN
	}WindowModes;

	typedef struct windowInfo {			
		int width;
		int height;
		WindowModes mode;
	}WindowInfo;

	typedef struct screen {
		SDL_Window *window;
		WindowInfo info_window;
		Camera camera;
	}Screen;

	typedef struct gameTime {
		double delta_time;
		struct timespec timer_start;
		struct timespec timer_stop;
	}GameTime;

	typedef struct map {
		TileMap **tile_map;
		TileMapInfo info_tile_map;
	}Map;

	typedef struct speed {
		double character;
		double solid;
		double foe;
	}Speed;

	typedef struct score {
		int point;
	}Score;

	typedef struct player {
		TileMap *object;
		Score score;
		Movement movement_player;
		Movement last_movement;
		int lives;
		int right_of_lives;
	}Player;

	typedef struct input {
		Keyboard keyboard;
		Key key;
	}Input;

	typedef struct fPS {
		bool lock;
		int per_second;
		bool show;
	}FPS;

	typedef struct windowSetting {
		bool should_change;
	}WindowSetting;

	typedef struct devMode {
		bool is_on;
		bool unlocked_save[LEVEL_COUNT];
		bool is_saved, is_loaded;
		int old_score;
	}DevMode;

	typedef struct settings {
		FPS fps;
		DevMode dev_mode;
		WindowSetting window;
	}Settings;

	typedef struct game
	{
		bool is_running;
		bool end;
		bool win;
		GameMode mode;
		Speed speed;
		Player player;
		Menu menu;
		Audio audio;
		Screen screen;
		GameTime time;
		Map map;
		Input input;
		Settings settings;
		Video video;
		Level level;
	}Game;

	void free_game(Game **game);
	void fix_delta_time(double *const delta_time);
	double get_delta_time(const struct timespec *const timer_start, const struct timespec *const timer_stop);
	double get_resultant_speed(const TileSet tile, const Game *const game);
	void handle_window_mode(Game *const game);
	void handle_dev_mode(Game *const game);
	void handle_fps(FPS *const fps, GameTime *const time);
	void handle_settings(Game *const game);
	void handle_game_mode(Game *const game);
	void init_input(Input *const input, struct timespec *timer_start);
	void init_game_time(GameTime *const time);
	void init_player(Player *const player);
	void init_speed(Speed *const speed);
	void init_settings(Settings *const settings);
	void init_game(Game **const game, SDL_Window *window, SDL_Renderer *renderer);
	int update_game(Game *const game);
	int load_game(SDL_Window *window, SDL_Renderer *renderer);

#endif