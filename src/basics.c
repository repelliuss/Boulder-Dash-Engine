#include <RPS/BD.h>

int build_game(void) {
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	window = build_window();
	if(window) {
		renderer = build_renderer(window);
		if(renderer) {
			load_game(window, renderer);
		}
	}

	if(!window || !renderer) {
		return 1;
	}
	else clean_game(window, renderer);
	
	return 0;
}

void init_stack_array(StackMovables **root, const int size) {

	int i;

	for(i = 0; i < size; ++i) {
		root[i] = NULL;
	}
}

StackMovables* new_movables(const int x_pos, const int y_pos) {

	StackMovables* node = (StackMovables*)malloc(sizeof(StackMovables));
	node->x_pos = x_pos;
	node->y_pos = y_pos;
	node->next = NULL;
	return node;
}

void push_movables(StackMovables **root, const int x_pos, const int y_pos) {

	StackMovables* node = new_movables(x_pos, y_pos);
	node->next = *root;
	*root = node;
}

void pop_movables(StackMovables **root) {
	
	if(*root != NULL) {
		StackMovables *temp = *root;
		*root = (*root)->next;
		free(temp);
		temp = NULL;
	}
}

/*more uniformly distributed version*/
int get_random_number(const int min, const int max) {
	
	const double fraction = 1.0 / (RAND_MAX + 1.0);		/*RAND_MAX declared in <stdlib.h>*/

	return min + (int)((max - min + 1) * (rand() * fraction));
}

int get_absolute_value(int value) {

	if(value < 0) {
		return -value;
	}
	else return value;
}

int get_digit_count(int number) {

	int count = 0;

	if(number != 0) {
		for(; number > 0; number /= 10) ++count;
	}
	else {
		count = 1;
	}

	return count;
}

double calculate_rate(double x, double y) {

	return x/y; 
}

/*converts 3 digit integers to string with 0s at the beginning*/
void convert_time_to_string(const int time, char str[4]) {

	if(time > 99) {
		sprintf(&str[0], "%d", time);
	}
	else if(time > 9) {
		str[0] = '0';
		sprintf(&str[1], "%d", time);
	}
	else if(time > 0) {
		str[0] = '0';
		str[1] = '0';
		sprintf(&str[2], "%d", time);
	}
	else {
		strcpy(str, "000\0");
	}
}

void convert_score_to_string(const int score, char str[5]) {

	if(score < 10) {
		str[0] = '0';
		str[1] = '0';
		str[2] = '0';
		sprintf(&str[3], "%d", score);
	}
	else if(score < 100) {
		str[0] = '0';
		str[1] = '0';
		sprintf(&str[2], "%d", score);
	}
	else if(score < 1000) {
		str[0] = '0';
		sprintf(&str[1], "%d", score);
	}
	else if(score < 10000) {
		sprintf(&str[0], "%d", score);
	}
	else {
		strcpy(str, "9999\0");
	}
}

int clean_game(SDL_Window *window, SDL_Renderer *renderer) {

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}
