#include <RPS/BD.h>

int load_game(SDL_Window *window, SDL_Renderer *renderer) {

	Game *game = NULL;
	bool go_next_step = FALSE;
	bool game_restart = FALSE;

	if(!window || !renderer) {
		return 1;
	}

	init_game(&game, window, renderer);

	if(game != NULL) {

		go_next_step = open_start_screen(game);

		if(go_next_step) {

			go_next_step = open_new_game_screen(game);

			if(go_next_step) {
				update_game(game);
			}
		}

		if(game->is_running && go_next_step) {
			Mix_Pause(-1);
			if(game->win) {
				play_chunk(game->audio.sfx[AUDIO_SFX_GAME_WIN].chunk, game->audio.sfx[AUDIO_SFX_GAME_WIN].channel, 0);
				set_chunk_volume(game->audio.sfx[AUDIO_SFX_GAME_WIN].chunk, game->audio.vol_sfx);
				show_text_timed_screen(game, game->video.perm_textures.textures[TEXTURE_PERM_WIN], &game->video.perm_textures.rects[RECT_PERM_DES_WIN], 3.0);
			}
			else {
				play_chunk(game->audio.sfx[AUDIO_SFX_GAME_LOSE].chunk, game->audio.sfx[AUDIO_SFX_GAME_LOSE].channel, 0);
				set_chunk_volume(game->audio.sfx[AUDIO_SFX_GAME_LOSE].chunk, game->audio.vol_sfx);
				show_text_timed_screen(game, game->video.perm_textures.textures[TEXTURE_PERM_LOSE], &game->video.perm_textures.rects[RECT_PERM_DES_LOSE], 3.0);
			}

			game_restart = open_are_you_sure(game, game->video.perm_textures.textures[TEXTURE_PERM_GAME_RESTART], &game->video.perm_textures.rects[RECT_PERM_DES_GAME_RESTART], FALSE);
		}

		free_game(&game);

		if(game_restart) {
			load_game(window, renderer);
		}
	}

	return 0;
}

int update_game(Game *const game) {

	while(game->is_running && !game->end) {

		game->time.timer_start = SDL_GetPerformanceCounter();

		do_events(game);

		if(is_pressed(&(game->input.keyboard), KEY_ESC)) {

			game->menu.pause_time = handle_menu(game);
		}
		else if(game->is_running && !game->end) {

			handle_settings(game);

			load_level(game);

			if(game->is_running) {
			
				update_camera(game);
				
				render_game(game);

				if(game->video.effects.fade.state == FADE_STATE_NO_FADE) {

					Mix_Resume(-1);

					update_map(game);
					
					handle_water_time(&(game->level.water), game->time.delta_time);
					
					handle_level(game);

					late_update_map(game);
				}
				else {
					handle_fade_timer(&(game->video.effects.fade), game->time.delta_time);
				}
			}
		}

		handle_keyboard_time(&game->input.keyboard, game->time.delta_time);

		if(game->level.is_passed == TRUE) {
			decrease_time(&game->time.delta_time, 0.01);
		}

		game->time.timer_stop = SDL_GetPerformanceCounter();
		game->time.delta_time = get_delta_time(&game->time.timer_start, &game->time.timer_stop);
	}

	return 0;
}

void init_game(Game **const game, SDL_Window *window, SDL_Renderer *renderer) {

	*game = (Game*)malloc(sizeof(Game));
	if((*game) == NULL) {
		printf("Error! Couldn't allocate memory for 'game'.\n");
		return;
	}
	else {
		memset((*game), 0, sizeof(Game));
	}

	(*game)->is_running = TRUE;
	(*game)->end = FALSE;
	(*game)->win = FALSE;
	(*game)->mode = GAME_MODE_NORMAL;
	(*game)->screen.window = window;
	(*game)->screen.info_window.mode = WINDOW_MODE_FULLSCREEN;
	(*game)->video.renderer = renderer;
	(*game)->map.tile_map = NULL;

	init_speed(&((*game)->speed));
	init_player(&((*game)->player));
	init_game_time(&((*game)->time));
	init_settings(&(*game)->settings);
	handle_window_mode((*game));

	get_window_size((*game)->screen.window, &(*game)->screen.info_window);
	init_textures((*game)->video.textures.map, TEXTURE_MAP_COUNT);
	init_textures((*game)->video.textures.hud, TEXTURE_HUD_COUNT);
	init_textures((*game)->video.perm_textures.textures, TEXTURE_PERM_COUNT);
	init_level(&(*game)->level);
	init_input(&(*game)->input, &(*game)->time.timer_start);
	init_hud(&(*game)->video.hud, &(*game)->screen.info_window);
	init_fade(&(*game)->video.effects.fade, &(*game)->time.timer_start);
	load_textures_perm((*game)->video.perm_textures.textures, (*game)->video.renderer, (*game)->video.hud.fonts);
	get_rects_perm((*game)->video.perm_textures.rects, &(*game)->screen.info_window);
	init_audio(&((*game)->audio));
	open_audio(&((*game)->audio.spec));
	Mix_AllocateChannels((*game)->audio.allocated_channels);
	load_sounds(&((*game)->audio));
}

void init_settings(Settings *const settings) {

	settings->fps.lock = TRUE;
	settings->fps.per_second = 240;
	settings->dev_mode.is_on = FALSE;
	settings->dev_mode.is_saved = TRUE;
	settings->dev_mode.is_loaded = TRUE;
	settings->window.should_change = TRUE;
	settings->fps.show = FALSE;
}

void init_speed(Speed *const speed) {

	speed->character = 4;
	speed->solid = 1.0;
	speed->foe = 0.8;
}

void init_player(Player *const player) {

	player->object = NULL;
	player->lives = 4;
	player->score.point = 0;
	player->movement_player = MOVE_WAIT;
	player->right_of_lives = 2;
}

void init_game_time(GameTime *const time) {

	time->delta_time = 0.0;
}

void init_input(Input *const input, Uint64 *timer_start) {

	input->key = KEY_NONE;
	init_keyboard(&(input->keyboard), timer_start);
}

void handle_game_mode(Game *const game) {

	switch(game->mode) {
		case GAME_MODE_EASY:
			game->speed.solid = 0.9;
			game->speed.foe = 0.6;
			game->player.right_of_lives = 2;
			game->player.lives = 4;
			game->level.water.flow_time_extra = 0.3;
			break;
		case GAME_MODE_NORMAL:
			game->speed.solid = 0.98;
			game->speed.foe = 0.8;
			game->player.right_of_lives = 2;
			game->player.lives = 4;
			game->level.water.flow_time_extra = 0.0;
			break;
		case GAME_MODE_HARD:
			game->speed.solid = 1.0;
			game->speed.foe = 1.0;
			game->player.right_of_lives = 1;
			game->player.lives = 3;
			game->level.water.flow_time_extra = -0.2;
			break;
		case GAME_MODE_IMPOSSIBLE:
			game->speed.solid = 1.008; /*this gives player to do immediate dodge in 0,00397 seconds at 240FPS
											since this is fps related which means faster fps means lower chance to dodge,
												this value should be calculated more carefully or change dynamically related to fps
													why? because FPS Lock doesn't work perfectly thanks to SDL_Delay so even fps lock is on
														at max capped rate there will be fps spikes above max capped rate and also
															fps may not be capped by player's choice*/
			game->speed.foe = 1.05;
			game->player.right_of_lives = 0;
			game->player.lives = 3;
			game->level.water.flow_time_extra = -0.4;
			break;
	}
}

void handle_settings(Game *const game) {

	handle_fps(&(game->settings.fps), &game->time);
	handle_dev_mode(game);
}

void handle_fps(FPS *const fps, GameTime *const time) {

	double expected = 1000.0 / fps->per_second;
	double current = time->delta_time * 1000.0;

	if(fps->lock == TRUE) {

		if(expected >= current) {
			SDL_Delay((int)(expected - current));
		}
	}
}

void handle_dev_mode(Game *const game) {

	int i = 0;

	if(game->settings.dev_mode.is_saved == FALSE) {
		for(i = 0; i < LEVEL_COUNT; ++i) {
			game->settings.dev_mode.unlocked_save[i] = game->level.is_unlocked[i];
		}
		game->settings.dev_mode.is_saved = TRUE;
		game->settings.dev_mode.old_score = game->player.score.point;
	}

	if(game->settings.dev_mode.is_loaded == FALSE) {
		for(i = 0; i < LEVEL_COUNT; ++i) {
			game->level.is_unlocked[i] = game->settings.dev_mode.unlocked_save[i];
			if(game->settings.dev_mode.unlocked_save[i] == TRUE) {
				game->level.levelID = i;
			}
		}
		game->player.score.point = game->settings.dev_mode.old_score;

		free_map(&(game->map.tile_map), &(game->map.info_tile_map));
		free_camera(&(game->screen.camera));

		game->level.is_level_screen_open = TRUE;

		game->settings.dev_mode.is_loaded = TRUE;	
	}

	if(game->settings.dev_mode.is_on == TRUE) { 
		for(i = 0; i < LEVEL_COUNT; ++i) {
			game->level.is_unlocked[i] = TRUE;
		}
	}
}

void handle_window_mode(Game *const game) {

	SDL_DisplayMode dp_mode;

	if(game->settings.window.should_change == TRUE) {
		switch(game->screen.info_window.mode) {
			case WINDOW_MODE_WINDOWED:
				SDL_SetWindowFullscreen(game->screen.window, 0);
				SDL_SetWindowBordered(game->screen.window, SDL_TRUE);
				SDL_ShowCursor(SDL_ENABLE);
				break;
			case WINDOW_MODE_BORDERLESS:
				SDL_SetWindowFullscreen(game->screen.window, 0);
				SDL_RestoreWindow(game->screen.window);
				SDL_GetCurrentDisplayMode(SDL_GetWindowDisplayIndex(game->screen.window), &dp_mode);
				SDL_SetWindowSize(game->screen.window, dp_mode.w, dp_mode.h);
				SDL_SetWindowBordered(game->screen.window, SDL_FALSE);
				SDL_ShowCursor(SDL_ENABLE);
				break;
			case WINDOW_MODE_FULLSCREEN:
				SDL_SetWindowFullscreen(game->screen.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
				SDL_SetWindowBordered(game->screen.window, SDL_FALSE);
				SDL_ShowCursor(SDL_DISABLE);
				break;
		}

		game->settings.window.should_change = FALSE;
	}
}

double get_resultant_speed(const TileSet tile, const Game *const game) {

	double resultant_speed = game->speed.character;

	switch(tile) {
		case TILE_STONE:
		case TILE_DIAMOND:
			resultant_speed *= game->speed.solid;
			break;
		case TILE_SPIDER:
		case TILE_MONSTER:
			resultant_speed *= game->speed.foe;
			break;
		default:
			break;
	}

	return resultant_speed;
}

double get_delta_time(const Uint64 *const timer_start, const Uint64 *const timer_stop) {

	double delta_time = 0.0;
		
	delta_time = get_time_seconds(timer_start, timer_stop);
	fix_delta_time(&delta_time);

	return delta_time;
}

void fix_delta_time(double *const delta_time) {

	if(*delta_time > 1.0) *delta_time = 1.0;
}

void free_game(Game **game) {

	if((*game) != NULL) {
		free_fonts((*game)->video.hud.fonts);
		free_map(&((*game)->map.tile_map), &(*game)->map.info_tile_map);
		free_camera(&(*game)->screen.camera);
		free_textures((*game)->video.textures.map, TEXTURE_MAP_COUNT);
		free_textures((*game)->video.textures.hud, TEXTURE_HUD_COUNT);
		free_textures((*game)->video.perm_textures.textures, TEXTURE_PERM_COUNT);
		free_audio(&((*game)->audio));
		free((*game));
		(*game) = NULL;
	}
}
