#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <terminal_color.h>

unsigned colors[AVAILABLE_COLORS] = {-1};

void init_colors(void) {
  colors[BLACK] = 30;
  colors[RED] = 31;
  colors[GREEN] = 32;
  colors[YELLOW] = 33;
  colors[BLUE] = 34;
  colors[PURPLE] = 35;
  colors[CYAN] = 36;
}

void toggle_color(enum COLOR color) {
  printf("\x1b[%dm", colors[color]);
}

void reset_color(void) {
  printf("\x1b[0m");
}

void alloc_formatted_string(
    char **formatted_string, char *format_string,
    va_list ap) {
  if (formatted_string == NULL) {
    fputs("Null pointer to formatted string "
          "(pointer to pointer to char)",
          stderr);
    return;
  }

  if (format_string == NULL) {
    fputs("`format_string` is null", stderr);
    return;
  }

  int bufsize = 0;
  int size = vsnprintf(*formatted_string, bufsize,
                       format_string, ap) +
             1; //+1 for null terminator
  if (size < bufsize) {
    printf("`vsnprintf` error\n");
    return;
  }

  *formatted_string = malloc(size);

  if (*formatted_string == NULL) {
    fputs("Failed to allocated memory for "
          "formatted string",
          stderr);
    return;
  }

  int new_size = vsnprintf(
      *formatted_string, size, format_string, ap);
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
  alloc_formatted_string(&formatted_string,
                         format_string, args);
  va_end(args);
  printf("%s", formatted_string);
  free(formatted_string);
  reset_color();
}
