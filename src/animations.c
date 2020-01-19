#include <RPS/BD.h>

void handle_anim(Anim *const anim, const TileSet tile) {

	if(tile == TILE_CHARACTER || tile == TILE_STONE || tile == TILE_STAR || tile == TILE_LITTLE_DIAMOND || tile == TILE_GATE) {
		reset_frame(anim);
	}
}

void reset_frame(Anim *const anim) {

	anim->frame = 0;
	anim->frame_time = 0.0; 
}

void late_update_map(Game *const game) {

	int x_pos, y_pos;
	StackMovables *root[STACK_COUNT + STACK_EXTRA_COUNT];

	if(game->map.tile_map != NULL) {

		init_stack_array(root, STACK_COUNT + STACK_EXTRA_COUNT);

		for(y_pos = 0; y_pos < game->map.info_tile_map.height; ++y_pos) {
			for(x_pos = 0; x_pos < game->map.info_tile_map.width; ++x_pos) {
				switch(game->map.tile_map[y_pos][x_pos].tile) {
					case TILE_CHARACTER:
						push_movables(&root[STACK_CHARACTER], x_pos, y_pos);
						break;
					case TILE_STONE:
						if(game->level.worldID != WORLD_FOUR) {
							push_movables(&root[STACK_STONES], x_pos, y_pos);
						}
						break;
					case TILE_DIAMOND:
						push_movables(&root[STACK_DIAMONDS], x_pos, y_pos);
						break;
					case TILE_SPIDER:
						push_movables(&root[STACK_SPIDERS], x_pos, y_pos);
						break;
					case TILE_MONSTER:
						push_movables(&root[STACK_MONSTERS], x_pos, y_pos);
						break;
					case TILE_CONVERTER:
						push_movables(&root[STACK_CONVERTER], x_pos, y_pos);
						break;
					case TILE_STAR:
						push_movables(&root[STACK_STARS], x_pos, y_pos);
						break;
					case TILE_LITTLE_DIAMOND:
						push_movables(&root[STACK_LITTLE_DIAMONDS], x_pos, y_pos);
						break;
					case TILE_GATE:
						push_movables(&root[STACK_GATE], x_pos, y_pos);
						break;
					case TILE_BACKGROUND:
						if(game->level.worldID != WORLD_ZERO && game->level.worldID != WORLD_ONE) {
							push_movables(&root[STACK_BACKGROUND], x_pos, y_pos);
						}
						break;
					case TILE_DIRT:
						if(game->level.worldID == WORLD_TWO || game->level.worldID == WORLD_FOUR || game->level.worldID == WORLD_FIVE) {
							push_movables(&root[STACK_DIRT], x_pos, y_pos);
						}
						break;
					default:
						break;
				}
			}
		}

		late_update_stars(root[STACK_STARS], game->map.tile_map, &(game->time.timer_start));
		late_update_character(root[STACK_CHARACTER], game);
		if(game->level.stop_others == FALSE) {
		
			late_update_stones(root[STACK_STONES], game->map.tile_map, &(game->time.timer_start));
			late_update_converter(root[STACK_CONVERTER], game->map.tile_map, &(game->time.timer_start));
			late_update_diamonds(root[STACK_DIAMONDS], game->map.tile_map, &(game->time.timer_start));
			late_update_spiders(root[STACK_SPIDERS], game->map.tile_map, &(game->map.info_tile_map), game->audio.sfx, game->audio.vol_sfx, &game->player, &(game->time.timer_start));
			late_update_monsters(root[STACK_MONSTERS], game->map.tile_map, &(game->map.info_tile_map), game->audio.sfx, game->audio.vol_sfx, &game->player, &(game->time.timer_start));
			late_update_little_diamonds(root[STACK_LITTLE_DIAMONDS], game->map.tile_map, &(game->time.timer_start));
			late_update_gate(root[STACK_GATE], game->map.tile_map, &(game->time.timer_start));
			late_update_background(root[STACK_BACKGROUND], game->map.tile_map, &(game->time.timer_start));
			late_update_dirt(root[STACK_DIRT], game->map.tile_map, &(game->time.timer_start));
		}
		else {
			free_anim_stack(root);
		}
	}
}

void late_update_character(StackMovables *root, Game *const game) {

	int y_move, x_move;
	DeathType death_type;

	while(root != NULL) {
		if(game->level.gate.is_player_there == FALSE) {
			if(game->map.tile_map[root->y_pos][root->x_pos].is_dead == FALSE) {

				switch(game->map.tile_map[root->y_pos][root->x_pos].movement) {
					/*animate movement frames*/
					case MOVE_UP:
						find_frame(&(game->map.tile_map[root->y_pos][root->x_pos].src_rect), game->map.tile_map[root->y_pos][root->x_pos].anim.frame,
										ANIM_CHAR_MOVE_UP);

						go_next_frame(&(game->map.tile_map[root->y_pos][root->x_pos].anim.frame), &(game->map.tile_map[root->y_pos][root->x_pos].anim.frame_time),
										ANIM_CHAR_MOVE_UP_TOTAL_FRAME, 0.0416, &(game->time.timer_start));
						break;
					case MOVE_RIGHT:
						find_frame(&(game->map.tile_map[root->y_pos][root->x_pos].src_rect), game->map.tile_map[root->y_pos][root->x_pos].anim.frame,
										ANIM_CHAR_MOVE_RIGHT);

						go_next_frame(&(game->map.tile_map[root->y_pos][root->x_pos].anim.frame), &(game->map.tile_map[root->y_pos][root->x_pos].anim.frame_time),
										ANIM_CHAR_MOVE_RIGHT_TOTAL_FRAME, 0.0416, &(game->time.timer_start));
						break;
					case MOVE_DOWN:
						find_frame(&(game->map.tile_map[root->y_pos][root->x_pos].src_rect), game->map.tile_map[root->y_pos][root->x_pos].anim.frame,
										ANIM_CHAR_MOVE_DOWN);

						go_next_frame(&(game->map.tile_map[root->y_pos][root->x_pos].anim.frame), &(game->map.tile_map[root->y_pos][root->x_pos].anim.frame_time),
										ANIM_CHAR_MOVE_DOWN_TOTAL_FRAME, 0.0416, &(game->time.timer_start));
						break;
					case MOVE_LEFT:
						find_frame(&(game->map.tile_map[root->y_pos][root->x_pos].src_rect), game->map.tile_map[root->y_pos][root->x_pos].anim.frame,
										ANIM_CHAR_MOVE_LEFT);

						go_next_frame(&(game->map.tile_map[root->y_pos][root->x_pos].anim.frame), &(game->map.tile_map[root->y_pos][root->x_pos].anim.frame_time),
										ANIM_CHAR_MOVE_LEFT_TOTAL_FRAME, 0.0416, &(game->time.timer_start));
						break;
					case MOVE_WAIT:
						find_frame(&(game->map.tile_map[root->y_pos][root->x_pos].src_rect), game->map.tile_map[root->y_pos][root->x_pos].anim.frame,
										ANIM_CHAR_MOVE_WAIT);

						go_next_frame(&(game->map.tile_map[root->y_pos][root->x_pos].anim.frame), &(game->map.tile_map[root->y_pos][root->x_pos].anim.frame_time),
										ANIM_CHAR_MOVE_WAIT_TOTAL_FRAME, 0.20, &(game->time.timer_start));
					default:
						break;
				}
			}
			else if(game->map.tile_map[root->y_pos][root->x_pos].destroy == FALSE) {
				if(game->map.tile_map[root->y_pos][root->x_pos].is_movable == TRUE) {

					death_type = game->map.tile_map[root->y_pos][root->x_pos].death_type;

					if(game->map.tile_map[root->y_pos][root->x_pos].anim.frame_time == 0.0) {

						Mix_HaltChannel(-1);
						play_chunk(game->audio.sfx[AUDIO_SFX_LEVEL_LOSE].chunk, game->audio.sfx[AUDIO_SFX_LEVEL_LOSE].channel, 0);
						set_chunk_volume(game->audio.sfx[AUDIO_SFX_LEVEL_LOSE].chunk, game->audio.vol_sfx);

						if(game->map.tile_map[root->y_pos][root->x_pos].death_type == DTYPE_WATER) {
							game->level.water.flow_time = 0.5;
							game->level.water.flow_time_extra = 0;
						}
						for(y_move = -1; y_move < 2; ++y_move) {
							if(root->y_pos + y_move >= 0 && root->y_pos + y_move < game->map.info_tile_map.height) {
								
								for(x_move = -1; x_move < 2; ++x_move) {
									if(root->x_pos + x_move >= 0 && root->x_pos + x_move < game->map.info_tile_map.width) {
										if(x_move != 0 || y_move != 0) {
											switch(death_type) {
												case DTYPE_SOLID:
													if(game->map.tile_map[root->y_pos + y_move][root->x_pos + x_move].tile != TILE_STONE &&
														game->map.tile_map[root->y_pos + y_move][root->x_pos + x_move].tile != TILE_DIAMOND) {
														convert_tile(&(game->map.tile_map[root->y_pos + y_move][root->x_pos + x_move]), TILE_STAR);
													}
													break;
												case DTYPE_WATER:
													if(game->map.tile_map[root->y_pos + y_move][root->x_pos + x_move].tile != TILE_WATER) {
														convert_tile(&(game->map.tile_map[root->y_pos + y_move][root->x_pos + x_move]), TILE_STAR);
													}
													break;
												case DTYPE_FOE:
													if(game->map.tile_map[root->y_pos + y_move][root->x_pos + x_move].tile != TILE_MONSTER &&
														game->map.tile_map[root->y_pos + y_move][root->x_pos + x_move].tile != TILE_SPIDER) {
														convert_tile(&(game->map.tile_map[root->y_pos + y_move][root->x_pos + x_move]), TILE_STAR);
													}
													break;
												default:
													convert_tile(&(game->map.tile_map[root->y_pos + y_move][root->x_pos + x_move]), TILE_STAR);
													break;
											}
										}
									}
								}
							}
						}
					}

					switch(death_type) {
						case DTYPE_FOE:
							
							find_frame(&(game->map.tile_map[root->y_pos][root->x_pos].src_rect), game->map.tile_map[root->y_pos][root->x_pos].anim.frame,
									ANIM_CHAR_DEATH_FOE);

							go_next_frame(&(game->map.tile_map[root->y_pos][root->x_pos].anim.frame), &(game->map.tile_map[root->y_pos][root->x_pos].anim.frame_time),
									ANIM_CHAR_DEATH_FOE_TOTAL_FRAME, 0.7, &(game->time.timer_start));
							
							break;

						case DTYPE_SOLID:

							find_frame(&(game->map.tile_map[root->y_pos][root->x_pos].src_rect), game->map.tile_map[root->y_pos][root->x_pos].anim.frame,
									ANIM_CHAR_DEATH_SOLID);

							go_next_frame(&(game->map.tile_map[root->y_pos][root->x_pos].anim.frame), &(game->map.tile_map[root->y_pos][root->x_pos].anim.frame_time),
									ANIM_CHAR_DEATH_SOLID_TOTAL_FRAME, 0.7, &(game->time.timer_start));
							break;

						case DTYPE_WATER:
						case DTYPE_JAMMING:
						case DTYPE_TIME:

							find_frame(&(game->map.tile_map[root->y_pos][root->x_pos].src_rect), game->map.tile_map[root->y_pos][root->x_pos].anim.frame,
									ANIM_CHAR_DEATH_JAMMING);

							go_next_frame(&(game->map.tile_map[root->y_pos][root->x_pos].anim.frame), &(game->map.tile_map[root->y_pos][root->x_pos].anim.frame_time),
									ANIM_CHAR_DEATH_JAMMING_TOTAL_FRAME, 0.7, &(game->time.timer_start));
							break;

						default:
							break;
					}

					if(game->map.tile_map[root->y_pos][root->x_pos].anim.frame_time == 0.0) {
						game->map.tile_map[root->y_pos][root->x_pos].destroy = TRUE;
					}
				}
			}
			else if(game->map.tile_map[root->y_pos][root->x_pos].destroy == TRUE) {
				if(game->level.is_faded == FALSE || game->video.effects.fade.state != FADE_STATE_NO_FADE) {
					if(game->level.is_faded == FALSE) {
						game->video.effects.fade.state = FADE_STATE_FADING_OUT;
						game->video.effects.fade.alpha = 255;
						game->video.effects.fade.fade_time = DEFAULT_FADE_TIME;
						game->video.effects.fade.full_cycle = FALSE;
					}
					game->level.is_faded = TRUE;
				}
				else {
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
				}
			}
		}
		else if(game->level.is_passed == FALSE) {
			if(game->map.tile_map[root->y_pos][root->x_pos].is_movable == TRUE) {
				
				if(game->map.tile_map[root->y_pos][root->x_pos].anim.frame_time == 0.0) {
					Mix_HaltChannel(-1);
					play_chunk(game->audio.sfx[AUDIO_SFX_LEVEL_WIN].chunk, game->audio.sfx[AUDIO_SFX_LEVEL_WIN].channel, 0);
					set_chunk_volume(game->audio.sfx[AUDIO_SFX_LEVEL_WIN].chunk, game->audio.vol_sfx);
				}

				find_frame(&(game->map.tile_map[root->y_pos][root->x_pos].src_rect), game->map.tile_map[root->y_pos][root->x_pos].anim.frame,
									ANIM_CHAR_WIN_GATE);

				go_next_frame(&(game->map.tile_map[root->y_pos][root->x_pos].anim.frame), &(game->map.tile_map[root->y_pos][root->x_pos].anim.frame_time),
									ANIM_CHAR_WIN_GATE_TOTAL_FRAME, 0.4, &(game->time.timer_start));

				if(game->map.tile_map[root->y_pos][root->x_pos].anim.frame_time == 0.0) {
					game->level.is_passed = TRUE;
				}
			}
		}
		pop_movables(&root);
	}
}

void late_update_stones(StackMovables *root, TileMap **const map, const struct timespec *const timer_start) {

	while(root != NULL) {
		if(map[root->y_pos][root->x_pos].is_dead == FALSE) {
			if(map[root->y_pos][root->x_pos].is_movable == FALSE) {
			
				find_frame(&map[root->y_pos][root->x_pos].src_rect, map[root->y_pos][root->x_pos].anim.frame,
								ANIM_STONE_MOVE_WAIT);			

			}
			else {

				find_frame(&map[root->y_pos][root->x_pos].src_rect, map[root->y_pos][root->x_pos].anim.frame,
								ANIM_STONE_MOVE_WAIT);

				go_next_frame(&map[root->y_pos][root->x_pos].anim.frame, &map[root->y_pos][root->x_pos].anim.frame_time,
								ANIM_STONE_MOVE_WAIT_TOTAL_FRAME, 0.15, timer_start);
			}
		}
		pop_movables(&root);
	}
}

void late_update_diamonds(StackMovables *root, TileMap **const map, const struct timespec *const timer_start) {

	while(root != NULL) {
		if(map[root->y_pos][root->x_pos].is_dead == FALSE) {
			find_frame(&map[root->y_pos][root->x_pos].src_rect, map[root->y_pos][root->x_pos].anim.frame,
							ANIM_DIAMOND_MOVE_WAIT);
			
			go_next_frame(&map[root->y_pos][root->x_pos].anim.frame, &map[root->y_pos][root->x_pos].anim.frame_time,
							ANIM_DIAMOND_MOVE_WAIT_TOTAL_FRAME, 0.15, timer_start);
		}
		else if(map[root->y_pos][root->x_pos].destroy == FALSE) {
			if(map[root->y_pos][root->x_pos].anim.frame == 10/*ANIM_CHAR_DEATH_FRAME_COUNT*/) {
				map[root->y_pos][root->x_pos].destroy = TRUE;
			}
			else {
				/*animate death frames*/
			}
		}
		pop_movables(&root);
	}
}

void late_update_converter(StackMovables *root, TileMap **const map, const struct timespec *const timer_start) {

	while(root != NULL) {
		
		find_frame(&map[root->y_pos][root->x_pos].src_rect, map[root->y_pos][root->x_pos].anim.frame,
						ANIM_CONVERTER_MOVE_WAIT);
			
		go_next_frame(&map[root->y_pos][root->x_pos].anim.frame, &map[root->y_pos][root->x_pos].anim.frame_time,
						ANIM_CONVERTER_MOVE_WAIT_TOTAL_FRAME, 0.1, timer_start);
		pop_movables(&root);
	}
}

void late_update_spiders(StackMovables *root, TileMap **const map, const TileMapInfo *const info_map,
								const SFX *const sfx, const Uint8 vol, Player *const player, const struct timespec *const timer_start) {

	int y_move, x_move;

	while(root != NULL) {
		if(map[root->y_pos][root->x_pos].is_dead == FALSE) {
			find_frame(&map[root->y_pos][root->x_pos].src_rect, map[root->y_pos][root->x_pos].anim.frame,
							ANIM_SPIDER_MOVE_WAIT);
			
			go_next_frame(&map[root->y_pos][root->x_pos].anim.frame, &map[root->y_pos][root->x_pos].anim.frame_time,
							ANIM_SPIDER_MOVE_WAIT_TOTAL_FRAME, 0.2, timer_start);
		}
		else if(map[root->y_pos][root->x_pos].is_movable == TRUE) {
			
			player->score.point += SCORE_SPIDER;

			for(y_move = -1; y_move < 2; ++y_move) {
				if(root->y_pos + y_move >= 0 && root->y_pos + y_move < info_map->height) {
					
					for(x_move = -1; x_move < 2; ++x_move) {
						if(root->x_pos + x_move >= 0 && root->x_pos + x_move < info_map->width) {
							if(x_move != 0 || y_move != 0) {
								if(map[root->y_pos + y_move][root->x_pos + x_move].tile == TILE_DIRT) {
									play_chunk(sfx[AUDIO_SFX_DIAMOND_CREATED].chunk, sfx[AUDIO_SFX_DIAMOND_CREATED].channel, 0);
									set_chunk_volume(sfx[AUDIO_SFX_DIAMOND_CREATED].chunk, vol);
									convert_tile(&map[root->y_pos + y_move][root->x_pos + x_move], TILE_LITTLE_DIAMOND);
								}
							}
							else {
								convert_tile(&map[root->y_pos + y_move][root->x_pos + x_move], TILE_BACKGROUND);
							}
						}
					}
				}
			}
		}
		pop_movables(&root);
	}
}

void late_update_monsters(StackMovables *root, TileMap **const map, const TileMapInfo *const info_map,
								const SFX *const sfx, const Uint8 vol, Player *const player, const struct timespec *const timer_start) {

	int y_move, x_move;

	while(root != NULL) {
		if(map[root->y_pos][root->x_pos].is_dead == FALSE) {
			find_frame(&map[root->y_pos][root->x_pos].src_rect, map[root->y_pos][root->x_pos].anim.frame,
							ANIM_MONSTER_MOVE_WAIT);
			
			go_next_frame(&map[root->y_pos][root->x_pos].anim.frame, &map[root->y_pos][root->x_pos].anim.frame_time,
							ANIM_MONSTER_MOVE_WAIT_TOTAL_FRAME, 0.1, timer_start);
		}
		else if(map[root->y_pos][root->x_pos].is_movable == TRUE) {
			
			player->score.point += SCORE_MONSTER;

			for(y_move = -1; y_move < 2; ++y_move) {
				if(root->y_pos + y_move >= 0 && root->y_pos + y_move < info_map->height) {
					
					for(x_move = -1; x_move < 2; ++x_move) {
						if(root->x_pos + x_move >= 0 && root->x_pos + x_move < info_map->width) {
							if(x_move != 0 || y_move != 0) {
								if(map[root->y_pos + y_move][root->x_pos + x_move].tile == TILE_DIRT) {
									play_chunk(sfx[AUDIO_SFX_DIAMOND_CREATED].chunk, sfx[AUDIO_SFX_DIAMOND_CREATED].channel, 0);
									set_chunk_volume(sfx[AUDIO_SFX_DIAMOND_CREATED].chunk, vol);
									convert_tile(&map[root->y_pos + y_move][root->x_pos + x_move], TILE_LITTLE_DIAMOND);
								}
							}
							else {
								play_chunk(sfx[AUDIO_SFX_DIAMOND_CREATED].chunk, sfx[AUDIO_SFX_DIAMOND_CREATED].channel, 0);
								set_chunk_volume(sfx[AUDIO_SFX_DIAMOND_CREATED].chunk, vol);
								convert_tile(&map[root->y_pos + y_move][root->x_pos + x_move], TILE_BACKGROUND);
							}
						}
					}

					if(root->y_pos - 2 >= 0) {
						if(map[root->y_pos - 2][root->x_pos].tile == TILE_DIRT) {
							play_chunk(sfx[AUDIO_SFX_DIAMOND_CREATED].chunk, sfx[AUDIO_SFX_DIAMOND_CREATED].channel, 0);
							set_chunk_volume(sfx[AUDIO_SFX_DIAMOND_CREATED].chunk, vol);
							convert_tile(&map[root->y_pos - 2][root->x_pos], TILE_LITTLE_DIAMOND);
						}
					}

					if(root->x_pos + 2 < info_map->width) {
						if(map[root->y_pos][root->x_pos + 2].tile == TILE_DIRT) {
							play_chunk(sfx[AUDIO_SFX_DIAMOND_CREATED].chunk, sfx[AUDIO_SFX_DIAMOND_CREATED].channel, 0);
							set_chunk_volume(sfx[AUDIO_SFX_DIAMOND_CREATED].chunk, vol);
							convert_tile(&map[root->y_pos][root->x_pos + 2], TILE_LITTLE_DIAMOND);
						}
					}

					if(root->y_pos + 2 < info_map->height) {
						if(map[root->y_pos + 2][root->x_pos].tile == TILE_DIRT) {
							play_chunk(sfx[AUDIO_SFX_DIAMOND_CREATED].chunk, sfx[AUDIO_SFX_DIAMOND_CREATED].channel, 0);
							set_chunk_volume(sfx[AUDIO_SFX_DIAMOND_CREATED].chunk, vol);
							convert_tile(&map[root->y_pos + 2][root->x_pos], TILE_LITTLE_DIAMOND);
						}
					}

					if(root->x_pos - 2 >= 0) {
						if(map[root->y_pos][root->x_pos - 2].tile == TILE_DIRT) {
							play_chunk(sfx[AUDIO_SFX_DIAMOND_CREATED].chunk, sfx[AUDIO_SFX_DIAMOND_CREATED].channel, 0);
							set_chunk_volume(sfx[AUDIO_SFX_DIAMOND_CREATED].chunk, vol);
							convert_tile(&map[root->y_pos][root->x_pos - 2], TILE_LITTLE_DIAMOND);
						}
					}
				}
			}
		}
		pop_movables(&root);
	}
}

void late_update_little_diamonds(StackMovables *root, TileMap **const map, const struct timespec *const timer_start) {

	while(root != NULL) {
		if(map[root->y_pos][root->x_pos].is_dead == FALSE) {
			find_frame(&map[root->y_pos][root->x_pos].src_rect, map[root->y_pos][root->x_pos].anim.frame,
							ANIM_LITTLE_DIAMOND_MOVE_WAIT);
			
			go_next_frame(&map[root->y_pos][root->x_pos].anim.frame, &map[root->y_pos][root->x_pos].anim.frame_time,
							ANIM_LITTLE_DIAMOND_MOVE_WAIT_TOTAL_FRAME, 0.1, timer_start);

			if(map[root->y_pos][root->x_pos].anim.frame_time == 0.0) {
				map[root->y_pos][root->x_pos].is_dead = TRUE;
			}
		}
		else {
			convert_tile(&map[root->y_pos][root->x_pos], TILE_DIAMOND);
		}
		pop_movables(&root);
	}
}

void late_update_stars(StackMovables *root, TileMap **const map, const struct timespec *const timer_start) {

	while(root != NULL) {
		if(map[root->y_pos][root->x_pos].is_dead == FALSE) {
			find_frame(&map[root->y_pos][root->x_pos].src_rect, map[root->y_pos][root->x_pos].anim.frame,
							ANIM_STAR_MOVE_WAIT);
			
			go_next_frame(&map[root->y_pos][root->x_pos].anim.frame, &map[root->y_pos][root->x_pos].anim.frame_time,
							ANIM_STAR_MOVE_WAIT_TOTAL_FRAME, 0.13, timer_start);
		}
		pop_movables(&root);
	}
}

void late_update_gate(StackMovables *root, TileMap **const map, const struct timespec *const timer_start) {

	while(root != NULL) {
		if(map[root->y_pos][root->x_pos].is_dead == FALSE) {
			find_frame(&map[root->y_pos][root->x_pos].src_rect, map[root->y_pos][root->x_pos].anim.frame,
							ANIM_GATE_MOVE_WAIT);
			
			go_next_frame(&map[root->y_pos][root->x_pos].anim.frame, &map[root->y_pos][root->x_pos].anim.frame_time,
							ANIM_GATE_MOVE_WAIT_TOTAL_FRAME, 0.17, timer_start);
		}
		else if(map[root->y_pos][root->x_pos].destroy == FALSE) {
			
		}
		pop_movables(&root);
	}
}

void late_update_background(StackMovables *root, TileMap **const map, const struct timespec *const timer_start) {

	while(root != NULL) {

		find_frame(&map[root->y_pos][root->x_pos].src_rect, map[root->y_pos][root->x_pos].anim.frame,
						ANIM_BACKGROUND_MOVE_WAIT);

		go_next_frame(&map[root->y_pos][root->x_pos].anim.frame, &map[root->y_pos][root->x_pos].anim.frame_time,
						ANIM_BACKGROUND_MOVE_WAIT_TOTAL_FRAME, 0.1, timer_start);

		pop_movables(&root);
	}
}

void late_update_dirt(StackMovables *root, TileMap **const map, const struct timespec *const timer_start) {

	while(root != NULL) {

		find_frame(&map[root->y_pos][root->x_pos].src_rect, map[root->y_pos][root->x_pos].anim.frame,
						ANIM_DIRT_MOVE_WAIT);

		go_next_frame(&map[root->y_pos][root->x_pos].anim.frame, &map[root->y_pos][root->x_pos].anim.frame_time,
						ANIM_DIRT_MOVE_WAIT_TOTAL_FRAME, 0.1, timer_start);

		pop_movables(&root);
	}
}

void find_frame(SDL_Rect *const src_rect, const int frame, const int first_frame) {

	src_rect->x = (first_frame % 10) * TILE_WIDTH;
	src_rect->y = ((first_frame + frame * 10) / 10) * TILE_HEIGHT;
	src_rect->w = TILE_WIDTH;
	src_rect->h = TILE_HEIGHT; 
}

void go_next_frame(int *const frame, double *const frame_time,
					const int total_frame, const double next_frame_time, const struct timespec *const timer_start) {

	struct timespec timer_current;
	
	clock_gettime(CLOCK_MONOTONIC, &timer_current);

	*frame_time += get_time_seconds(timer_start, &timer_current);

	if(*frame_time >= next_frame_time + ((*frame) * next_frame_time)) {
		if(*frame + 1 >= total_frame) {
			*frame = 0;
			*frame_time = 0.0;
		}
		else {
			*frame = (*frame) + 1;
		}
	}
}

void free_anim_stack(StackMovables **root) {

	while(root[STACK_STONES] != NULL) {
		pop_movables(&root[STACK_STONES]);
	}

	while(root[STACK_CONVERTER] != NULL) {
		pop_movables(&root[STACK_CONVERTER]);
	}

	while(root[STACK_DIAMONDS] != NULL) {
		pop_movables(&root[STACK_DIAMONDS]);
	}

	while(root[STACK_SPIDERS] != NULL) {
		pop_movables(&root[STACK_SPIDERS]);
	}

	while(root[STACK_MONSTERS] != NULL) {
		pop_movables(&root[STACK_MONSTERS]);
	}

	while(root[STACK_LITTLE_DIAMONDS] != NULL) {
		pop_movables(&root[STACK_LITTLE_DIAMONDS]);
	}

	while(root[STACK_GATE] != NULL) {
		pop_movables(&root[STACK_GATE]);
	}

	while(root[STACK_BACKGROUND] != NULL) {
		pop_movables(&root[STACK_BACKGROUND]);
	}

	while(root[STACK_DIRT] != NULL) {
		pop_movables(&root[STACK_DIRT]);
	}	
}
