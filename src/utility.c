#include <RPS/BD.h>

int save_game(Player *const player, Level *const level, const GameMode game_mode, DevMode *const dev_mode) {

	FILE *fptr = NULL;

	fptr = fopen("Resources/Save/save", "wb");
	if(fptr == NULL) {
		fprintf(stderr, "%s\n", "Save file couldn't open for writing");
		return 1;
	}

	fwrite(&game_mode, sizeof(GameMode), 1, fptr);
	fwrite(&player->lives, sizeof(int), 1, fptr);
	fwrite(&player->right_of_lives, sizeof(int), 1, fptr);

	if(dev_mode->is_on == FALSE) {
		fwrite(&player->score.point, sizeof(int), 1, fptr);
		fwrite(level->is_unlocked, sizeof(bool), LEVEL_COUNT, fptr);
	}
	else {
		fwrite(&dev_mode->old_score, sizeof(int), 1, fptr);
		fwrite(dev_mode->unlocked_save, sizeof(bool), LEVEL_COUNT, fptr);
	}

	fclose(fptr);

	return 0;
}

int load_save(Game *const game) {

	FILE *fptr = NULL;
	int i;

	fptr = fopen("Resources/Save/save", "rb");
	if(fptr == NULL) {
		/*error message given in-game*/
		return 1;
	}

	fread(&game->mode, sizeof(GameMode), 1, fptr);

	handle_game_mode(game);

	fread(&game->player.lives, sizeof(int), 1, fptr);
	fread(&game->player.right_of_lives, sizeof(int), 1, fptr);
	fread(&game->player.score.point, sizeof(int), 1, fptr);
	fread(game->level.is_unlocked, sizeof(bool), LEVEL_COUNT, fptr);

	fclose(fptr);

	for(i = 0; i < LEVEL_COUNT; ++i) {
		if(game->level.is_unlocked[i] == TRUE) {
			game->level.levelID = i;
		}
	}

	game->level.is_level_screen_open = TRUE;

	free_map(&(game->map.tile_map), &(game->map.info_tile_map));
	free_camera(&(game->screen.camera));

	return 0;
}
