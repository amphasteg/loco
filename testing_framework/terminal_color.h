#ifndef TERM_COLORS
#define TERM_COLORS
#define AVAILABLE_COLORS 8

enum COLOR { BLACK, RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE };

void print_colored_text(enum COLOR color, char *format_string, ...);

#endif
