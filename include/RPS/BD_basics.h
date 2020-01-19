#ifndef BD_BASICS_H
#define BD_BASICS_H

	enum {
		STACK_CHARACTER,
		STACK_STONES,
		STACK_DIAMONDS,
		STACK_SPIDERS,
		STACK_MONSTERS,
		STACK_CONVERTER,
		STACK_WATER,
		STACK_STATIC_WATER,
		STACK_COUNT,
		STACK_STARS = 7,
		STACK_LITTLE_DIAMONDS,
		STACK_GATE,
		STACK_BACKGROUND,
		STACK_DIRT,
		STACK_EXTRA_COUNT = 5
	};

	typedef enum { FALSE, TRUE } bool;		/*for readibility*/

	typedef struct stackMovables {
		int x_pos, y_pos;
		struct stackMovables *next;
	}StackMovables;

	int clean_game(SDL_Window *window, SDL_Renderer *renderer);
	void convert_score_to_string(const int score, char str[5]);
	void convert_time_to_string(const int time, char str[4]);
	double calculate_rate(double x, double y);
	int get_digit_count(int number);
	int get_absolute_value(int value);
	int get_random_number(const int min, const int max);
	void pop_movables(StackMovables **root);
	void push_movables(StackMovables **root, const int x_pos, const int y_pos);
	StackMovables* new_movables(const int x_pos, const int y_pos);
	void init_stack_array(StackMovables **root, const int size);
	int build_game(void);

#endif