#include <RPS/BD.h>

void do_events(Game *const game) {
	
	SDL_Event event;

	/*handling general events in a while loop*/
	while(SDL_PollEvent(&event)) {

		switch(event.type) {
			case SDL_QUIT:
				game->is_running = FALSE;
				break;

			case SDL_WINDOWEVENT:
				switch(event.window.event) {
					case SDL_WINDOWEVENT_SIZE_CHANGED:
						get_window_size(game->screen.window, &(game->screen.info_window));
						update_perm_rects(game->video.perm_textures.rects, &(game->screen.info_window));
						update_hud_rects(game->video.hud.rects, &(game->screen.info_window));
						break;
				}
				break;

			default:
				break;
		}
	}
	
	handle_player_movement(&(game->player.movement_player));
	handle_keyboard(&(game->input.keyboard));
}

void do_events_gui(Game *const game) {

	SDL_Event event;

	/*handling general events in a while loop*/
	while(SDL_PollEvent(&event)) {

		switch(event.type) {
			case SDL_QUIT:
				game->is_running = FALSE;
				break;

			case SDL_WINDOWEVENT:
				switch(event.window.event) {
					case SDL_WINDOWEVENT_SIZE_CHANGED:
						get_window_size(game->screen.window, &game->screen.info_window);
						update_perm_rects(game->video.perm_textures.rects, &(game->screen.info_window));
						update_hud_rects(game->video.hud.rects, &(game->screen.info_window));
						break;
				}
				break;

			default:
				break;
		}
	}

	handle_keyboard(&game->input.keyboard);	
}

void handle_player_movement(Movement *const movement_player) {

	const Uint8 *keystates = SDL_GetKeyboardState(NULL);

	if(keystates[SDL_SCANCODE_W] || keystates[SDL_SCANCODE_UP]) {
		*movement_player = MOVE_UP;
	}
	else if(keystates[SDL_SCANCODE_D] || keystates[SDL_SCANCODE_RIGHT]) {
		*movement_player = MOVE_RIGHT;
	}
	else if(keystates[SDL_SCANCODE_S] || keystates[SDL_SCANCODE_DOWN]) {
		*movement_player = MOVE_DOWN;
	}
	else if(keystates[SDL_SCANCODE_A] || keystates[SDL_SCANCODE_LEFT]) {
		*movement_player = MOVE_LEFT;
	}
	else {
		*movement_player = MOVE_WAIT;
	}
}

/*keyboard inputs is more consistent if you handle them like a snapshot of keyboard*/
void handle_keyboard(Keyboard *const keyboard) {

	const Uint8 *keystates = SDL_GetKeyboardState(NULL);		/*Uint8 and other different sized integers that uses typedef is declared in SDL*/
	Uint64 timer_current;

	if(keyboard->get_key == TRUE) {

		if(keystates[SDL_SCANCODE_ESCAPE]) {
			keyboard->key = KEY_ESC;
			keyboard->get_key = FALSE;
		}
		else if(keystates[SDL_SCANCODE_RETURN]) {
			keyboard->key = KEY_ENTER;
			keyboard->get_key = FALSE;
		}
		else if(keystates[SDL_SCANCODE_D]) {
			keyboard->key = KEY_D;
			keyboard->get_key = FALSE;
		}
		else if(keystates[SDL_SCANCODE_RIGHT]) {
			keyboard->key = KEY_RIGHT;
			keyboard->get_key = FALSE;
		}
		else if(keystates[SDL_SCANCODE_A]) {
			keyboard->key = KEY_A;
			keyboard->get_key = FALSE;
		}
		else if(keystates[SDL_SCANCODE_LEFT]) {
			keyboard->key = KEY_LEFT;
			keyboard->get_key = FALSE;
		}
		else if(keystates[SDL_SCANCODE_UP]) {
			keyboard->key = KEY_UP;
			keyboard->get_key = FALSE;
		}
		else if(keystates[SDL_SCANCODE_W]) {
			keyboard->key = KEY_W;
			keyboard->get_key = FALSE;
		}
		else if(keystates[SDL_SCANCODE_DOWN]) {
			keyboard->key = KEY_DOWN;
			keyboard->get_key = FALSE;
		}
		else if(keystates[SDL_SCANCODE_S]) {
			keyboard->key = KEY_S;
			keyboard->get_key = FALSE;
		}
		else {
			keyboard->key = KEY_NONE;
		}
	}

	if(keyboard->get_key == FALSE) {

		timer_current = SDL_GetPerformanceCounter();
		keyboard->last_time = get_time_seconds(keyboard->timer_start, &timer_current);
		keyboard->time += keyboard->last_time;
	}
}

void handle_menu_events(Game *const game, const int layer_place, bool *quit_loop) {

	switch(layer_place) {

		case 0:
			open_settings(game);
			break;
		case 1:

			if(game->settings.dev_mode.is_on == FALSE) {
				if(game->player.lives > 1) {
					--(game->player.lives);
				}
				else {
					game->end = TRUE;
					game->win = FALSE;
				}
			}

			free_map(&(game->map.tile_map), &(game->map.info_tile_map));
			free_camera(&(game->screen.camera));
			*quit_loop = TRUE;
			break;

		case 2:

			if(game->settings.dev_mode.is_on == FALSE) {
				if(game->player.lives > 1) {
					--(game->player.lives);
				}
				else {
					game->end = TRUE;
					game->win = FALSE;
				}
			}

			free_map(&(game->map.tile_map), &(game->map.info_tile_map));
			free_camera(&(game->screen.camera));
			game->level.is_level_screen_open = TRUE;
			*quit_loop = TRUE;
			break;
		case 3:
			if(game->mode != GAME_MODE_IMPOSSIBLE) {
				if(save_game(&game->player, &game->level, game->mode, &game->settings.dev_mode) != 0) {
					show_text_timed_screen(game, game->video.perm_textures.textures[TEXTURE_PERM_FAIL_SAVE], &game->video.perm_textures.rects[RECT_PERM_DES_FAIL_SAVE], 3.0);
				}
			}
			else {
				show_text_timed_screen(game, game->video.perm_textures.textures[TEXTURE_PERM_CANT_SAVE], &game->video.perm_textures.rects[RECT_PERM_DES_CANT_SAVE], 3.0);
			}
			break;
		case 4:
			if(load_save(game) != 0) {
				show_text_timed_screen(game, game->video.perm_textures.textures[TEXTURE_PERM_FAIL_LOAD], &game->video.perm_textures.rects[RECT_PERM_DES_FAIL_LOAD], 3.0);
			}
			break;
		case 5:
			if(open_are_you_sure(game, NULL, NULL, TRUE)) {
				game->is_running = FALSE;
			}
			break;
		default:
			break;
	}
}

Movement find_camera_movement(const Point2D *const base, const Point2D *const future) {

	Movement move = MOVE_WAIT;

	if(future->x - base->x == 0) {
		if(future->y - base->y == 0) move = MOVE_WAIT;
		else if(future->y - base->y < 0) move = MOVE_UP;
		else move = MOVE_DOWN; 
	}
	else if(future->x - base->x < 0) {
		if(future->y - base->y == 0) move = MOVE_LEFT;
		else if(future->y - base->y < 0) move = MOVE_UP_LEFT;
		else move = MOVE_DOWN_LEFT;
	}
	else {
		if(future->y - base->y == 0) move = MOVE_RIGHT;
		else if(future->y - base->y < 0) move = MOVE_UP_RIGHT;
		else move = MOVE_DOWN_RIGHT;
	}

	return move;
}

Movement find_manhattan_movement(const Point2D *const src, const Point2D *const des,
										TileMap **const map, const TileMapInfo *const info_map, const TileSet tile) {

	Movement move = MOVE_WAIT;
	Point2D manhattan = { .x = des->x - src->x,
							.y = des->y - src->y};

	if(get_absolute_value(manhattan.x) > get_absolute_value(manhattan.y)) {
		move = manhattan_helper_x(&manhattan, src, TRUE, map, info_map, tile);
	}
	else if(get_absolute_value(manhattan.x) < get_absolute_value(manhattan.y)) {
		move = manhattan_helper_y(&manhattan, src, TRUE, map, info_map, tile);
	}
	else if(get_absolute_value(manhattan.x) == get_absolute_value(manhattan.y) && manhattan.x != 0) {
		if(get_random_number(0,1)) {
			move = manhattan_helper_x(&manhattan, src, TRUE, map, info_map, tile);
		}
		else {
			move = manhattan_helper_y(&manhattan, src, TRUE, map, info_map, tile);
		}
	}
 
	return move;
}

Movement manhattan_helper_x(const Point2D *const manhattan, const Point2D *const src, const bool try_again,
								TileMap **const map, const TileMapInfo *const info_map, const TileSet tile) {

	Movement move = MOVE_WAIT;
	MoveType move_type = MTYPE_NO_MOVE;

	if(manhattan->x > 0) {
		move = MOVE_RIGHT;
	}
	else {
		move = MOVE_LEFT;
	}

	move_type = check_move(map, info_map, tile, move, src->x, src->y);
	if(move_type == MTYPE_NO_MOVE) {
		if(get_absolute_value(manhattan->y) != 0 && try_again == TRUE) {
			move = manhattan_helper_y(manhattan, src, FALSE, map, info_map, tile);
		}
		else {
			move = get_random_number(1,4);
		}
	}

	return move;
}

Movement manhattan_helper_y(const Point2D *const manhattan, const Point2D *const src, const bool try_again,
								TileMap **const map, const TileMapInfo *const info_map, const TileSet tile) {

	Movement move = MOVE_WAIT;
	MoveType move_type = MTYPE_NO_MOVE;

	if(manhattan->y > 0) {
		move = MOVE_DOWN;
	}
	else {
		move = MOVE_UP;
	}

	move_type = check_move(map, info_map, tile, move, src->x, src->y);
	if(move_type == MTYPE_NO_MOVE) {
		if(get_absolute_value(manhattan->x) != 0 && try_again == TRUE) {
			move = manhattan_helper_x(manhattan, src, FALSE, map, info_map, tile);
		}
		else {
			move = get_random_number(1,4);
		}
	}

	return move;
}

void check_kill_solid(TileMap **const map, const TileMapInfo *const info_map, const int x_pos, const int y_pos, const Movement movement,
						const SFX *const sfx, const Uint8 vol) {

	if(y_pos + 1 < info_map->height) {
		if(movement == MOVE_DOWN) {
			if(map[y_pos + 1][x_pos].tile == TILE_CHARACTER) {
				map[y_pos + 1][x_pos].is_dead = TRUE;
				map[y_pos + 1][x_pos].death_type = DTYPE_SOLID;
				handle_anim(&map[y_pos + 1][x_pos].anim, TILE_CHARACTER);			
			}
		}
		else if(map[y_pos + 1][x_pos].tile == TILE_SPIDER ||
				map[y_pos + 1][x_pos].tile == TILE_MONSTER) {

			play_chunk(sfx[AUDIO_SFX_FOE_KILL].chunk, sfx[AUDIO_SFX_FOE_KILL].channel, 0);
			set_chunk_volume(sfx[AUDIO_SFX_FOE_KILL].chunk, vol);
			map[y_pos + 1][x_pos].is_dead = TRUE;
			map[y_pos + 1][x_pos].death_type = DTYPE_SOLID;
		}
	}
}

bool check_kill_foe(TileMap **const map, const TileMapInfo *const info_map, const int x_pos, const int y_pos) {

	bool result = FALSE;

	if(y_pos - 1 >= 0) {
		if(map[y_pos - 1][x_pos].tile == TILE_CHARACTER) {
			map[y_pos - 1][x_pos].is_dead = TRUE;
			map[y_pos - 1][x_pos].death_type = DTYPE_FOE;
			handle_anim(&map[y_pos - 1][x_pos].anim, TILE_CHARACTER);
			result = TRUE;
		}
	}

	if(x_pos + 1 < info_map->width) {
		if(map[y_pos][x_pos + 1].tile == TILE_CHARACTER) {
			map[y_pos][x_pos + 1].is_dead = TRUE;
			map[y_pos][x_pos + 1].death_type = DTYPE_FOE;
			handle_anim(&map[y_pos][x_pos + 1].anim, TILE_CHARACTER);
			result = TRUE;
		}
	}

	if(y_pos + 1 < info_map->height) {
		if(map[y_pos + 1][x_pos].tile == TILE_CHARACTER) {
			map[y_pos + 1][x_pos].is_dead = TRUE;
			map[y_pos + 1][x_pos].death_type = DTYPE_FOE;
			handle_anim(&map[y_pos + 1][x_pos].anim, TILE_CHARACTER);
			result = TRUE;
		}
	}

	if(x_pos - 1 >= 0) {
		if(map[y_pos][x_pos - 1].tile == TILE_CHARACTER) {
			map[y_pos][x_pos - 1].is_dead = TRUE;
			map[y_pos][x_pos - 1].death_type = DTYPE_FOE;
			handle_anim(&map[y_pos][x_pos - 1].anim, TILE_CHARACTER);
			result = TRUE;
		}
	}

	return result;
}

void check_death_character(TileMap **const map, const TileMapInfo *const info_map, const int x_pos, const int y_pos, Game *const game) {

	MoveType move_type;
	bool is_dead[4] = {TRUE, TRUE, TRUE, TRUE};	/*4 different direction*/

	if(map[y_pos][x_pos].is_dead == FALSE) {

		/*check if player is capable of moving*/
		move_type = check_move_conditions(map, info_map, TILE_CHARACTER, x_pos, y_pos, 0, -1);
		if(move_type == MTYPE_NO_MOVE) {
			move_type = check_move_conditions(map, info_map, TILE_CHARACTER, x_pos, y_pos, 1, 0);
			if(move_type == MTYPE_NO_MOVE) {
				move_type = check_move_conditions(map, info_map, TILE_CHARACTER, x_pos, y_pos, 0, 1);
				if(move_type == MTYPE_NO_MOVE) {
					move_type = check_move_conditions(map, info_map, TILE_CHARACTER, x_pos, y_pos, -1, 0);
					if(move_type == MTYPE_NO_MOVE) {

						/* check if environment around of player is moving OR CAPABLE OF MOVING*/
						if(y_pos - 1 >= 0) {
							if(map[y_pos - 1][x_pos].is_movable == FALSE) {
								is_dead[0] = FALSE;
							}
							else if(map[y_pos - 1][x_pos].tile == TILE_STONE || map[y_pos - 1][x_pos].tile == TILE_DIAMOND) {
								is_dead[0] = check_death_character_helper(game, x_pos, y_pos - 1);
							}
						}

						if(x_pos + 1 < info_map->width) {
							if(map[y_pos][x_pos + 1].is_movable == FALSE) {
								is_dead[1] = FALSE;
							}
							else if(map[y_pos][x_pos + 1].tile == TILE_STONE || map[y_pos][x_pos + 1].tile == TILE_DIAMOND) {
								is_dead[1] = check_death_character_helper(game, x_pos + 1, y_pos);
							}
						}

						if(y_pos + 1 < info_map->height) {
							if(map[y_pos + 1][x_pos].is_movable == FALSE) {
								is_dead[2] = FALSE;
							}
							else if(map[y_pos + 1][x_pos].tile == TILE_STONE || map[y_pos + 1][x_pos].tile == TILE_DIAMOND) {
								is_dead[2] = check_death_character_helper(game, x_pos, y_pos + 1);
							}
						}

						if(x_pos - 1 >= 0) {
							if(map[y_pos][x_pos - 1].is_movable == FALSE) {
								is_dead[3] = FALSE;
							}
							else if(map[y_pos][x_pos - 1].tile == TILE_STONE || map[y_pos][x_pos - 1].tile == TILE_DIAMOND) {
								is_dead[3] = check_death_character_helper(game, x_pos - 1, y_pos);
							}
						}

						if(is_dead[0] == TRUE && is_dead[1] == TRUE && is_dead[2] == TRUE && is_dead[3] == TRUE) {
							map[y_pos][x_pos].is_dead = TRUE;
							handle_anim(&map[y_pos][x_pos].anim, TILE_CHARACTER);
						}
					
					}
				}
			}		
		}

		if(is_dead[0] == TRUE && is_dead[1] == TRUE && is_dead[2] == TRUE && is_dead[3] == TRUE) {
			map[y_pos][x_pos].death_type = DTYPE_JAMMING;
			if(y_pos - 1 >= 0) {
				if(map[y_pos - 1][x_pos].tile == TILE_WATER) {
					map[y_pos][x_pos].death_type = DTYPE_WATER;
				}
			}
			if(x_pos + 1 < info_map->width) {
				if(map[y_pos][x_pos + 1].tile == TILE_WATER) {
					map[y_pos][x_pos].death_type = DTYPE_WATER;
				}
			}
			if(y_pos + 1 < info_map->height) {
				if(map[y_pos + 1][x_pos].tile == TILE_WATER) {
					map[y_pos][x_pos].death_type = DTYPE_WATER;
				}
			}
			if(x_pos - 1 >= 0) {
				if(map[y_pos][x_pos - 1].tile == TILE_WATER) {
					map[y_pos][x_pos].death_type = DTYPE_WATER;
				}
			}
		}
	}
}


/*This is a recursive function. What this does is, lets say character is jammed at 1 frame and there is a solid with adjacent to player.
	This solid may not be able to move at next frame cause there may be a dirt tile under of his or there may be again a solid under of his.
		At that frame adjacent solid may be not moving but the solid under of the adjacent solid may move and FREE THE PLAYER at next frame or it wont move
			and player is ACTUALLY jammed at his place. Why recursive? Cause there may be another solid under the solid of the adjacent solid and so on.
				This function basically version of update_solids function's. And the if statements which has do_move function returns FALSE, else TRUE.*/
bool check_death_character_helper(Game *const game, const int x_pos, const int y_pos) {

	MoveType move_type = MTYPE_NO_MOVE;
	MoveType move_type_condition = MTYPE_NO_MOVE;

		move_type = check_move_conditions(game->map.tile_map, &(game->map.info_tile_map), TILE_STONE, x_pos, y_pos, 0, 1);
		if(move_type != MTYPE_NO_MOVE) {
			return FALSE;
		}
		else if(y_pos + 1 < game->map.info_tile_map.height) {

			if(game->map.tile_map[y_pos + 1][x_pos].tile == TILE_STONE ||
				game->map.tile_map[y_pos + 1][x_pos].tile == TILE_DIAMOND ||
				game->map.tile_map[y_pos + 1][x_pos].tile == TILE_BORDER) {

				move_type = check_move_conditions(game->map.tile_map, &(game->map.info_tile_map), TILE_STONE, x_pos, y_pos, -1, 0);
				move_type_condition = check_move_conditions(game->map.tile_map, &(game->map.info_tile_map), TILE_STONE, x_pos, y_pos, -1, 1);
				if(move_type == MTYPE_NORMAL && move_type == move_type_condition) {
					return FALSE;
				}
				else if(move_type == MTYPE_NORMAL && move_type_condition == MTYPE_KILL) {
					return FALSE;
				}
				else {
					move_type = check_move_conditions(game->map.tile_map, &(game->map.info_tile_map), TILE_STONE, x_pos, y_pos, 1, 0);
					move_type_condition = check_move_conditions(game->map.tile_map, &(game->map.info_tile_map), TILE_STONE, x_pos, y_pos, 1, 1);
					if(move_type == MTYPE_NORMAL && move_type == move_type_condition) {
						return FALSE;
					}
					else if(move_type == MTYPE_NORMAL && move_type_condition == MTYPE_KILL) {
						return FALSE;
					}
					else if(game->map.tile_map[y_pos + 1][x_pos].tile == TILE_STONE ||
								game->map.tile_map[y_pos + 1][x_pos].tile == TILE_DIAMOND) {

						return check_death_character_helper(game, x_pos, y_pos + 1);
					}
					else {
						return TRUE;
					}
				}
			}
			else {
				return TRUE;
			}
		}
		else {
			return TRUE;
		}
}

void kill(TileMap *const tile, const DeathType death_type) {
	
	tile->is_dead = TRUE;
	tile->death_type = death_type;
	handle_anim(&tile->anim, tile->tile);
}
