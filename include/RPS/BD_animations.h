#ifndef BD_ANIMATIONS_H
#define BD_ANIMATIONS_H

	enum anim_char_move {
		ANIM_CHAR_MOVE_WAIT = 9,
		ANIM_CHAR_MOVE_WAIT_TOTAL_FRAME = 10,
		ANIM_CHAR_MOVE_UP = 50,
		ANIM_CHAR_MOVE_UP_TOTAL_FRAME = 6,
		ANIM_CHAR_MOVE_RIGHT = 51,
		ANIM_CHAR_MOVE_RIGHT_TOTAL_FRAME = 4,
		ANIM_CHAR_MOVE_DOWN = 52,
		ANIM_CHAR_MOVE_DOWN_TOTAL_FRAME = 6,
		ANIM_CHAR_MOVE_LEFT = 53,
		ANIM_CHAR_MOVE_LEFT_TOTAL_FRAME = 4
	};

	enum anim_char_death {
		ANIM_CHAR_DEATH_FOE = 54,
		ANIM_CHAR_DEATH_FOE_TOTAL_FRAME = 6,
		ANIM_CHAR_DEATH_SOLID = 55,
		ANIM_CHAR_DEATH_SOLID_TOTAL_FRAME = 6,
		ANIM_CHAR_DEATH_JAMMING = 76,
		ANIM_CHAR_DEATH_JAMMING_TOTAL_FRAME = 6,
	};

	enum anim_char_win {
		ANIM_CHAR_WIN_GATE = 16,
		ANIM_CHAR_WIN_GATE_TOTAL_FRAME = 6
	};

	enum anim_stone_move {
		ANIM_STONE_MOVE_WAIT = 10,
		ANIM_STONE_MOVE_WAIT_TOTAL_FRAME = 4
	};

	enum anim_diamond_move {
		ANIM_DIAMOND_MOVE_WAIT = 11,
		ANIM_DIAMOND_MOVE_WAIT_TOTAL_FRAME = 4
	};

	enum anim_converter_move {
		ANIM_CONVERTER_MOVE_WAIT = 15,
		ANIM_CONVERTER_MOVE_WAIT_TOTAL_FRAME = 4 
	};

	enum anim_spider_move {
		ANIM_SPIDER_MOVE_WAIT = 58,
		ANIM_SPIDER_MOVE_WAIT_TOTAL_FRAME = 7
	};

	enum anim_monster_move {
		ANIM_MONSTER_MOVE_WAIT = 57,
		ANIM_MONSTER_MOVE_WAIT_TOTAL_FRAME = 8
	};

	enum anim_little_diamond_move {
		ANIM_LITTLE_DIAMOND_MOVE_WAIT = 12,
		ANIM_LITTLE_DIAMOND_MOVE_WAIT_TOTAL_FRAME = 4
	};

	enum anim_star_move {
		ANIM_STAR_MOVE_WAIT = 13,
		ANIM_STAR_MOVE_WAIT_TOTAL_FRAME = 4
	};

	enum anim_gate_move {
		ANIM_GATE_MOVE_WAIT = 14,
		ANIM_GATE_MOVE_WAIT_TOTAL_FRAME = 4
	};

	enum anim_background_move {
		ANIM_BACKGROUND_MOVE_WAIT = 18,
		ANIM_BACKGROUND_MOVE_WAIT_TOTAL_FRAME = 4
	};

	enum anim_dirt_move {
		ANIM_DIRT_MOVE_WAIT = 7,
		ANIM_DIRT_MOVE_WAIT_TOTAL_FRAME = 4
	};

	typedef struct anim {
		int frame;
		double frame_time;
	}Anim;

	void free_anim_stack(StackMovables **root);
	void go_next_frame(int *const frame, double *const frame_time,
						const int total_frame, const double next_frame_time, const Uint64 *const timer_start);
	void find_frame(SDL_Rect *const src_rect, const int frame, const int first_frame);
	void late_update_background(StackMovables *root, TileMap **const map, const Uint64 *const timer_start);
	void late_update_dirt(StackMovables *root, TileMap **const map, const Uint64 *const timer_start);
	void late_update_gate(StackMovables *root, TileMap **const map, const Uint64 *const timer_start);
	void late_update_stars(StackMovables *root, TileMap **const map, const Uint64 *const timer_start);
	void late_update_little_diamonds(StackMovables *root, TileMap **const map, const Uint64 *const timer_start);
	void late_update_monsters(StackMovables *root, TileMap **const map, const TileMapInfo *const info_map,
								const SFX *const sfx, const Uint8 vol, Player *const player, const Uint64 *const timer_start);
	void late_update_spiders(StackMovables *root, TileMap **const map, const TileMapInfo *const info_map,
								const SFX *const sfx, const Uint8 vol, Player *const player, const Uint64 *const timer_start);
	void late_update_converter(StackMovables *root, TileMap **const map, const Uint64 *const timer_start);
	void late_update_diamonds(StackMovables *root, TileMap **const map, const Uint64 *const timer_start);
	void late_update_stones(StackMovables *root, TileMap **const map, const Uint64 *const timer_start);
	void late_update_character(StackMovables *root, Game *const game);
	void late_update_map(Game *const game);
	void reset_frame(Anim *const anim);
	void handle_anim(Anim *const anim, const TileSet tile);

#endif
