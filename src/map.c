#include <RPS/BD.h>

TileMap** load_map(TileMapInfo *const info_map, const LevelID levelID, int *const total_diamonds) {

	FILE *f_map = NULL;
	TileMap **map = NULL;
	int tile_id;
	int y_pos, x_pos;
	char *f_location = NULL;

	f_location = get_level_map(levelID);

	f_map = fopen(f_location, "r");

	if(!f_map) {/* temizlemeye yönlendir*/
		perror("Level's map file couldn't open.\n");
		return NULL;
	}

	fscanf(f_map, "%d", &(info_map->width));
	fscanf(f_map, "%d", &(info_map->height));

	map = (TileMap**)malloc(info_map->height * sizeof(TileMap*));
	if(!map) {
		perror("Memory allocation error for map. (1)\n");
		return NULL;
	}
	else {
		memset(map, 0, info_map->height * sizeof(TileMap*));
	}
	for(y_pos = 0; y_pos < info_map->height; ++y_pos) {
		map[y_pos] = (TileMap*)malloc(info_map->width * sizeof(TileMap));
		if(!map[y_pos]) {
			perror("Memory allocation error for map. (2)\n");
			info_map->height = y_pos - 1;										/*frees allocated place until here on error*/
			free_map(&map, info_map);
			return NULL;
		}
		else {
			memset(map[y_pos], 0, info_map->width * sizeof(TileMap));
		}
	}

	for(y_pos = 0; y_pos < info_map->height; ++y_pos) {
		fseek(f_map, sizeof(char), SEEK_CUR);
		for(x_pos = 0; x_pos < info_map->width; ++x_pos) {
			fscanf(f_map, "%d", &tile_id);

			map[y_pos][x_pos].tile = tile_id;
			find_src_rect(&map[y_pos][x_pos].src_rect, tile_id);
			map[y_pos][x_pos].base_des_rect.x = x_pos * TILE_WIDTH;
			map[y_pos][x_pos].base_des_rect.y = y_pos * TILE_HEIGHT;
			map[y_pos][x_pos].HR_base_des_rect.x = (double)map[y_pos][x_pos].base_des_rect.x;
			map[y_pos][x_pos].HR_base_des_rect.y = (double)map[y_pos][x_pos].base_des_rect.y;
			map[y_pos][x_pos].src_rect.w = map[y_pos][x_pos].base_des_rect.w = map[y_pos][x_pos].des_rect.w = TILE_WIDTH;
			map[y_pos][x_pos].src_rect.h = map[y_pos][x_pos].base_des_rect.h = map[y_pos][x_pos].des_rect.h = TILE_HEIGHT;
			map[y_pos][x_pos].occupied_des_rect.w = TILE_WIDTH;
			map[y_pos][x_pos].occupied_des_rect.h = TILE_HEIGHT;
			map[y_pos][x_pos].movement = MOVE_WAIT;
			map[y_pos][x_pos].is_movable = TRUE;
			map[y_pos][x_pos].is_dead = FALSE;
			map[y_pos][x_pos].destroy = FALSE;
			map[y_pos][x_pos].anim.frame = 0;
			map[y_pos][x_pos].anim.frame_time = 0.0;

			if(tile_id == TILE_DIAMOND) {
				++(*total_diamonds);
			}

			fseek(f_map, sizeof(char), SEEK_CUR);
		}
	}

	fclose(f_map);
	free(f_location);

	return map;
}

void update_map(Game *const game) {

	int x_pos, y_pos;
	StackMovables *root[STACK_COUNT];

	init_stack_array(root, STACK_COUNT);

	for(y_pos = 0; y_pos < game->map.info_tile_map.height; ++y_pos) {
		for(x_pos = 0; x_pos < game->map.info_tile_map.width; ++x_pos) {

			/*if tile is open to update*/
			if(game->map.tile_map[y_pos][x_pos].is_movable == TRUE) {
				/*if a game event like player dead, level win didn't happen*/
				if(game->level.stop_others == FALSE) {
					/*if this tile is alive*/
					if(game->map.tile_map[y_pos][x_pos].is_dead == FALSE) {
						/*if game is not at the very first frame*/
						if(game->time.delta_time > 0.0) {
							switch(game->map.tile_map[y_pos][x_pos].tile) {
								case TILE_CHARACTER:
									/*is character jammed?*/
									check_death_character(game->map.tile_map, &(game->map.info_tile_map), x_pos, y_pos, game);
									push_movables(&root[STACK_CHARACTER], x_pos, y_pos);
									break;
								case TILE_STONE:
									push_movables(&root[STACK_STONES], x_pos, y_pos);
									break;
								case TILE_DIAMOND:
									push_movables(&root[STACK_DIAMONDS], x_pos, y_pos);
									break;
								case TILE_SPIDER:
									/*is player at 4 adjacent tiles?*/
									if(check_kill_foe(game->map.tile_map, &(game->map.info_tile_map), x_pos, y_pos) == FALSE) {
										push_movables(&root[STACK_SPIDERS], x_pos, y_pos);
									}
									break;
								case TILE_MONSTER:
									if(check_kill_foe(game->map.tile_map, &(game->map.info_tile_map), x_pos, y_pos) == FALSE) {
										push_movables(&root[STACK_MONSTERS], x_pos, y_pos);
									}
									break;
								case TILE_WATER:
									push_movables(&root[STACK_STATIC_WATER], x_pos, y_pos);
									break;
								case TILE_CONVERTER:
									push_movables(&root[STACK_CONVERTER], x_pos, y_pos);
									break;
								default:
									break;
							}
						}
					}
				}
				/*if player dead and its death cause is water, continue moving water. This is a game effect*/
				else if(game->player.object->death_type == DTYPE_WATER && game->map.tile_map[y_pos][x_pos].tile == TILE_WATER) {
					push_movables(&root[STACK_STATIC_WATER], x_pos, y_pos);
				}
			}
			/*if player is dead only move player and never add velocity to water(water movement works with time)*/
			else if((game->level.stop_others == TRUE && game->map.tile_map[y_pos][x_pos].tile == TILE_CHARACTER) ||
						(game->map.tile_map[y_pos][x_pos].tile != TILE_WATER)) {
				
				add_velocity(&(game->map.tile_map[y_pos][x_pos]), game);
			}
			/*if the tile is water and game is still going on or player is dead by jamming with water is a cause of it*/
			else if(game->level.stop_others == FALSE ||
						(game->level.stop_others == TRUE && game->player.object->death_type == DTYPE_WATER)) {

				push_movables(&root[STACK_WATER], x_pos, y_pos);
			}
		}
	}

	update_static_water(root[STACK_STATIC_WATER], game);
	update_water(root[STACK_WATER], game->map.tile_map, &(game->level), &(game->time.timer_start));
	update_spiders(root[STACK_SPIDERS], game);
	update_monsters(root[STACK_MONSTERS], game);
	update_solids(root[STACK_STONES], game);
	update_solids(root[STACK_DIAMONDS], game);
	update_converter(root[STACK_CONVERTER], game);
	update_character(root[STACK_CHARACTER], game);

	if(game->player.object->is_dead == TRUE) {
		game->level.stop_others = TRUE;
	}
}

void update_static_water(StackMovables *root, Game *const game) {

	MoveType move_type = MTYPE_NO_MOVE;

	game->level.water.last_time = get_last_time(root, &(game->time.timer_start));
	game->level.water.time += game->level.water.last_time;

	while(root != NULL) {
		move_type = check_move_conditions(game->map.tile_map, &(game->map.info_tile_map), TILE_WATER, root->x_pos, root->y_pos, 0, 1);
		if(move_type != MTYPE_NO_MOVE) {
			do_move_water(game->map.tile_map, MOVE_DOWN, root->x_pos, root->y_pos, &(game->level), 0, 1);
		}

		move_type = check_move_conditions(game->map.tile_map, &(game->map.info_tile_map), TILE_WATER, root->x_pos, root->y_pos, 1, 0);
		if(move_type != MTYPE_NO_MOVE) {
			do_move_water(game->map.tile_map, MOVE_RIGHT, root->x_pos, root->y_pos, &(game->level), 1, 0);
		}

		move_type = check_move_conditions(game->map.tile_map, &(game->map.info_tile_map), TILE_WATER, root->x_pos, root->y_pos, -1, 0);
		if(move_type != MTYPE_NO_MOVE) {
			do_move_water(game->map.tile_map, MOVE_LEFT, root->x_pos, root->y_pos, &(game->level), -1, 0);
		}

		move_type = check_move_conditions(game->map.tile_map, &(game->map.info_tile_map), TILE_WATER, root->x_pos, root->y_pos, 0, -1);
		if(move_type != MTYPE_NO_MOVE) {
			do_move_water(game->map.tile_map, MOVE_UP, root->x_pos, root->y_pos, &(game->level), 0, -1);
		}
		pop_movables(&root);
	}
}

void update_water(StackMovables *root, TileMap **const map, Level *const level, const struct timespec *const timer_start) {
	
	level->water.time -= level->water.last_time;
	level->water.last_time = get_last_time(root, timer_start);
	level->water.time += level->water.last_time;

	while(root != NULL) {
		do_move_water_helper(&map[root->y_pos][root->x_pos], level);
		pop_movables(&root);
	}
}

void update_solids(StackMovables *root, Game *const game) {

	MoveType move_type = MTYPE_NO_MOVE;
	MoveType move_type_condition = MTYPE_NO_MOVE;

	while(root != NULL) {
		move_type = check_move_conditions(game->map.tile_map, &(game->map.info_tile_map), TILE_STONE, root->x_pos, root->y_pos, 0, 1);
		if(move_type == MTYPE_NORMAL) {
			if(game->map.tile_map[root->y_pos][root->x_pos].tile == TILE_STONE) {
				if(Mix_Playing(game->audio.sfx[AUDIO_SFX_STONE_FALL].channel) == 0) {
					play_chunk_timed(game->audio.sfx[AUDIO_SFX_STONE_FALL].chunk, game->audio.sfx[AUDIO_SFX_STONE_FALL].channel, 0, 750);
					set_chunk_volume(game->audio.sfx[AUDIO_SFX_STONE_FALL].chunk, game->audio.vol_sfx);
				}
			}
			do_move(game, move_type, MOVE_DOWN, root->x_pos, root->y_pos);
		}
		else if(move_type == MTYPE_KILL) {
			play_chunk(game->audio.sfx[AUDIO_SFX_FOE_KILL].chunk, game->audio.sfx[AUDIO_SFX_FOE_KILL].channel, 0);
			set_chunk_volume(game->audio.sfx[AUDIO_SFX_FOE_KILL].chunk, game->audio.vol_sfx);
			kill(&(game->map.tile_map[root->y_pos + 1][root->x_pos]), DTYPE_SOLID);
			do_move(game, move_type, MOVE_DOWN, root->x_pos, root->y_pos);
		}
		else if(root->y_pos + 1 < game->map.info_tile_map.height) {

			if(game->map.tile_map[root->y_pos + 1][root->x_pos].tile == TILE_STONE ||
				game->map.tile_map[root->y_pos + 1][root->x_pos].tile == TILE_DIAMOND ||
				game->map.tile_map[root->y_pos + 1][root->x_pos].tile == TILE_BORDER) {

				move_type = check_move_conditions(game->map.tile_map, &(game->map.info_tile_map), TILE_STONE, root->x_pos, root->y_pos, -1, 0);
				move_type_condition = check_move_conditions(game->map.tile_map, &(game->map.info_tile_map), TILE_STONE, root->x_pos, root->y_pos, -1, 1);
				if(move_type == MTYPE_NORMAL && move_type == move_type_condition) {
					do_move(game, move_type, MOVE_LEFT, root->x_pos, root->y_pos);
				}
				else if(move_type == MTYPE_NORMAL && move_type_condition == MTYPE_KILL) {
					play_chunk(game->audio.sfx[AUDIO_SFX_FOE_KILL].chunk, game->audio.sfx[AUDIO_SFX_FOE_KILL].channel, 0);
					set_chunk_volume(game->audio.sfx[AUDIO_SFX_FOE_KILL].chunk, game->audio.vol_sfx);
					kill(&game->map.tile_map[root->y_pos + 1][root->x_pos - 1], DTYPE_SOLID);
					do_move(game, move_type, MOVE_LEFT, root->x_pos, root->y_pos);
				}
				else {
					move_type = check_move_conditions(game->map.tile_map, &(game->map.info_tile_map), TILE_STONE, root->x_pos, root->y_pos, 1, 0);
					move_type_condition = check_move_conditions(game->map.tile_map, &(game->map.info_tile_map), TILE_STONE, root->x_pos, root->y_pos, 1, 1);
					if(move_type == MTYPE_NORMAL && move_type == move_type_condition) {
						do_move(game, move_type, MOVE_RIGHT, root->x_pos, root->y_pos);
					}
					else if(move_type == MTYPE_NORMAL && move_type_condition == MTYPE_KILL) {
						play_chunk(game->audio.sfx[AUDIO_SFX_FOE_KILL].chunk, game->audio.sfx[AUDIO_SFX_FOE_KILL].channel, 0);
						set_chunk_volume(game->audio.sfx[AUDIO_SFX_FOE_KILL].chunk, game->audio.vol_sfx);
						kill(&game->map.tile_map[root->y_pos + 1][root->x_pos + 1], DTYPE_SOLID);
						do_move(game, move_type, MOVE_RIGHT, root->x_pos, root->y_pos);
					}
				}
			}
		}
		pop_movables(&root);
	}
}

void update_converter(StackMovables *root, Game *const game) {

	while(root != NULL) {
		if(root->y_pos - 1 >= 0) {
			if(root->y_pos + 1 < game->map.info_tile_map.height) {
				if(game->map.tile_map[root->y_pos - 1][root->x_pos].tile == TILE_STONE) {
					if(game->map.tile_map[root->y_pos - 1][root->x_pos].is_movable == TRUE) {
						if(game->map.tile_map[root->y_pos + 1][root->x_pos].tile == TILE_BACKGROUND) {
							convert_tile(&(game->map.tile_map[root->y_pos - 1][root->x_pos]), TILE_BACKGROUND);
							play_chunk(game->audio.sfx[AUDIO_SFX_DIAMOND_CREATED].chunk, game->audio.sfx[AUDIO_SFX_DIAMOND_CREATED].channel, 0);
							set_chunk_volume(game->audio.sfx[AUDIO_SFX_DIAMOND_CREATED].chunk, game->audio.vol_sfx);
							convert_tile(&(game->map.tile_map[root->y_pos + 1][root->x_pos]), TILE_LITTLE_DIAMOND);
						}
					}
				}
			}
		}
		pop_movables(&root);
	}
}

void update_spiders(StackMovables *root, Game *const game) {
		
	MoveType move_type = MTYPE_NO_MOVE;

	while(root != NULL) {
		if(game->map.tile_map[root->y_pos][root->x_pos].is_dead == FALSE) {
			switch(game->map.tile_map[root->y_pos][root->x_pos].movement) {
			case MOVE_WAIT:
				move_type = check_move_conditions(game->map.tile_map, &(game->map.info_tile_map), TILE_SPIDER, root->x_pos, root->y_pos, 1, 0);
				if(move_type != MTYPE_NO_MOVE) {
					do_move(game, move_type, MOVE_RIGHT, root->x_pos, root->y_pos);
				}
				else {
					game->map.tile_map[root->y_pos][root->x_pos].movement = MOVE_DOWN;
				}
				break;
			case MOVE_DOWN:
				move_type = check_move_conditions(game->map.tile_map, &(game->map.info_tile_map), TILE_SPIDER, root->x_pos, root->y_pos, 0, 1);
				if(move_type != MTYPE_NO_MOVE) {
					do_move(game, move_type, MOVE_DOWN, root->x_pos, root->y_pos);
				}
				else {
					if(get_random_number(0,1)) {
						game->map.tile_map[root->y_pos][root->x_pos].movement = MOVE_LEFT;
					}
					else {
						game->map.tile_map[root->y_pos][root->x_pos].movement = MOVE_UP;	
					}
				}
				break;
			case MOVE_LEFT:
				move_type = check_move_conditions(game->map.tile_map, &(game->map.info_tile_map), TILE_SPIDER, root->x_pos, root->y_pos, -1, 0);
				if(move_type != MTYPE_NO_MOVE) {
					do_move(game, move_type, MOVE_LEFT, root->x_pos, root->y_pos);	
				}
				else {
					game->map.tile_map[root->y_pos][root->x_pos].movement = MOVE_WAIT;	
				}
				break;
			case MOVE_UP:
				move_type = check_move_conditions(game->map.tile_map, &(game->map.info_tile_map), TILE_SPIDER, root->x_pos, root->y_pos, 0, -1);
				if(move_type != MTYPE_NO_MOVE) {
					do_move(game, move_type, MOVE_UP, root->x_pos, root->y_pos);
				}
				else {
					game->map.tile_map[root->y_pos][root->x_pos].movement = MOVE_WAIT;
				}
				break;
			default:
				break;
			}
		}
		pop_movables(&root);
	}
}

void update_monsters(StackMovables *root, Game *const game) {
	
	Point2D src, des;
	Movement move;
	MoveType move_type;

	des.x = (int)(game->screen.camera.object->base_des_rect.x / TILE_WIDTH);
	des.y = (int)(game->screen.camera.object->base_des_rect.y / TILE_HEIGHT);

	while(root != NULL) {
		if(game->map.tile_map[root->y_pos][root->x_pos].is_dead == FALSE) {
			src.x = root->x_pos;
			src.y = root->y_pos;

			move = find_manhattan_movement(&src, &des, game->map.tile_map, &(game->map.info_tile_map), TILE_MONSTER);
			move_type = check_move(game->map.tile_map, &(game->map.info_tile_map), TILE_MONSTER, move, root->x_pos, root->y_pos);
			if(move_type != MTYPE_NO_MOVE) {
				do_move(game, move_type, move, root->x_pos, root->y_pos);
			}
		}
		pop_movables(&root);
	}
}

void update_character(StackMovables *root, Game *const game) {

	MoveType move_type = MTYPE_NO_MOVE;

	while(root != NULL) {
		if(game->map.tile_map[root->y_pos][root->x_pos].is_dead == FALSE) {
			move_type = check_move(game->map.tile_map, &(game->map.info_tile_map), TILE_CHARACTER, game->player.movement_player, root->x_pos, root->y_pos);
			if(move_type != MTYPE_NO_MOVE) {

				if(move_type == MTYPE_WITH_STONE) {
					do_move(game, MTYPE_WITH_STONE, game->player.movement_player, root->x_pos, root->y_pos);
				}
				else {
					do_move(game, MTYPE_NORMAL, game->player.movement_player, root->x_pos, root->y_pos);
				}

				follow_camera_bounded(&(game->screen.camera), game->map.tile_map, game->player.movement_player, root->x_pos, root->y_pos);
				game->player.object = game->screen.camera.object;
				game->player.last_movement = game->player.movement_player;

				if(move_type == MTYPE_SCORE_DIAMOND) {
					play_chunk(game->audio.sfx[AUDIO_SFX_DIAMOND_PICK].chunk, game->audio.sfx[AUDIO_SFX_DIAMOND_PICK].channel, 0);
					set_chunk_volume(game->audio.sfx[AUDIO_SFX_DIAMOND_PICK].chunk, game->audio.vol_sfx);
					game->player.score.point += SCORE_DIAMOND;
					handle_gate(&(game->level.gate), game->map.tile_map, &(game->audio.sfx[AUDIO_SFX_GATE_OPEN]), game->audio.vol_sfx);	
				}
				else if(move_type == MTYPE_GATE) {
					game->level.gate.is_player_there = TRUE;
					game->level.stop_others = TRUE;
					handle_anim(&(game->map.tile_map[root->y_pos][root->x_pos].anim), TILE_CHARACTER);
				}
				else if(move_type == MTYPE_DIRT) {
					play_chunk(game->audio.sfx[AUDIO_SFX_STEP_DIRT].chunk, game->audio.sfx[AUDIO_SFX_STEP_DIRT].channel, 0);
					set_chunk_volume(game->audio.sfx[AUDIO_SFX_STEP_DIRT].chunk, game->audio.vol_sfx);
				}
			}
			else {
				if(game->map.tile_map[root->y_pos][root->x_pos].movement != MOVE_WAIT) {
					handle_anim(&(game->map.tile_map[root->y_pos][root->x_pos].anim), TILE_CHARACTER);
				}
				game->map.tile_map[root->y_pos][root->x_pos].movement = MOVE_WAIT;
			}
		}
		else {
			handle_anim(&(game->map.tile_map[root->y_pos][root->x_pos].anim), TILE_CHARACTER);
		}
		pop_movables(&root);
	}
}

MoveType check_move(TileMap **const map, const TileMapInfo *const info_map, const TileSet tile, const Movement movement,
						const int x_pos, const int y_pos) {

	MoveType move_type = MTYPE_NO_MOVE;

	switch(movement) {
		case MOVE_UP:
			move_type = check_move_conditions(map, info_map, tile, x_pos, y_pos, 0, -1);
			break;
		case MOVE_RIGHT:
			move_type = check_move_conditions(map, info_map, tile, x_pos, y_pos, 1, 0);
			break;
		case MOVE_DOWN:
			move_type = check_move_conditions(map, info_map, tile, x_pos, y_pos, 0, 1);
			break;
		case MOVE_LEFT:
			move_type = check_move_conditions(map, info_map, tile, x_pos, y_pos, -1, 0);
			break;
		default:
			break;
	}

	return move_type;
}

MoveType check_move_conditions(TileMap **const map, const TileMapInfo *const info_map, const TileSet tile,
								const int x_pos, const int y_pos, const int x_move, const int y_move) {

	MoveType move_type = MTYPE_NO_MOVE;

	if(y_pos + y_move >= 0 && y_pos + y_move < info_map->height && x_pos + x_move >= 0 && x_pos + x_move < info_map->width) {

			switch(tile) {
				case TILE_CHARACTER:
					if(map[y_pos + y_move][x_pos + x_move].tile == TILE_BACKGROUND) {
						move_type = MTYPE_NORMAL;
					}
					else if(map[y_pos + y_move][x_pos + x_move].tile == TILE_STONE) {
						if((x_move == 1 || x_move == -1) && y_move == 0) {
							if(map[y_pos][x_pos + x_move].is_movable == TRUE) {

								if(x_pos + x_move * 2 >= 0 && x_pos + x_move * 2 < info_map->width) {

									if(map[y_pos][x_pos + x_move * 2].tile == TILE_BACKGROUND) {
										move_type = MTYPE_WITH_STONE;
										if(y_pos + 1 < info_map->height) {
											if(map[y_pos + 1][x_pos + x_move].tile == TILE_BACKGROUND) {
												move_type = MTYPE_NO_MOVE;
											}
										}
									}
								}
							}
						}
					}
					else if(map[y_pos + y_move][x_pos + x_move].tile == TILE_DIAMOND && map[y_pos + y_move][x_pos + x_move].is_movable == TRUE) {
						move_type = MTYPE_SCORE_DIAMOND;
					}
					else if(map[y_pos + y_move][x_pos + x_move].tile == TILE_GATE) {
						move_type = MTYPE_GATE;
					}
					else if(map[y_pos + y_move][x_pos + x_move].tile == TILE_DIRT) {
						move_type = MTYPE_DIRT;
					}
					break;
				case TILE_STONE:
					if(map[y_pos + y_move][x_pos + x_move].tile == TILE_BACKGROUND) {
						move_type = MTYPE_NORMAL;
					}
					else if(map[y_pos + y_move][x_pos + x_move].tile == TILE_SPIDER ||
							map[y_pos + y_move][x_pos + x_move].tile == TILE_MONSTER) {
						move_type = MTYPE_KILL;
					}
					break;
				case TILE_DIAMOND:
					if(map[y_pos + y_move][x_pos + x_move].tile == TILE_BACKGROUND) {
						move_type = MTYPE_NORMAL;
					}
					else if(map[y_pos + y_move][x_pos + x_move].tile == TILE_SPIDER ||
							map[y_pos + y_move][x_pos + x_move].tile == TILE_MONSTER) {
						move_type = MTYPE_KILL;
					}
					break;
				case TILE_SPIDER:
					if(map[y_pos + y_move][x_pos + x_move].tile == TILE_BACKGROUND) {
						move_type = MTYPE_NORMAL;
					}
					break;
				case TILE_MONSTER:
					if(map[y_pos + y_move][x_pos + x_move].tile == TILE_BACKGROUND) {
						move_type = MTYPE_NORMAL;
					}
					break;
				case TILE_WATER:
					if(map[y_pos + y_move][x_pos + x_move].tile == TILE_DIRT) {
						move_type = MTYPE_WATER;
					}
					break;
				default:
					break;
			}
	}

	return move_type;
}

/*does proper move direction*/
void do_move(Game *const game, const MoveType move_type, const Movement movement, const int x_pos, const int y_pos) {

	switch(movement) {
		case MOVE_UP:
			do_move_helper(game, move_type, movement, x_pos, y_pos, 0, -1);
			break;
		case MOVE_RIGHT:
			do_move_helper(game, move_type, movement, x_pos, y_pos, 1, 0);
			break;
		case MOVE_DOWN:
			do_move_helper(game, move_type, movement, x_pos, y_pos, 0, 1);
			break;
		case MOVE_LEFT:
			do_move_helper(game, move_type, movement, x_pos, y_pos, -1, 0);
			break;
		default:
			break;
	}
}

/*changes tiles with proper move action as ids in map*/ 
void do_move_helper(Game *const game, const MoveType move_type, const Movement movement,
						const int x_pos, const int y_pos, const int x_move, const int y_move) {

	switch(move_type) {
		case MTYPE_NORMAL:
			do_move_normal(game, movement, x_pos, y_pos, x_move, y_move);
			break;
		case MTYPE_WITH_STONE:
			do_move_with_stone(game, movement, x_pos, y_pos, x_move, y_move);
			break;
		default:
			break;
	}
}

void do_move_normal(Game *const game, const Movement movement,
						const int x_pos, const int y_pos, const int x_move, const int y_move) {

	game->map.tile_map[y_pos][x_pos].future_des_rect.x = game->map.tile_map[y_pos][x_pos].base_des_rect.x + (x_move * TILE_WIDTH);
	game->map.tile_map[y_pos][x_pos].future_des_rect.y = game->map.tile_map[y_pos][x_pos].base_des_rect.y + (y_move * TILE_HEIGHT);
	game->map.tile_map[y_pos][x_pos].movement = movement;
	game->map.tile_map[y_pos][x_pos].is_movable = FALSE;
	
	if(game->map.tile_map[y_pos][x_pos].tile != TILE_CHARACTER ||
		(game->map.tile_map[y_pos][x_pos].tile == TILE_CHARACTER && movement != game->player.last_movement)) {
		
		handle_anim(&(game->map.tile_map[y_pos][x_pos].anim), game->map.tile_map[y_pos][x_pos].tile);
	}

	if(game->map.tile_map[y_pos + y_move][x_pos + x_move].is_movable == TRUE && game->map.tile_map[y_pos + y_move][x_pos + x_move].tile != TILE_DIAMOND) {
		game->map.tile_map[y_pos][x_pos].occupied_src_rect = game->map.tile_map[y_pos + y_move][x_pos + x_move].src_rect;
	}
	else if(game->map.tile_map[y_pos + y_move][x_pos + x_move].tile == TILE_DIAMOND) {
		switch(game->map.tile_map[y_pos + y_move][x_pos + x_move].src_rect.y / 64) {

			case 1:
				find_src_rect(&game->map.tile_map[y_pos][x_pos].occupied_src_rect, TILE_OCCUPIED_CHARACTER_DIAMOND_ZERO);
				break;
			case 2:
				find_src_rect(&game->map.tile_map[y_pos][x_pos].occupied_src_rect, TILE_OCCUPIED_CHARACTER_DIAMOND_ONE);
				break;
			case 3:
				find_src_rect(&game->map.tile_map[y_pos][x_pos].occupied_src_rect, TILE_OCCUPIED_CHARACTER_DIAMOND_TWO);
				break;
			case 4:
				find_src_rect(&game->map.tile_map[y_pos][x_pos].occupied_src_rect, TILE_OCCUPIED_CHARACTER_DIAMOND_THREE);
				break;
			default:
				break; 

		} 
	}
	else {
		find_src_rect(&game->map.tile_map[y_pos][x_pos].occupied_src_rect, TILE_BACKGROUND);	
	}

	game->map.tile_map[y_pos][x_pos].occupied_base_des_rect.x = game->map.tile_map[y_pos][x_pos].future_des_rect.x;
	game->map.tile_map[y_pos][x_pos].occupied_base_des_rect.y = game->map.tile_map[y_pos][x_pos].future_des_rect.y;

	if(game->map.tile_map[y_pos][x_pos].tile == TILE_CHARACTER) {
		game->map.tile_map[y_pos][x_pos].occupied_des_rect.w = TILE_WIDTH;
		game->map.tile_map[y_pos][x_pos].occupied_des_rect.h = TILE_HEIGHT;
	}	

	game->map.tile_map[y_pos + y_move][x_pos + x_move] = game->map.tile_map[y_pos][x_pos];

	reset_to_background(&(game->map.tile_map[y_pos][x_pos]));

	/*this is a delay for solids, this gives a 1 pyxel offset which gives player chance to react from death cause of solids*/
	if(game->map.tile_map[y_pos + y_move][x_pos + x_move].tile == TILE_CHARACTER) {
		add_velocity(&(game->map.tile_map[y_pos + y_move][x_pos + x_move]), game);

		optimize_tile(&(game->map.tile_map[y_pos + y_move][x_pos + x_move]), game->time.delta_time, movement);
	}
}

void do_move_with_stone(Game *const game, const Movement movement,
							const int x_pos, const int y_pos, const int x_move, const int y_move) {

	/*we don't delay stone's move if it is pushed by player*/
	do_move_normal(game, movement, x_pos+x_move, y_pos+y_move, x_move, y_move);
	add_velocity(&(game->map.tile_map[y_pos + y_move * 2][x_pos + x_move * 2]), game);
	optimize_tile(&(game->map.tile_map[y_pos + y_move * 2][x_pos + x_move * 2]), game->time.delta_time, movement);
	
	do_move_normal(game, movement, x_pos, y_pos, x_move, y_move);
}

void do_move_water(TileMap **const map, const Movement movement, const int x_pos, const int y_pos, Level *const level,
						const int x_move, const int y_move) {

	map[y_pos][x_pos].future_des_rect.x = map[y_pos][x_pos].base_des_rect.x + (x_move * TILE_WIDTH);
	map[y_pos][x_pos].future_des_rect.y = map[y_pos][x_pos].base_des_rect.y + (y_move * TILE_HEIGHT);
	map[y_pos][x_pos].movement = movement;
	map[y_pos][x_pos].is_movable = FALSE;
	find_src_rect(&map[y_pos][x_pos].occupied_src_rect, TILE_OCCUPIED_WATER_DIRT);
	map[y_pos][x_pos].occupied_base_des_rect = map[y_pos + y_move][x_pos + x_move].base_des_rect;
	map[y_pos + y_move][x_pos + x_move] = map[y_pos][x_pos];

	reset_to_water(&map[y_pos][x_pos]);
	do_move_water_helper(&map[y_pos + y_move][x_pos + x_move], level);

	/*on systems which gets like below 5 FPS, at first game cycle timer holds the 0.5 part of the game loop,
		but at the other cycles timer holds 1 part of the game loop, so if flow time higher than the 0.5 game loop,
			but lower than 1 game loop, a graphic bug appears*/
	/*the reason why i'm not using an if statement is this problem happens on slow systems so there would be 3 thing for CPU
		instead of 2, and 2 thing instead of 1 is no problem for fast systems*/
	map[y_pos + y_move][x_pos + x_move].movement = movement;
	map[y_pos + y_move][x_pos + x_move].is_movable = FALSE;
}

void do_move_water_helper(TileMap *const tile, Level *const level) {

	double rate;
	double delta_move = 0.0;

	if(level->water.time <= level->water.flow_time + level->water.flow_time_extra) {
		rate = calculate_rate(level->water.time, level->water.flow_time + level->water.flow_time_extra);
		rate = 1 - rate;
		switch(tile->movement) {
			case MOVE_UP:
				delta_move = (int)(TILE_HEIGHT * rate);
				if(tile->base_des_rect.y > tile->future_des_rect.y + delta_move) {
					tile->base_des_rect.y = tile->future_des_rect.y + delta_move;
				}
				break;
			case MOVE_RIGHT:
				delta_move = (int)(TILE_WIDTH * rate);
				if(tile->base_des_rect.x < tile->future_des_rect.x - delta_move) {	
					tile->base_des_rect.x = tile->future_des_rect.x - delta_move;
				}
				break;
			case MOVE_DOWN:
				delta_move = (int)(TILE_HEIGHT * rate);
				if(tile->base_des_rect.y < tile->future_des_rect.y - delta_move) {
					tile->base_des_rect.y = tile->future_des_rect.y - delta_move;
				}
				break;
			case MOVE_LEFT:
				delta_move = (int)(TILE_WIDTH * rate);
				if(tile->base_des_rect.x > tile->future_des_rect.x + delta_move) {
					tile->base_des_rect.x = tile->future_des_rect.x + delta_move;
				}
				break;
			default:
				break;
		}
	}
	else {
		tile->base_des_rect.x = tile->future_des_rect.x;
		tile->base_des_rect.y = tile->future_des_rect.y;
		reset_to_water(tile);
	}
}

/*gives proper rectangle location in tileset.png files*/
void find_src_rect(SDL_Rect *const src_rect, const TileSet tile) {

	src_rect->x = (tile % 10) * TILE_WIDTH;
	src_rect->y = (tile / 10) * TILE_HEIGHT;
	src_rect->w = TILE_WIDTH;
	src_rect->h = TILE_HEIGHT;
}

void reset_to_background(TileMap *background) {

	background->tile = TILE_BACKGROUND;
	find_src_rect(&(background->src_rect), TILE_BACKGROUND);
	background->movement = MOVE_WAIT;
	background->is_movable = TRUE;
	background->anim.frame = 0;
	background->anim.frame_time = 0.0;
	background->is_dead = FALSE;
	background->destroy = FALSE;
}

void reset_to_water(TileMap *water) {

	water->tile = TILE_WATER;
	find_src_rect(&(water->src_rect), TILE_WATER);
	water->movement = MOVE_WAIT;
	water->is_movable = TRUE;
}

/*adds velocities in proper directions to coordinates related with framerate*/  
void add_velocity(TileMap *const tile, Game *const game) {

	double resultant_speed = get_resultant_speed(tile->tile, game);

	switch(tile->movement) {
		case MOVE_UP:
			tile->HR_base_des_rect.y -= TILE_HEIGHT * resultant_speed * game->time.delta_time;
			tile->base_des_rect.y = (int)tile->HR_base_des_rect.y; 
			if(tile->future_des_rect.y >= tile->base_des_rect.y) {
				tile->base_des_rect.y = tile->future_des_rect.y;
				tile->HR_base_des_rect.y = (double)tile->base_des_rect.y;
				get_next_movement(tile, game->map.tile_map, &(game->map.info_tile_map), game->audio.sfx, game->audio.vol_sfx, game->level.gate.is_player_there);
			}
			break;
		case MOVE_RIGHT:
			tile->HR_base_des_rect.x += TILE_WIDTH * resultant_speed * game->time.delta_time;
			tile->base_des_rect.x = (int)tile->HR_base_des_rect.x;
			if(tile->future_des_rect.x <= tile->base_des_rect.x) {
				tile->base_des_rect.x = tile->future_des_rect.x;
				tile->HR_base_des_rect.x = (double)tile->base_des_rect.x;
				get_next_movement(tile, game->map.tile_map, &(game->map.info_tile_map), game->audio.sfx, game->audio.vol_sfx, game->level.gate.is_player_there);
			}
			break;
		case MOVE_DOWN:
			tile->HR_base_des_rect.y += TILE_HEIGHT * resultant_speed * game->time.delta_time;
			tile->base_des_rect.y = (int)tile->HR_base_des_rect.y;
			if(tile->future_des_rect.y <= tile->base_des_rect.y) {
				tile->base_des_rect.y = tile->future_des_rect.y;
				tile->HR_base_des_rect.y = (double)tile->base_des_rect.y;
				get_next_movement(tile, game->map.tile_map, &(game->map.info_tile_map), game->audio.sfx, game->audio.vol_sfx, game->level.gate.is_player_there);
			}
			break;
		case MOVE_LEFT:
			tile->HR_base_des_rect.x -= TILE_WIDTH * resultant_speed * game->time.delta_time;
			tile->base_des_rect.x = (int)tile->HR_base_des_rect.x;
			if(tile->future_des_rect.x >= tile->base_des_rect.x) {
				tile->base_des_rect.x = tile->future_des_rect.x;
				tile->HR_base_des_rect.x = (double)tile->base_des_rect.x;
				get_next_movement(tile, game->map.tile_map, &(game->map.info_tile_map), game->audio.sfx, game->audio.vol_sfx, game->level.gate.is_player_there);
			}
			break;
		default:
			break;
	}
}

void get_next_movement(TileMap *const tile, TileMap **const map, const TileMapInfo *const info_map, const SFX *const sfx, const Uint8 vol, const bool is_player_there) {
	
	if(tile->tile == TILE_STONE) {
		check_kill_solid(map, info_map, tile->base_des_rect.x / TILE_WIDTH, tile->base_des_rect.y / TILE_HEIGHT, tile->movement, sfx, vol);

		if(tile->movement == MOVE_DOWN) {
			if((tile->base_des_rect.y / 64) + 1 < info_map->height) {
				if(map[(tile->base_des_rect.y / 64) + 1][tile->base_des_rect.x / 64].tile != TILE_BACKGROUND) {
					play_chunk(sfx[AUDIO_SFX_STONE_FELL].chunk, sfx[AUDIO_SFX_STONE_FELL].channel, 0);
					set_chunk_volume(sfx[AUDIO_SFX_STONE_FELL].chunk, vol);
				}
			}
		}
	}
	else if(tile->tile == TILE_DIAMOND) {
		check_kill_solid(map, info_map, tile->base_des_rect.x / TILE_WIDTH, tile->base_des_rect.y / TILE_HEIGHT, tile->movement, sfx, vol);

		if((tile->base_des_rect.y / 64) + 1 < info_map->height) {
			if(map[(tile->base_des_rect.y / 64) + 1][tile->base_des_rect.x / 64].tile != TILE_BACKGROUND) {
				play_chunk(sfx[AUDIO_SFX_DIAMOND_FELL].chunk, sfx[AUDIO_SFX_DIAMOND_FELL].channel, 0);
				set_chunk_volume(sfx[AUDIO_SFX_DIAMOND_FELL].chunk, vol);
			}
		}
	}

	tile->is_movable = TRUE;
	if(tile->tile != TILE_CHARACTER || (tile->tile == TILE_CHARACTER && (tile->is_dead == TRUE || is_player_there == TRUE))) {
		handle_anim(&tile->anim, tile->tile);
	}

	switch(tile->tile) {
		case TILE_SPIDER:
			switch(tile->movement) {
				case MOVE_RIGHT:
					tile->movement = MOVE_DOWN;
					break;
				case MOVE_DOWN:
					if(get_random_number(0,1)) {
						tile->movement = MOVE_LEFT;
					}
					else {
						tile->movement = MOVE_UP;
					}
					break;
				case MOVE_LEFT:
				case MOVE_UP:
					tile->movement = MOVE_WAIT;
					break;
				default:
					break;
			}
			break;
		default:
			if(tile->tile != TILE_CHARACTER) {
				tile->movement = MOVE_WAIT;
			}
			break;
	}
}

/*on very slow machines helps to keep healthy graphics
	very slow machines mean BIG delta_time
		which then means tiles is not smoothly moves but jumps to another instantly
			you can test this with putting an SDL_Delay(milliseconds) on game loop with also removing this*/
void optimize_tile(TileMap *const tile, const double delta_time, const Movement movement) {

	if(tile->is_movable != FALSE) {
		tile->is_movable = FALSE;
		tile->movement = movement;
	}
	else if(delta_time <= 0.0) {
		tile->base_des_rect.x = tile->future_des_rect.x;
		tile->base_des_rect.y = tile->future_des_rect.y;
	}
}

void convert_tile(TileMap *const target, const TileSet tile) {

	target->tile = tile;
	find_src_rect(&target->src_rect, tile);
	if(target->is_movable == FALSE) {
		target->base_des_rect.x = target->future_des_rect.x;
		target->base_des_rect.y = target->future_des_rect.y;
		target->is_movable = TRUE;
	}
	target->movement = MOVE_WAIT;
	target->is_dead = FALSE;
	handle_anim(&target->anim, tile);
	target->destroy = FALSE;
}

bool check_if_dirt(TileMap *const tile, const SDL_Rect *const dirt_src_rect) {

	bool is_dirt = FALSE;

	if(tile->occupied_src_rect.x < dirt_src_rect->x + TILE_WIDTH) {
		if(tile->occupied_src_rect.x >= dirt_src_rect->x) {
			if(tile->occupied_src_rect.y < dirt_src_rect->y + TILE_HEIGHT) {
				if(tile->occupied_src_rect.y >= dirt_src_rect->y) {
					is_dirt = TRUE;
				}
			}
		}
	}

	return is_dirt;
}

void free_map(TileMap ***map, const TileMapInfo *const info_map) {

	int y_pos;

	if((*map) != NULL) {
		for(y_pos = 0; y_pos < info_map->height; ++y_pos) {
			if((*map)[y_pos] != NULL) {
				free((*map)[y_pos]);
				(*map)[y_pos] = NULL;
			}
		}
		free((*map));
		(*map) = NULL;
	}
}
