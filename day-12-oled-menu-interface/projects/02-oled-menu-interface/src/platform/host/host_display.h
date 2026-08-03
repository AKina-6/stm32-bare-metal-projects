#ifndef HOST_DISPLAY_H
#define HOST_DISPLAY_H

#include <stdbool.h>
#include <stddef.h>

#define HOST_DISPLAY_MAX_LINES 8U
#define HOST_DISPLAY_LINE_LENGTH 64U

typedef struct {
    char lines[HOST_DISPLAY_MAX_LINES][HOST_DISPLAY_LINE_LENGTH];
    size_t line_count;
    size_t present_count;
} host_display_t;

void host_display_clear(void *context);
void host_display_draw_text(
    void *context,
    unsigned char x,
    unsigned char y,
    const char *text,
    bool inverted
);
void host_display_present(void *context);

#endif
