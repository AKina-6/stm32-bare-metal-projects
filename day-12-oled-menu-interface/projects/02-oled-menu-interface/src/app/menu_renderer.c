#include "app/menu_renderer.h"
#include <stddef.h>
#include <stdio.h>

bool menu_display_is_valid(const menu_display_t *display)
{
    return display != NULL &&
           display->clear != NULL &&
           display->draw_text != NULL &&
           display->present != NULL;
}

static void render_menu(
    const menu_state_t *state,
    const menu_display_t *display
) {
    for (uint8_t i = 0U; i < MENU_ITEM_COUNT; ++i) {
        display->draw_text(
            display->context,
            0U,
            (uint8_t)(i * 16U),
            menu_item_label(i),
            i == state->selected_index
        );
    }
}

static void render_page(
    const menu_state_t *state,
    const menu_display_t *display
) {
    char line[32];

    display->draw_text(
        display->context, 0U, 0U,
        menu_page_title(state->current_page), false
    );

    switch (state->current_page) {
        case MENU_PAGE_HOME:
            display->draw_text(
                display->context, 0U, 20U,
                "System Ready", false
            );
            break;

        case MENU_PAGE_SENSOR:
            display->draw_text(
                display->context, 0U, 20U,
                "Temp: 25.0 C", false
            );
            display->draw_text(
                display->context, 0U, 36U,
                "Light: 320 lx", false
            );
            break;

        case MENU_PAGE_SETTINGS:
            (void)snprintf(
                line, sizeof(line),
                "Events: %lu",
                (unsigned long)state->event_count
            );
            display->draw_text(
                display->context, 0U, 20U,
                line, false
            );
            break;

        case MENU_PAGE_ABOUT:
            display->draw_text(
                display->context, 0U, 20U,
                "STM32 Menu Demo", false
            );
            break;

        default:
            break;
    }

    display->draw_text(
        display->context, 0U, 52U,
        "< Back", false
    );
}

void menu_render(
    const menu_state_t *state,
    const menu_display_t *display
) {
    if (state == NULL || !menu_display_is_valid(display)) return;

    display->clear(display->context);

    if (state->page_open) {
        render_page(state, display);
    } else {
        render_menu(state, display);
    }

    display->present(display->context);
}
