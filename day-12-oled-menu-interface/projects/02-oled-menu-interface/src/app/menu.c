#include "app/menu.h"
#include <stddef.h>

static const char *const labels[MENU_ITEM_COUNT] = {
    "Home", "Sensor", "Settings", "About"
};

void menu_init(menu_state_t *state)
{
    if (state == NULL) return;
    state->current_page = MENU_PAGE_HOME;
    state->selected_index = 0U;
    state->page_open = false;
    state->event_count = 0U;
}

void menu_handle_event(menu_state_t *state, menu_event_t event)
{
    if (state == NULL || event == MENU_EVENT_NONE) return;

    state->event_count++;

    if (state->page_open) {
        if (event == MENU_EVENT_BACK) {
            state->page_open = false;
        }
        return;
    }

    switch (event) {
        case MENU_EVENT_UP:
            state->selected_index =
                state->selected_index == 0U
                    ? MENU_ITEM_COUNT - 1U
                    : (uint8_t)(state->selected_index - 1U);
            break;

        case MENU_EVENT_DOWN:
            state->selected_index =
                (uint8_t)((state->selected_index + 1U) %
                          MENU_ITEM_COUNT);
            break;

        case MENU_EVENT_SELECT:
            state->current_page =
                (menu_page_t)state->selected_index;
            state->page_open = true;
            break;

        default:
            break;
    }
}

const char *menu_item_label(uint8_t index)
{
    return index < MENU_ITEM_COUNT ? labels[index] : "Unknown";
}

const char *menu_page_title(menu_page_t page)
{
    switch (page) {
        case MENU_PAGE_HOME: return "Home";
        case MENU_PAGE_SENSOR: return "Sensor";
        case MENU_PAGE_SETTINGS: return "Settings";
        case MENU_PAGE_ABOUT: return "About";
        default: return "Unknown";
    }
}
