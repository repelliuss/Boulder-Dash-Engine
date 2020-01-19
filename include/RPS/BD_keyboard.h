#ifndef BD_KEYBOARD_H
#define BD_KEYBOARD_H

	typedef enum key {
		KEY_ESC,
		KEY_ENTER,
		KEY_D,
		KEY_RIGHT,
		KEY_A,
		KEY_LEFT,
		KEY_W,
		KEY_UP,
		KEY_S,
		KEY_DOWN,
		KEY_NONE
	}Key;

	typedef struct keyboard {
		Key key;
		double time;
		double last_time;
		double key_delay;
		struct timespec *timer_start;
		bool get_key;
	}Keyboard;

	void reset_key(Key *const key);
	bool is_pressed(Keyboard *const keyboard, const Key key);
	void init_keyboard(Keyboard *const keyboard, struct timespec *const timer_start);
	
#endif