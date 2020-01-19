#include <RPS/BD.h>

void init_timer(struct timespec *const timer) {

	timer->tv_sec = 0;
	timer->tv_nsec = 0.0;
}

double get_last_time(StackMovables *root_water, const struct timespec *const timer_start) {
	
	double time = 0.0;
	struct timespec timer_current;

	if(root_water == NULL) {
		clock_gettime(CLOCK_MONOTONIC, &timer_current);
		time = get_time_seconds(timer_start, &timer_current);
	}
	else {
		time = get_last_time(root_water->next, timer_start);
	}

	return time;
}

double get_time_seconds(const struct timespec *const timer_start, const struct timespec *const timer_stop) {

	double delta_time = 0.0;

	delta_time = ((timer_stop->tv_sec - timer_start->tv_sec) * 1000000) + (timer_stop->tv_nsec - timer_start->tv_nsec) / 1000;
	delta_time /= 1000000;

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
