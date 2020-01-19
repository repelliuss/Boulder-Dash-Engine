#ifndef BD_TIMER_H
#define BD_TIMER_H

	typedef struct water Water;
	typedef struct keyboard Keyboard;

	enum {
		TIME_PRECISION_OFFSET = 1
	};

	typedef enum timeState {
		TIME_STATE_FIRST_PERCENT,
		TIME_STATE_SECOND_PERCENT,
		TIME_STATE_THIRD_PERCENT,
		TIME_STATE_LAST_PERCENT
	}TimeState;

	void decrease_time(double *const target, const double value);
	void handle_keyboard_time(Keyboard *const keyboard, const double delta_time);
	void handle_water_time(Water *const water, const double delta_time);
	double get_time_seconds(const struct timespec *const start, const struct timespec *const stop);
	double get_last_time(StackMovables *root_water, const struct timespec *const timer_start);
	void init_timer(struct timespec *const timer);

#endif