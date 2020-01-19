#ifndef BD_EVENTS_H
#define BD_EVENTS_H

	typedef enum movement {
		MOVE_WAIT,
		MOVE_UP,
		MOVE_RIGHT,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_UP_RIGHT,
		MOVE_UP_LEFT,
		MOVE_DOWN_RIGHT,
		MOVE_DOWN_LEFT
	}Movement;

	typedef enum moveType {
		MTYPE_NO_MOVE,
		MTYPE_NORMAL,
		MTYPE_WITH_STONE,
		MTYPE_WATER,
		MTYPE_KILL,
		MTYPE_SCORE_DIAMOND,
		MTYPE_GATE,
		MTYPE_DIRT
	}MoveType;

	typedef enum deathType {
		DTYPE_SOLID,
		DTYPE_FOE,
		DTYPE_WATER,
		DTYPE_JAMMING,
		DTYPE_TIME
	}DeathType;

	typedef enum tileSet TileSet;

	void kill(TileMap *const tile, const DeathType death_type);
	bool check_death_character_helper(Game *const game, const int x_pos, const int y_pos);
	void check_death_character(TileMap **const map, const TileMapInfo *const info_map, const int x_pos, const int y_pos, Game *const game);
	bool check_kill_foe(TileMap **const map, const TileMapInfo *const info_map, const int x_pos, const int y_pos);
	void check_kill_solid(TileMap **const map, const TileMapInfo *const info_map, const int x_pos, const int y_pos, const Movement movement,
							const SFX *const sfx, const Uint8 vol);
	Movement manhattan_helper_y(const Point2D *const manhattan, const Point2D *const src, const bool try_again,
									TileMap **const map, const TileMapInfo *const info_map, const TileSet tile);
	Movement manhattan_helper_x(const Point2D *const manhattan, const Point2D *const src, const bool try_again,
									TileMap **const map, const TileMapInfo *const info_map, const TileSet tile);
	Movement find_manhattan_movement(const Point2D *const src, const Point2D *const des,
										TileMap **const map, const TileMapInfo *const info_map, const TileSet tile);
	void handle_menu_events(Game *const game, const int layer_place, bool *quit_loop);
	Movement find_camera_movement(const Point2D *const base, const Point2D *const future);
	void handle_player_movement(Movement *const movement_player);
	void handle_keyboard(Keyboard *const keyboard);
	void do_events_gui(Game *const game);
	void do_events(Game *const game);

#endif