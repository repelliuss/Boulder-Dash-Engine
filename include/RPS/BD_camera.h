#ifndef BD_CAMERA_H
#define BD_CAMERA_H

	typedef struct speed Speed;
	
	typedef struct deltaCamera {
		Point2D shift;
	}DeltaCamera;

	typedef struct camera {
		SDL_Rect focus_area;
		Point2D base_focus_point, future_focus_point;
		DPoint2D HR_base_focus_point;
		Point2D focus_center;
		DPoint2D focus_multiplier;
		Point2D offset;
		TileMap *object;
		Movement *movement;
		Movement xx;
		DeltaCamera delta_camera;
		double speed;
	}Camera;

	void free_camera(Camera *camera);
	void smoothen_character_occupied(TileMap *const tile);
	void offset_with_camera(SDL_Rect *const des, SDL_Rect *const base, const Camera *const camera);
	Point2D focus_camera(TileMap **const map, const TileMapInfo *const info_map,
							const WindowInfo *const info_window, const Camera *const camera);
	void shift_camera(Camera *const camera, const Speed *const speed, const double delta_time);
	Point2D find_camera_focus(Camera *const camera);
	void update_camera(Game *const game);
	void follow_camera_bounded(Camera *const camera, TileMap **const map, const Movement movement, const int x_pos, const int y_pos);
	void init_camera(Camera *const camera, TileMap **const map, const TileMapInfo *const info_map);
	void set_camera_focus_multiplier(Camera *const camera, const LevelID LevelID);

#endif