#include <RPS/BD.h>

void init_level(Level *const level) {

	int i;

	level->levelID = LEVEL_ZERO;

	level->is_unlocked[LEVEL_ZERO] = TRUE;

	level->is_level_screen_open = TRUE;

	for(i = 1; i < LEVEL_COUNT; ++i) {
		level->is_unlocked[i] = FALSE;
	}
}

void load_level(Game *const game) {

	if(game->map.tile_map == NULL) {
		reset_level(game);
	}
	
	load_textures(game);
}

void handle_level(Game *const game) {

	int i;

	/*the reason there is a time precision offset(1) is since time is double precision and the time user sees at hud is int precision,
		when time goes 0.00001 below of 1 user sees 0 at the hud but program acts when time goes below 0.0, to synchronize what user sees
			and the events in-game there is a precision offset*/ 
	
	if(game->map.tile_map != NULL) {
		if(game->player.object->is_dead == FALSE && game->level.gate.is_player_there == FALSE) {

			decrease_time(&(game->level.time), game->time.delta_time);

			if(game->level.time <= 0.0 + TIME_PRECISION_OFFSET && game->player.object->is_dead == FALSE) {
				game->player.object->is_dead = TRUE;
				game->player.object->death_type = DTYPE_TIME;
				game->level.stop_others = TRUE;
				handle_anim(&(game->player.object->anim), game->player.object->tile);
			}

			if(game->level.time_state == TIME_STATE_FIRST_PERCENT) {
				if(game->level.time < (int)(game->level.total_time * 0.3) + TIME_PRECISION_OFFSET) {
					increase_rythm(game->audio.music, game->level.levelID, game->audio.vol_music);
					game->level.time_state = TIME_STATE_SECOND_PERCENT;
				}
			}
			else if(game->level.time_state == TIME_STATE_SECOND_PERCENT) {
				if(game->level.time < (int)(game->level.total_time * 0.2) + TIME_PRECISION_OFFSET) {
					increase_rythm(game->audio.music, game->level.levelID, game->audio.vol_music);
					game->level.time_state = TIME_STATE_THIRD_PERCENT;
				}
			}
			else if(game->level.time_state == TIME_STATE_THIRD_PERCENT) {
				if(game->level.time < (int)(game->level.total_time * 0.1) + TIME_PRECISION_OFFSET) {
					increase_rythm(game->audio.music, game->level.levelID, game->audio.vol_music);
					game->level.time_state = TIME_STATE_LAST_PERCENT;
				}
			}
		}
	}

	if(game->level.is_passed == TRUE) {
		
		if(game->level.time >= 1.0) {
			if(Mix_Playing(game->audio.sfx[AUDIO_SFX_LEVEL_WIN].channel) == 0) {
				game->level.time -= 1.0;
				game->player.score.point += SCORE_TIME;
				if(Mix_Playing(game->audio.sfx[AUDIO_SFX_DIAMOND_PICK].channel) == 0) {
					play_chunk(game->audio.sfx[AUDIO_SFX_DIAMOND_PICK].chunk, game->audio.sfx[AUDIO_SFX_DIAMOND_PICK].channel, 0);
					set_chunk_volume(game->audio.sfx[AUDIO_SFX_DIAMOND_PICK].chunk, game->audio.vol_sfx);
				}
				SDL_Delay(10);
			}
		}
		else if(game->level.is_faded == FALSE) {

			game->level.is_faded = TRUE;
			game->video.effects.fade.state = FADE_STATE_FADING_OUT;
			game->video.effects.fade.alpha = 255;
			game->video.effects.fade.fade_time = DEFAULT_FADE_TIME;
			game->video.effects.fade.full_cycle = FALSE;
		}
		else if(game->video.effects.fade.state == FADE_STATE_NO_FADE) {

			if(game->settings.dev_mode.is_on == FALSE) {
				++(game->level.levelID);

				if(game->level.levelID > 0) {
					if(game->level.is_unlocked[game->level.levelID - 1] == TRUE) {	/*protects dev mode glitch*/
						if(game->level.levelID >= LEVEL_COUNT) {
							game->end = TRUE;
							game->win = TRUE;
						}
						else {
							game->level.is_unlocked[game->level.levelID] = TRUE;
							game->level.is_level_screen_open = TRUE;
						}
					}
					else {
						for(i = 0; i < LEVEL_COUNT; ++i) {
							if(game->level.is_unlocked[i] == TRUE) {
								game->level.levelID = i;
							}
						}

						game->level.is_level_screen_open = TRUE;
					}
				}
				else {
					game->level.is_unlocked[game->level.levelID] = TRUE;
					game->level.is_level_screen_open = TRUE;
				}

				/*if player has 1 right of life give it to player at only level six(LEVEL_FIVE), this is about game mode*/
				if(game->player.right_of_lives >= 2) {
					if(game->level.levelID == LEVEL_TWO || game->level.levelID == LEVEL_FIVE) {
						--(game->player.right_of_lives);
						++(game->player.lives);
						play_chunk(game->audio.sfx[AUDIO_SFX_LIFE_UP].chunk, game->audio.sfx[AUDIO_SFX_LIFE_UP].channel, 0);
						set_chunk_volume(game->audio.sfx[AUDIO_SFX_LIFE_UP].chunk, game->audio.vol_sfx);
					}
				}
				else if(game->player.right_of_lives > 0) {
					if(game->level.levelID == LEVEL_FIVE) {
						--(game->player.right_of_lives);
						++(game->player.lives);
						play_chunk(game->audio.sfx[AUDIO_SFX_LIFE_UP].chunk, game->audio.sfx[AUDIO_SFX_LIFE_UP].channel, 0);
						set_chunk_volume(game->audio.sfx[AUDIO_SFX_LIFE_UP].chunk, game->audio.vol_sfx);
					}
				}
			}
			else {
				game->level.is_level_screen_open = TRUE;
			}

			free_map(&(game->map.tile_map), &(game->map.info_tile_map));
			free_camera(&(game->screen.camera));
		}
	}
}

void reset_level(Game *const game) {

	bool is_player_continues = TRUE;

	if(game->level.is_level_screen_open) {
		free_textures(game->video.textures.map, TEXTURE_MAP_COUNT);
		is_player_continues = open_level_screen(game);
		game->level.is_level_screen_open = FALSE;
	}

	if(is_player_continues) {
		get_level(&(game->level));
		game->map.tile_map = load_map(&(game->map.info_tile_map), game->level.levelID, &(game->level.total_diamonds));
		get_gate(&(game->level));
		set_camera_focus_multiplier(&game->screen.camera, game->level.levelID);
		init_camera(&(game->screen.camera), game->map.tile_map, &(game->map.info_tile_map));
		game->player.object = game->screen.camera.object;
		game->audio.music[game->level.levelID].rythm = RYTHM_ORIGINAL;
		Mix_HaltChannel(game->audio.music[game->level.levelID].channel);
		play_chunk(game->audio.music[game->level.levelID].chunk[game->audio.music[game->level.levelID].rythm], game->audio.music[game->level.levelID].channel, -1);
		set_chunk_volume(game->audio.music[game->level.levelID].chunk[game->audio.music[game->level.levelID].rythm], game->audio.vol_music);
		Mix_Pause(game->audio.music[game->level.levelID].channel);

		if(game->video.effects.fade.state == FADE_STATE_NO_FADE) {
			set_effect_fade_in(&game->video.effects.fade);
		}
	}
	else {
		game->is_running = FALSE;
	}
}

void get_level(Level *const level) {

	switch(level->levelID) {
		case LEVEL_ZERO:
			level->is_passed = FALSE;
			level->total_diamonds = 0;
			level->stop_others = FALSE;
			level->time = 120.0 + TIME_PRECISION_OFFSET;	/*reason for precision is here because the first two frames by user can't recognizable*/
			level->total_time = 120;
			level->time_state = TIME_STATE_FIRST_PERCENT;
			level->water.time = 0.0;
			level->water.last_time = 0.0;
			level->water.flow_time = 10;
			level->is_faded = FALSE;
			level->worldID = WORLD_ZERO;
			level->color_key = get_color_key(level->worldID);
			break;

		case LEVEL_ONE:
			level->is_passed = FALSE;
			level->total_diamonds = 0;
			level->stop_others = FALSE;
			level->time = 180.0 + TIME_PRECISION_OFFSET;
			level->total_time = 180;
			level->time_state = TIME_STATE_FIRST_PERCENT;
			level->water.time = 0.0;
			level->water.last_time = 0.0;
			level->water.flow_time = 10;
			level->is_faded = FALSE;
			level->worldID = WORLD_ONE;
			level->color_key = get_color_key(level->worldID);
			break;
		
		case LEVEL_TWO:
			level->is_passed = FALSE;
			level->total_diamonds = 0;
			level->stop_others = FALSE;
			level->time = 180.0 + TIME_PRECISION_OFFSET;
			level->total_time = 180;
			level->time_state = TIME_STATE_FIRST_PERCENT;
			level->water.time = 0.0;
			level->water.last_time = 0.0;
			level->water.flow_time = 10;
			level->is_faded = FALSE;
			level->worldID = WORLD_TWO;
			level->color_key = get_color_key(level->worldID);
			break;

		case LEVEL_THREE:
			level->is_passed = FALSE;
			level->total_diamonds = 0;
			level->stop_others = FALSE;
			level->time = 120.0 + TIME_PRECISION_OFFSET;
			level->total_time = 120;
			level->time_state = TIME_STATE_FIRST_PERCENT;
			level->water.time = 0.0;
			level->water.last_time = 0.0;
			level->water.flow_time = 10;
			level->is_faded = FALSE;
			level->worldID = WORLD_TWO;
			level->color_key = get_color_key(level->worldID);
			break;

		case LEVEL_FOUR:
			level->is_passed = FALSE;
			level->total_diamonds = 0;
			level->stop_others = FALSE;
			level->time = 45.0 + TIME_PRECISION_OFFSET;
			level->total_time = 45;
			level->time_state = TIME_STATE_FIRST_PERCENT;
			level->water.time = 0.0;
			level->water.last_time = 0.0;
			level->water.flow_time = 45.0 / 58.0;
			level->is_faded = FALSE;
			level->worldID = WORLD_THREE;
			level->color_key = get_color_key(level->worldID);
			break;

		case LEVEL_FIVE:
			level->is_passed = FALSE;
			level->total_diamonds = 0;
			level->stop_others = FALSE;
			level->time = 90.0 + TIME_PRECISION_OFFSET;
			level->total_time = 90;
			level->time_state = TIME_STATE_FIRST_PERCENT;
			level->water.time = 0.0;
			level->water.last_time = 0.0;
			level->water.flow_time = 0.0;
			level->is_faded = FALSE;
			level->worldID = WORLD_THREE;
			level->color_key = get_color_key(level->worldID);
			break;

		case LEVEL_SIX:
			level->is_passed = FALSE;
			level->total_diamonds = 0;
			level->stop_others = FALSE;
			level->time = 120.0 + TIME_PRECISION_OFFSET;
			level->total_time = 120;
			level->time_state = TIME_STATE_FIRST_PERCENT;
			level->water.time = 0.0;
			level->water.last_time = 0.0;
			level->water.flow_time = 10;
			level->is_faded = FALSE;
			level->worldID = WORLD_FOUR;
			level->color_key = get_color_key(level->worldID);
			break;

		case LEVEL_SEVEN:
			level->is_passed = FALSE;
			level->total_diamonds = 0;
			level->stop_others = FALSE;
			level->time = 140.0 + TIME_PRECISION_OFFSET;
			level->total_time = 140;
			level->time_state = TIME_STATE_FIRST_PERCENT;
			level->water.time = 0.0;
			level->water.last_time = 0.0;
			level->water.flow_time = 0.0;
			level->is_faded = FALSE;
			level->worldID = WORLD_FOUR;
			level->color_key = get_color_key(level->worldID);
			break;

		case LEVEL_EIGHT:
			level->is_passed = FALSE;
			level->total_diamonds = 0;
			level->stop_others = FALSE;
			level->time = 90.0 + TIME_PRECISION_OFFSET;
			level->total_time = 90;
			level->time_state = TIME_STATE_FIRST_PERCENT;
			level->water.time = 0.0;
			level->water.last_time = 0.0;
			level->water.flow_time = 3.0;
			level->is_faded = FALSE;
			level->worldID = WORLD_FIVE;
			level->color_key = get_color_key(level->worldID);
			break;

		case LEVEL_NINE:
			level->is_passed = FALSE;
			level->total_diamonds = 0;
			level->stop_others = FALSE;
			level->time = 30.0 + TIME_PRECISION_OFFSET;
			level->total_time = 30;
			level->time_state = TIME_STATE_FIRST_PERCENT;
			level->water.time = 0.0;
			level->water.last_time = 0.0;
			level->water.flow_time = 1.0;
			level->is_faded = FALSE;
			level->worldID = WORLD_FIVE;
			level->color_key = get_color_key(level->worldID);
			break;

		default:
			break;
	}
}

void get_gate(Level *const level) {

	switch(level->levelID) {
		case LEVEL_ZERO:
			level->gate.is_open = FALSE;
			level->gate.pos.x = 2;
			level->gate.pos.y = 9;
			level->gate.is_player_there = FALSE;
			level->gate.diamonds_to_open = (int)(level->total_diamonds / 3);
			break;

		case LEVEL_ONE:
			level->gate.is_open = FALSE;
			level->gate.pos.x = 11;
			level->gate.pos.y = 9;
			level->gate.is_player_there = FALSE;
			level->gate.diamonds_to_open = 36;
			break;
		case LEVEL_TWO:
			level->gate.is_open = FALSE;
			level->gate.pos.x = 17;
			level->gate.pos.y = 26;
			level->gate.is_player_there = FALSE;
			level->gate.diamonds_to_open = 40;
			break;
		case LEVEL_THREE:
			level->gate.is_open = FALSE;
			level->gate.pos.x = 5;
			level->gate.pos.y = 20;
			level->gate.is_player_there = FALSE;
			level->gate.diamonds_to_open = 45;
			break;
		case LEVEL_FOUR:
			level->gate.is_open = FALSE;
			level->gate.pos.x = 6;
			level->gate.pos.y = 77;
			level->gate.is_player_there = FALSE;
			level->gate.diamonds_to_open = 15;
			break;
		case LEVEL_FIVE:
			level->gate.is_open = FALSE;
			level->gate.pos.x = 10;
			level->gate.pos.y = 17;
			level->gate.is_player_there = FALSE;
			level->gate.diamonds_to_open = 25;
			break;

		case LEVEL_SIX:
			level->gate.is_open = FALSE;
			level->gate.pos.x = 67;
			level->gate.pos.y = 4;
			level->gate.is_player_there = FALSE;
			level->gate.diamonds_to_open = 24;
			break;

		case LEVEL_SEVEN:
			level->gate.is_open = FALSE;
			level->gate.pos.x = 27;
			level->gate.pos.y = 8;
			level->gate.is_player_there = FALSE;
			level->gate.diamonds_to_open = 25;
			break;

		case LEVEL_EIGHT:
			level->gate.is_open = FALSE;
			level->gate.pos.x = 9;
			level->gate.pos.y = 3;
			level->gate.is_player_there = FALSE;
			level->gate.diamonds_to_open = 20;
			break;

		case LEVEL_NINE:
			level->gate.is_open = FALSE;
			level->gate.pos.x = 19;
			level->gate.pos.y = 17;
			level->gate.is_player_there = FALSE;
			level->gate.diamonds_to_open = 10;
			break;
		default:
			break;
	}

	if(level->gate.diamonds_to_open <= 0) level->gate.diamonds_to_open = 1;
}

char* get_level_map(const LevelID levelID) {

	char *str = NULL;

	switch(levelID) {
		case LEVEL_ZERO:
			str = (char*)malloc(35 * sizeof(char));
			copy_string("Resources/Levels/level0/level0_map", str, 34);
			break;
		case LEVEL_ONE:
			str = (char*)malloc(35 * sizeof(char));
			copy_string("Resources/Levels/level1/level1_map", str, 34);
			break;
		case LEVEL_TWO:
			str = (char*)malloc(35 * sizeof(char));
			copy_string("Resources/Levels/level2/level2_map", str, 34);
			break;
		case LEVEL_THREE:
			str = (char*)malloc(35 * sizeof(char));
			copy_string("Resources/Levels/level3/level3_map", str, 34);
			break;
		case LEVEL_FOUR:
			str = (char*)malloc(35 * sizeof(char));
			copy_string("Resources/Levels/level4/level4_map", str, 34);
			break;
		case LEVEL_FIVE:
			str = (char*)malloc(35 * sizeof(char));
			copy_string("Resources/Levels/level5/level5_map", str, 34);
			break;

		case LEVEL_SIX:
			str = (char*)malloc(35 * sizeof(char));
			copy_string("Resources/Levels/level6/level6_map", str, 34);
			break;
		case LEVEL_SEVEN:
			str = (char*)malloc(35 * sizeof(char));
			copy_string("Resources/Levels/level7/level7_map", str, 34);
			break;
		case LEVEL_EIGHT:
			str = (char*)malloc(35 * sizeof(char));
			copy_string("Resources/Levels/level8/level8_map", str, 34);
			break;
		case LEVEL_NINE:
			str = (char*)malloc(35 * sizeof(char));
			copy_string("Resources/Levels/level9/level9_map", str, 34);
			break;
		default:
			break;
	}

	return str;
}

char* get_level_tileset(const LevelID levelID) {

	char *str = NULL;

	switch(levelID) {
		case LEVEL_ZERO: 
		 	str = (char*)malloc(43 * sizeof(char));
		 	copy_string("Resources/Levels/level0/level0_tileset.png", str, 42);
		 	break;
		case LEVEL_ONE:
			str = (char*)malloc(43 * sizeof(char));
		 	copy_string("Resources/Levels/level1/level1_tileset.png", str, 42);
		 	break;
		case LEVEL_TWO:
			str = (char*)malloc(43 * sizeof(char));
		 	copy_string("Resources/Levels/level2/level2_tileset.png", str, 42);
		 	break;
		case LEVEL_THREE:
			str = (char*)malloc(43 * sizeof(char));
		 	copy_string("Resources/Levels/level3/level3_tileset.png", str, 42);
		 	break;
		 case LEVEL_FOUR:
			str = (char*)malloc(43 * sizeof(char));
		 	copy_string("Resources/Levels/level4/level4_tileset.png", str, 42);
		 	break;
		case LEVEL_FIVE:
			str = (char*)malloc(43 * sizeof(char));
		 	copy_string("Resources/Levels/level5/level5_tileset.png", str, 42);
		 	break;
		 case LEVEL_SIX:
			str = (char*)malloc(43 * sizeof(char));
		 	copy_string("Resources/Levels/level6/level6_tileset.png", str, 42);
		 	break;
		 case LEVEL_SEVEN:
			str = (char*)malloc(43 * sizeof(char));
		 	copy_string("Resources/Levels/level7/level7_tileset.png", str, 42);
		 	break;
		 case LEVEL_EIGHT:
			str = (char*)malloc(43 * sizeof(char));
		 	copy_string("Resources/Levels/level8/level8_tileset.png", str, 42);
		 	break;
		 case LEVEL_NINE:
			str = (char*)malloc(43 * sizeof(char));
		 	copy_string("Resources/Levels/level9/level9_tileset.png", str, 42);
		 	break;
		default:
			break;
	}

	return str;
}

char* get_level_music(const MusicRythm rythm, const LevelID levelID) {
	
	char *str = NULL;

	switch(levelID) {
		case LEVEL_ZERO:
			switch(rythm) {
				case RYTHM_ORIGINAL: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level0/level0_music0.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_10: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level0/level0_music1.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_30: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level0/level0_music2.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_60: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level0/level0_music3.wav", str, 42);
				 	break;
				 default:
				 	break;
			 }
			 break;
		case LEVEL_ONE:
			switch(rythm) {
				case RYTHM_ORIGINAL: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level1/level1_music0.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_10: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level1/level1_music1.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_30: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level1/level1_music2.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_60: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level1/level1_music3.wav", str, 42);
				 	break;
				 default:
				 	break;
			 }
			 break;
		case LEVEL_TWO:
			switch(rythm) {
				case RYTHM_ORIGINAL: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level2/level2_music0.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_10: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level2/level2_music1.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_30: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level2/level2_music2.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_60: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level2/level2_music3.wav", str, 42);
				 	break;
				 default:
				 	break;
			 }
			 break;
		case LEVEL_THREE:
			switch(rythm) {
				case RYTHM_ORIGINAL: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level3/level3_music0.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_10: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level3/level3_music1.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_30: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level3/level3_music2.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_60: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level3/level3_music3.wav", str, 42);
				 	break;
				 default:
				 	break;
			 }
			 break;
		case LEVEL_FOUR:
			switch(rythm) {
				case RYTHM_ORIGINAL: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level4/level4_music0.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_10: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level4/level4_music1.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_30: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level4/level4_music2.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_60: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level4/level4_music3.wav", str, 42);
				 	break;
				 default:
				 	break;
			 }
			 break;
		case LEVEL_FIVE:
			switch(rythm) {
				case RYTHM_ORIGINAL: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level5/level5_music0.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_10: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level5/level5_music1.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_30: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level5/level5_music2.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_60: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level5/level5_music3.wav", str, 42);
				 	break;
				 default:
				 	break;
			 }
			 break;
		case LEVEL_SIX:
			switch(rythm) {
				case RYTHM_ORIGINAL: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level6/level6_music0.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_10: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level6/level6_music1.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_30: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level6/level6_music2.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_60: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level6/level6_music3.wav", str, 42);
				 	break;
				 default:
				 	break;
			 }
			 break;

		case LEVEL_SEVEN:
			switch(rythm) {
				case RYTHM_ORIGINAL: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level7/level7_music0.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_10: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level7/level7_music1.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_30: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level7/level7_music2.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_60: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level7/level7_music3.wav", str, 42);
				 	break;
				 default:
				 	break;
			 }
			 break;

		case LEVEL_EIGHT:
			switch(rythm) {
				case RYTHM_ORIGINAL: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level8/level8_music0.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_10: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level8/level8_music1.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_30: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level8/level8_music2.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_60: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level8/level8_music3.wav", str, 42);
				 	break;
				 default:
				 	break;
			 }
			 break;

		case LEVEL_NINE:
			switch(rythm) {
				case RYTHM_ORIGINAL: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level9/level9_music0.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_10: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level9/level9_music1.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_30: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level9/level9_music2.wav", str, 42);
				 	break;
				case RYTHM_INCREASED_60: 
				 	str = (char*)malloc(43 * sizeof(char));
				 	copy_string("Resources/Levels/level9/level9_music3.wav", str, 42);
				 	break;
				 default:
				 	break;
			 }
			 break;
		default:
			break;
	}

	return str;	
}

WorldID get_world_id(const LevelID levelID) {

	switch(levelID) {
		case LEVEL_ZERO:
			return WORLD_ZERO;
		case LEVEL_ONE:
			return WORLD_ONE;
		case LEVEL_TWO:
			return WORLD_TWO;
		case LEVEL_THREE:
			return WORLD_TWO;
		case LEVEL_FOUR:
			return WORLD_THREE;
		case LEVEL_FIVE:
			return WORLD_THREE;
		case LEVEL_SIX:
			return WORLD_FOUR;
		case LEVEL_SEVEN:
			return WORLD_FOUR;
		case LEVEL_EIGHT:
			return WORLD_FIVE;
		case LEVEL_NINE:
			return WORLD_FIVE;
		default:
			break;
	}

	return WORLD_ZERO;
}

SDL_Color get_color_key(const WorldID worldID) {

	SDL_Color color_key;

	switch(worldID) {
		case WORLD_FIVE:
			color_key.r = 107;
			color_key.g = 0;
			color_key.b = 0;
			break;
		default:
			color_key.r = 107;
			color_key.g = 109;
			color_key.b = 0;
			break;
	}

	color_key.a = 255;

	return color_key;
}

void handle_gate(Gate *const gate, TileMap **const map, SFX *sfx, const Uint8 vol) {

	if(gate->is_open == FALSE) {
		if(gate->diamonds_to_open > 0) {
			--(gate->diamonds_to_open);
		}

		if(gate->diamonds_to_open <= 0) {
			play_chunk(sfx->chunk, sfx->channel, 0);
			set_chunk_volume(sfx->chunk, vol);
			gate->is_open = TRUE;
			convert_tile(&map[gate->pos.y][gate->pos.x], TILE_GATE);
		}
	}
}

void copy_string(char *src, char *des, int length) {
	int i;

	for(i = 0; i < length; ++i) {
		des[i] = src[i];
	}
	des[i] = 0;
}
