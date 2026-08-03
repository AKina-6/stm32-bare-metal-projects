#include <stdio.h>
#include "app/menu.h"
#include "app/menu_renderer.h"
#include "host_display.h"

static void show(
    menu_state_t *state,
    const menu_display_t *display,
    const char *event
) {
    printf("event=%s\n", event);
    menu_render(state, display);
}

int main(void)
{
    menu_state_t state;
    host_display_t host = {0};

    const menu_display_t display = {
        .context = &host,
        .clear = host_display_clear,
        .draw_text = host_display_draw_text,
        .present = host_display_present
    };

    menu_init(&state);
    show(&state, &display, "INIT");

    menu_handle_event(&state, MENU_EVENT_DOWN);
    show(&state, &display, "DOWN");

    menu_handle_event(&state, MENU_EVENT_SELECT);
    show(&state, &display, "SELECT");

    menu_handle_event(&state, MENU_EVENT_BACK);
    show(&state, &display, "BACK");

    return 0;
}
