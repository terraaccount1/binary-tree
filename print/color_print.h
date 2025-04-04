#define STYLE_RESET		    0
#define STYLE_BRIGHT 		1
#define STYLE_DIM		    2
#define STYLE_UNDERLINE 	3
#define STYLE_BLINK		    4
#define STYLE_REVERSE		7
#define STYLE_HIDDEN		8

#define COLOR_BLACK 		0
#define COLOR_RED		    1
#define COLOR_GREEN		    2
#define COLOR_YELLOW		3
#define COLOR_BLUE		    4
#define COLOR_MAGENTA		5
#define COLOR_CYAN		    6
#define	COLOR_WHITE		    7

void set_print_with_background(int style, int color, int bg_color);
void set_print(int style, int color);
void reset_print();