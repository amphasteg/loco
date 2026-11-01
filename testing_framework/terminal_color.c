#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <terminal_color.h>

unsigned colors[AVAILABLE_COLORS] = {-1};

void init_colors(void) {
#ifdef WIN32 
// TODO Add table for Windows colors
#else
  colors[BLACK] = 30;
  colors[RED] = 31;
  colors[GREEN] = 32;
  colors[YELLOW] = 33;
  colors[BLUE] = 34;
  colors[PURPLE] = 35;
  colors[CYAN] = 36;
  colors[WHITE] = 37;
#endif
}

void toggle_color(enum COLOR color) {
#ifdef WIN32
  //TODO Add Windows calls here
#else
  printf("\x1b[%dm", colors[color]);
#endif
}

void reset_color(void) {
#ifdef WIN32
#else
  printf("\x1b[0m");
#endif
}

void print_colored_text(enum COLOR color,
                        char *format_string,
                        ...) {
  if (colors[0] == -1)
    init_colors();

  toggle_color(color);
  va_list args;
  va_start(args, format_string);
  char *formatted_string;
  vasprintf(&formatted_string, format_string, args);
  va_end(args);
  printf("%s", formatted_string);
  free(formatted_string);
  reset_color();
}
