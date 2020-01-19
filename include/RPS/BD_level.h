#ifndef BD_LEVEL_H
#define BD_LEVEL_H

	typedef enum levelID {
		LEVEL_ZERO,
		LEVEL_ONE,
		LEVEL_TWO,
		LEVEL_THREE,
		LEVEL_FOUR,
		LEVEL_FIVE,
		LEVEL_SIX,
		LEVEL_SEVEN,
		LEVEL_EIGHT,
		LEVEL_NINE,
		LEVEL_COUNT
	}LevelID;

	typedef enum worldID {
		WORLD_ZERO,
		WORLD_ONE,
		WORLD_TWO,
		WORLD_THREE,
		WORLD_FOUR,
		WORLD_FIVE,
		WORLD_COUNT
	}WorldID;

	typedef struct water {
		double time;
		double last_time;
		double flow_time;
		double flow_time_extra;
	}Water;

	typedef struct gate {
		Point2D pos;
		bool is_player_there;
		bool is_open;
		int diamonds_to_open;
	}Gate;

	typedef struct level {
		bool is_passed;
		bool is_level_screen_open;
		bool is_unlocked[LEVEL_COUNT];
		WorldID worldID;
		int total_diamonds;
		bool stop_others;
		LevelID levelID;
		Water water;
		Gate gate;
		double time;
		int total_time;
		TimeState time_state;
		SDL_Color color_key;
		bool is_faded;

	}Level;

	void copy_string(char *src, char *des, int length);
	void handle_gate(Gate *const gate, TileMap **const map, SFX *sfx, const Uint8 vol);
	SDL_Color get_color_key(const WorldID worldID);
	WorldID get_world_id(const LevelID levelID);
	char* get_level_music(const MusicRythm rythm, const LevelID levelID);
	char* get_level_map(const LevelID levelID);
	char* get_level_tileset(const LevelID levelID);
	void get_gate(Level *const level);
	void get_level(Level *const level);
	void reset_level(Game *const game);
	void handle_level(Game *const game);
	void load_level(Game *const game);
	void init_level(Level *const level);
	
#endif