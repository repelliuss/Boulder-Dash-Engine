#ifndef BD_LEVELS_H
#define BD_LEVELS_H
	
	typedef enum tileSpecs {
		TILE_WIDTH = 64,
		TILE_HEIGHT = 64
	}TileSpecs;

	typedef enum tileSet {
		TILE_BACKGROUND = 18,
		TILE_BORDER = 0,
		TILE_CHARACTER = 9,
		TILE_DIRT = 7,
		TILE_CONVERTER = 15,
		TILE_STONE = 10,
		TILE_DIAMOND = 11,
		TILE_GATE = 14,
		TILE_WATER = 3,
		TILE_SPIDER = 58,
		TILE_MONSTER = 57,
		TILE_STAR = 13,
		TILE_LITTLE_DIAMOND = 12,
		TILE_COUNT = 12,
	}TileSet;

	enum tileSetOccupied {
		TILE_OCCUPIED_WATER_DIRT = 8,
		TILE_OCCUPIED_CHARACTER_DIAMOND_ZERO = 109,
		TILE_OCCUPIED_CHARACTER_DIAMOND_ONE = 119,
		TILE_OCCUPIED_CHARACTER_DIAMOND_TWO = 129,
		TILE_OCCUPIED_CHARACTER_DIAMOND_THREE = 139,
		TILE_OCCUPIED_COUNT
	};

	typedef enum animations {
		TANIM_NO_ACTION = -1
	}Animations;

	typedef struct tileMap {
		TileSet tile;
		bool is_movable;
		Movement movement;
		Anim anim;
		bool is_dead;
		bool destroy;
		DeathType death_type;
		SDL_Rect src_rect;
		SDL_Rect base_des_rect, des_rect, future_des_rect;
		DPoint2D HR_base_des_rect;
		SDL_Rect occupied_src_rect, occupied_base_des_rect, occupied_des_rect;
	}TileMap;

	typedef struct tileMapInfo {
		int width, height;
	}TileMapInfo;

	void free_map(TileMap ***map, const TileMapInfo *const info_map);
	bool check_if_dirt(TileMap *const tile, const SDL_Rect *const dirt_src_rect);
	void convert_tile(TileMap *const target, const TileSet tile);
	void optimize_tile(TileMap *const tile, const double delta_time, const Movement movement);
	void get_next_movement(TileMap *const tile, TileMap **const map, const TileMapInfo *const info_map, const SFX *const sfx, const Uint8 vol, const bool is_player_there);
	void add_velocity(TileMap *const tile, Game *const game);
	void reset_to_water(TileMap *water);
	void reset_to_background(TileMap *background);
	void find_src_rect(SDL_Rect *const src_rect, const TileSet tile);
	void do_move_water_helper(TileMap *const tile, Level *const level);
	void do_move_water(TileMap **const map, const Movement movement, const int x_pos, const int y_pos, Level *const level,
							const int x_move, const int y_move);
	void do_move_with_stone(Game *const game, const Movement movement,
								const int x_pos, const int y_pos, const int x_move, const int y_move);
	void do_move_normal(Game *const game, const Movement movement,
							const int x_pos, const int y_pos, const int x_move, const int y_move);
	void do_move_helper(Game *const game, const MoveType move_type, const Movement movement,
							const int x_pos, const int y_pos, const int x_move, const int y_move);
	void do_move(Game *const game, const MoveType move_type, const Movement movement, const int x_pos, const int y_pos);
	MoveType check_move_conditions(TileMap **const map, const TileMapInfo *const info_map, const TileSet tile,
									const int x_pos, const int y_pos, const int x_move, const int y_move);
	MoveType check_move(TileMap **const map, const TileMapInfo *const info_map, const TileSet tile, const Movement movement,
							const int x_pos, const int y_pos);
	void update_character(StackMovables *root, Game *const game);
	void update_monsters(StackMovables *root, Game *const game);
	void update_spiders(StackMovables *root, Game *const game);
	void update_converter(StackMovables *root, Game *const game);
	void update_solids(StackMovables *root, Game *const game);
	void update_static_water(StackMovables *root, Game *const game);
	void update_water(StackMovables *root, TileMap **const map, Level *const level, const Uint64 *const timer_start);
	void update_map(Game *const game);
	TileMap** load_map(TileMapInfo *const info_map, const LevelID levelID, int *const total_diamonds);

#endif
