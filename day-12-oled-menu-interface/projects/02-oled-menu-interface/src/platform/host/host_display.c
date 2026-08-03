#include "host_display.h"
#include <stdio.h>

void host_display_clear(void *context)
{
    host_display_t *display = (host_display_t *)context;
    if (display == NULL) return;
    display->line_count = 0U;
}

void host_display_draw_text(
    void *context,
    unsigned char x,
    unsigned char y,
    const char *text,
    bool inverted
) {
    host_display_t *display = (host_display_t *)context;

    if (display == NULL ||
        text == NULL ||
        display->line_count >= HOST_DISPLAY_MAX_LINES) {
        return;
    }

    (void)snprintf(
        display->lines[display->line_count],
        HOST_DISPLAY_LINE_LENGTH,
        "x=%u y=%u %s%s%s",
        x, y,
        inverted ? "[" : "",
        text,
        inverted ? "]" : ""
    );

    display->line_count++;
}

void host_display_present(void *context)
{
    host_display_t *display = (host_display_t *)context;
    if (display == NULL) return;

    display->present_count++;

    for (size_t i = 0U; i < display->line_count; ++i) {
        printf("%s\n", display->lines[i]);
    }

    printf("--- frame %lu ---\n",
           (unsigned long)display->present_count);
}
