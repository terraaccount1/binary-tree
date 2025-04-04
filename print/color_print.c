#include <stdio.h>
#include "color_print.h"

void set_print_with_background(int style, int color, int bg_color) {
    printf("\033[%d;%d;%dm", style, color + 30, bg_color + 40);
}

void set_print(int style, int color) {
    printf("\033[%d;%dm", style, color + 30);
}

void reset_print() {
    printf("\033[0m"); // Reset all attributes
}