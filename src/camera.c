#include <RPS/BD.h>

void set_camera_focus_multiplier(Camera *const camera, const LevelID LevelID) {

	switch(LevelID) {
		case LEVEL_ZERO:
			camera->focus_multiplier.x = 1.5;
			camera->focus_multiplier.y = 1.5;
			break;
		case LEVEL_ONE:
			camera->focus_multiplier.x = 1.8;
			camera->focus_multiplier.y = 1.8;
			break;
		case LEVEL_TWO:
			camera->focus_multiplier.x = 1.5;
			camera->focus_multiplier.y = 1.3;
			break;
		case LEVEL_THREE:
			camera->focus_multiplier.x = 5;
			camera->focus_multiplier.y = 1.5;
			break;
		case LEVEL_FOUR:
			camera->focus_multiplier.x = 1;
			camera->focus_multiplier.y = 1.07;
			break;
		case LEVEL_FIVE:
			camera->focus_multiplier.x = 1;
			camera->focus_multiplier.y = 1.6;
			break;
		case LEVEL_SIX:
			camera->focus_multiplier.x = 1.4;
			camera->focus_multiplier.y = 1;
			break;
		case LEVEL_SEVEN:
			camera->focus_multiplier.x = 2;
			camera->focus_multiplier.y = 2;
			break;
		case LEVEL_EIGHT:
			camera->focus_multiplier.x = 2;
			camera->focus_multiplier.y = 1.4;
			break;
		case LEVEL_NINE:
			camera->focus_multiplier.x = 1;
			camera->focus_multiplier.y = 1;
			break;
		
		default:
			camera->focus_multiplier.x = 1;
			camera->focus_multiplier.y = 1;
			break;
	}
}

void init_camera(Camera *const camera, TileMap **const map, const TileMapInfo *const info_map) {

	int x_pos, y_pos;

	camera->focus_area.w = (int)(info_map->width * TILE_WIDTH / camera->focus_multiplier.x);
	camera->focus_area.h = (int)(info_map->height * TILE_HEIGHT / camera->focus_multiplier.y);

	camera->focus_area.x = (int)((info_map->width * TILE_WIDTH - camera->focus_area.w - TILE_WIDTH) / 2);
	camera->focus_area.y = (int)((info_map->height * TILE_HEIGHT - camera->focus_area.h - TILE_HEIGHT) / 2);

	for(y_pos = 0; y_pos < info_map->height; ++y_pos) {
		for(x_pos = 0; x_pos < info_map->width; ++x_pos) {
			if(map[y_pos][x_pos].tile == TILE_CHARACTER) {
				camera->object = &(map[y_pos][x_pos]);
			}
		}
	}

	camera->base_focus_point = find_camera_focus(camera);
	camera->HR_base_focus_point.x = (double)camera->base_focus_point.x;
	camera->HR_base_focus_point.y = (double)camera->base_focus_point.y;
	
	camera->movement = (Movement*)malloc(sizeof(Movement));
	*(camera->movement) = MOVE_WAIT;
	camera->speed = 0.9;
	camera->offset.x = (int)(TILE_WIDTH / 2);
	camera->offset.y = (int)(TILE_HEIGHT / 2);
}

void follow_camera_bounded(Camera *const camera, TileMap **const map, const Movement movement, const int x_pos, const int y_pos) {

	switch((int)movement) {
		case MOVE_UP:
			camera->object = &map[y_pos - 1][x_pos];
			break;
		case MOVE_RIGHT:
			camera->object = &map[y_pos][x_pos + 1];
			break;
		case MOVE_DOWN:
			camera->object = &map[y_pos + 1][x_pos];
			break;
		case MOVE_LEFT:
			camera->object = &map[y_pos][x_pos - 1];
			break;
	}
}

void update_camera(Game *const game) {

	game->screen.camera.future_focus_point = find_camera_focus(&(game->screen.camera));
	*(game->screen.camera.movement) = find_camera_movement(&(game->screen.camera.base_focus_point), &(game->screen.camera.future_focus_point));
	shift_camera(&(game->screen.camera), &(game->speed), game->time.delta_time);
	game->screen.camera.delta_camera.shift = focus_camera(game->map.tile_map, &(game->map.info_tile_map), &(game->screen.info_window), &(game->screen.camera));
}

Point2D find_camera_focus(Camera *const camera) {

	Point2D focus = {0, 0};

	if(camera->object->base_des_rect.x < camera->focus_area.x) {
		if(camera->object->base_des_rect.y < camera->focus_area.y) {
			focus.x = camera->focus_area.x;
			focus.y = camera->focus_area.y;
		}
		else if(camera->object->base_des_rect.y >= camera->focus_area.y &&
					camera->object->base_des_rect.y <= camera->focus_area.y + camera->focus_area.h) {

			focus.x = camera->focus_area.x;
			focus.y = camera->object->base_des_rect.y;
		}
		else {
			focus.x = camera->focus_area.x;
			focus.y = camera->focus_area.y + camera->focus_area.h;
		}	

	}
	else if(camera->object->base_des_rect.x >= camera->focus_area.x &&
				camera->object->base_des_rect.x <= camera->focus_area.x + camera->focus_area.w) {

		if(camera->object->base_des_rect.y < camera->focus_area.y) {
			focus.y = camera->focus_area.y;
			focus.x = camera->object->base_des_rect.x;
		}
		else if(camera->object->base_des_rect.y >= camera->focus_area.y &&
					camera->object->base_des_rect.y <= camera->focus_area.y + camera->focus_area.h) {

			focus.x = camera->object->base_des_rect.x;
			focus.y = camera->object->base_des_rect.y;
		}
		else {
			focus.y = camera->focus_area.y + camera->focus_area.h;
			focus.x = camera->object->base_des_rect.x;
		}
	}
	else {
		if(camera->object->base_des_rect.y < camera->focus_area.y) {
			focus.x = camera->focus_area.x + camera->focus_area.w;
			focus.y = camera->focus_area.y;
		}
		else if(camera->object->base_des_rect.y >= camera->focus_area.y &&
					camera->object->base_des_rect.y <= camera->focus_area.y + camera->focus_area.h) {
			
			focus.x = camera->focus_area.x + camera->focus_area.w;
			focus.y = camera->object->base_des_rect.y;
		}
		else {
			focus.x = camera->focus_area.x + camera->focus_area.w;
			focus.y = camera->focus_area.y + camera->focus_area.h;
		}
	}

	return focus;
}

void shift_camera(Camera *const camera, const Speed *const speed, const double delta_time) {

	if(*(camera->movement) != MOVE_WAIT) {
		if(*(camera->movement) == MOVE_UP || *(camera->movement) == MOVE_UP_RIGHT || *(camera->movement) == MOVE_UP_LEFT) {
			camera->HR_base_focus_point.y -= TILE_HEIGHT * speed->character * delta_time * camera->speed;
			camera->base_focus_point.y = (int)camera->HR_base_focus_point.y;
			if(camera->HR_base_focus_point.y < camera->future_focus_point.y) {
				camera->base_focus_point.y = camera->future_focus_point.y;
				camera->HR_base_focus_point.y = (double)camera->base_focus_point.y;
				switch(*(camera->movement)) {
					case MOVE_UP:
						*(camera->movement) = MOVE_WAIT;
						break;
					case MOVE_UP_RIGHT:
						*(camera->movement) = MOVE_RIGHT;
						break;
					case MOVE_UP_LEFT:
						*(camera->movement) = MOVE_LEFT;
						break;
					default:
						break;
				}
			}
		}

		if(*(camera->movement) == MOVE_RIGHT || *(camera->movement) == MOVE_UP_RIGHT || *(camera->movement) == MOVE_DOWN_RIGHT) {
			camera->HR_base_focus_point.x += TILE_WIDTH * speed->character * delta_time * camera->speed;
			camera->base_focus_point.x = (int)camera->HR_base_focus_point.x;
			if(camera->HR_base_focus_point.x > camera->future_focus_point.x) {
				camera->base_focus_point.x = camera->future_focus_point.x;
				camera->HR_base_focus_point.x = (double)camera->base_focus_point.x;
				switch(*(camera->movement)) {
					case MOVE_RIGHT:
						*(camera->movement) = MOVE_WAIT;
						break;
					case MOVE_UP_RIGHT:
						*(camera->movement) = MOVE_UP;
						break;
					case MOVE_DOWN_RIGHT:
						*(camera->movement) = MOVE_DOWN;
						break;
					default:
						break;
				}
			}
		}

		if(*(camera->movement) == MOVE_DOWN || *(camera->movement) == MOVE_DOWN_RIGHT || *(camera->movement) == MOVE_DOWN_LEFT) {
			camera->HR_base_focus_point.y += TILE_HEIGHT * speed->character * delta_time * camera->speed;
			camera->base_focus_point.y = (int)camera->HR_base_focus_point.y;
			if(camera->HR_base_focus_point.y > camera->future_focus_point.y) {
				camera->base_focus_point.y = camera->future_focus_point.y;
				camera->HR_base_focus_point.y = (double)camera->base_focus_point.y;
				switch(*(camera->movement)) {
					case MOVE_DOWN:
						*(camera->movement) = MOVE_WAIT;
						break;
					case MOVE_DOWN_RIGHT:
						*(camera->movement) = MOVE_RIGHT;
						break;
					case MOVE_DOWN_LEFT:
						*(camera->movement) = MOVE_LEFT;
						break;
					default:
						break;
				}
			}
		}

		if(*(camera->movement) == MOVE_LEFT || *(camera->movement) == MOVE_UP_LEFT || *(camera->movement) == MOVE_DOWN_LEFT) {
			camera->HR_base_focus_point.x -= TILE_WIDTH * speed->character * delta_time * camera->speed;
			camera->base_focus_point.x = (int)camera->HR_base_focus_point.x;
			if(camera->HR_base_focus_point.x < camera->future_focus_point.x) {
				camera->base_focus_point.x = camera->future_focus_point.x;
				camera->HR_base_focus_point.x = (double)camera->base_focus_point.x;
				switch(*(camera->movement)) {
					case MOVE_LEFT:
						*(camera->movement) = MOVE_WAIT;
						break;
					case MOVE_UP_LEFT:
						*(camera->movement) = MOVE_UP;
						break;
					case MOVE_DOWN_LEFT:
						*(camera->movement) = MOVE_DOWN;
						break;
					default:
						break;
				}
			}
		}
	}
}

Point2D focus_camera(TileMap **const map, const TileMapInfo *const info_map,
						const WindowInfo *const info_window, const Camera *const camera) {

	int y_pos, x_pos;
	Point2D shift;

	shift.y = (int)((info_window->height / 2) - camera->HR_base_focus_point.y - camera->offset.y);
	shift.x = (int)((info_window->width / 2) - camera->HR_base_focus_point.x - camera->offset.x);

	for(y_pos = 0; y_pos < info_map->height; ++y_pos) {
		for(x_pos = 0; x_pos < info_map->width; ++x_pos) {
			map[y_pos][x_pos].des_rect.y = map[y_pos][x_pos].base_des_rect.y + shift.y;
			map[y_pos][x_pos].des_rect.x = map[y_pos][x_pos].base_des_rect.x + shift.x;
		}
	}

	return shift;
}

void offset_with_camera(SDL_Rect *const des, SDL_Rect *const base, const Camera *const camera) {
	
	des->x = base->x + camera->delta_camera.shift.x;
	des->y = base->y + camera->delta_camera.shift.y;
}

void smoothen_character_occupied(TileMap *const tile) {

	SDL_Rect dirt_src_rect;
	int delta_src;
	bool is_dirt = FALSE;

	find_src_rect(&dirt_src_rect, TILE_DIRT);
					
	is_dirt = check_if_dirt(tile, &dirt_src_rect);

	if(is_dirt == FALSE) {
		find_src_rect(&dirt_src_rect, 17); /*other frames of dirt*/

		is_dirt = check_if_dirt(tile, &dirt_src_rect);
	}

	if(is_dirt == FALSE) {
		find_src_rect(&dirt_src_rect, 27);

		is_dirt = check_if_dirt(tile, &dirt_src_rect);
	}

	if(is_dirt == FALSE) {
		find_src_rect(&dirt_src_rect, 37);

		is_dirt = check_if_dirt(tile, &dirt_src_rect);
	}

	if(is_dirt) {
		switch(tile->movement) {
			case MOVE_UP:
				delta_src = tile->base_des_rect.y - tile->future_des_rect.y;

				tile->occupied_src_rect.y = dirt_src_rect.y;
				tile->occupied_src_rect.h = delta_src;
				tile->occupied_base_des_rect.y = tile->future_des_rect.y;
				tile->occupied_des_rect.h = delta_src;
				break;

			case MOVE_RIGHT:
				delta_src = tile->future_des_rect.x - tile->base_des_rect.x;

				tile->occupied_src_rect.x = dirt_src_rect.x + (TILE_WIDTH - delta_src);
				tile->occupied_src_rect.w = delta_src;
				tile->occupied_base_des_rect.x = tile->base_des_rect.x + TILE_WIDTH;
				tile->occupied_des_rect.w = delta_src;
				break;
			
			case MOVE_DOWN:
				delta_src = tile->future_des_rect.y - tile->base_des_rect.y;

				tile->occupied_src_rect.y = dirt_src_rect.y + (TILE_HEIGHT - delta_src);
				tile->occupied_src_rect.h = delta_src;
				tile->occupied_base_des_rect.y = tile->base_des_rect.y + TILE_HEIGHT;
				tile->occupied_des_rect.h = delta_src;
				break;

			case MOVE_LEFT:
				delta_src = tile->base_des_rect.x - tile->future_des_rect.x;

				tile->occupied_src_rect.x = dirt_src_rect.x;
				tile->occupied_src_rect.w = delta_src;
				tile->occupied_base_des_rect.x = tile->future_des_rect.x;
				tile->occupied_des_rect.w = delta_src;
				break;

			default:
				break;
		}
	}

}

void free_camera(Camera *camera) {

	if(camera->movement != NULL) {
		free(camera->movement);
		camera->movement = NULL;
	}
}
