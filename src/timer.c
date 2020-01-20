#include <RPS/BD.h>

double get_last_time(StackMovables *root_water, const Uint64 *const timer_start) {
	
	double time = 0.0;
	Uint64 timer_current;

	if(root_water == NULL) {
		timer_current = SDL_GetPerformanceCounter();
		time = get_time_seconds(timer_start, &timer_current);
	}
	else {
		time = get_last_time(root_water->next, timer_start);
	}

	return time;
}

double get_time_seconds(const Uint64 *const timer_start, const Uint64 *const timer_stop) {

	double delta_time = 0.0;

	delta_time = (double)((*timer_stop - *timer_start) * 1000) / SDL_GetPerformanceFrequency();
	delta_time /= 1000;

	return delta_time;
}

void handle_water_time(Water *const water, const double delta_time) {

	if(water->time >= water->flow_time + water->flow_time_extra) {
		water->time -= water->flow_time + water->flow_time_extra;
	}
	water->time -= water->last_time;
	water->time += delta_time;
	water->last_time = 0.0;
}

void handle_keyboard_time(Keyboard *const keyboard, const double delta_time) {

	if(keyboard->get_key == FALSE) {

		if(keyboard->time >= keyboard->key_delay) {
			keyboard->time = 0;
			keyboard->get_key = TRUE;
		}
		else {
			keyboard->time -= keyboard->last_time;
			keyboard->time += delta_time;
			keyboard->last_time = 0.0;
		}
	}
}

void decrease_time(double *const target, const double value) {

	*target -= value;
}
