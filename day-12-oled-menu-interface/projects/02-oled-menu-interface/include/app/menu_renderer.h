#ifndef MENU_RENDERER_H
#define MENU_RENDERER_H

#include <stdbool.h>
#include <stdint.h>
#include "app/menu.h"

typedef struct {
    void *context;
    void (*clear)(void *context);
    void (*draw_text)(
        void *context,
        uint8_t x,
        uint8_t y,
        const char *text,
        bool inverted
    );
    void (*present)(void *context);
} menu_display_t;

bool menu_display_is_valid(const menu_display_t *display);
void menu_render(
    const menu_state_t *state,
    const menu_display_t *display
);

#endif
