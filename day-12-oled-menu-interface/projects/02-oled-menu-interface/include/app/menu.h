#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include <stdint.h>

#define MENU_ITEM_COUNT 4U

typedef enum {
    MENU_PAGE_HOME = 0,
    MENU_PAGE_SENSOR,
    MENU_PAGE_SETTINGS,
    MENU_PAGE_ABOUT
} menu_page_t;

typedef enum {
    MENU_EVENT_NONE = 0,
    MENU_EVENT_UP,
    MENU_EVENT_DOWN,
    MENU_EVENT_SELECT,
    MENU_EVENT_BACK
} menu_event_t;

typedef struct {
    menu_page_t current_page;
    uint8_t selected_index;
    bool page_open;
    uint32_t event_count;
} menu_state_t;

void menu_init(menu_state_t *state);
void menu_handle_event(menu_state_t *state, menu_event_t event);
const char *menu_item_label(uint8_t index);
const char *menu_page_title(menu_page_t page);

#endif
