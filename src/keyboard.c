#include <RPS/BD.h>

void init_keyboard(Keyboard *const keyboard, struct timespec *const timer_start) {

	keyboard->key = KEY_NONE;
	keyboard->time = 0.0;
	keyboard->key_delay = 0.18;
	keyboard->last_time = 0.0;
	keyboard->timer_start = timer_start;
	keyboard->get_key = TRUE;
}

bool is_pressed(Keyboard *const keyboard, const Key key) {

	bool value = FALSE;

	if(keyboard->key == key) {
		value = TRUE;
		reset_key(&keyboard->key);
	}

	return value;
}

void reset_key(Key *const key) {

	*key = KEY_NONE; 
}
