#include "app/menu.h"
#include "app/menu_renderer.h"

extern menu_display_t ssd1306_menu_display_create(void);

static menu_state_t menu;
static menu_display_t display;
static bool redraw_required = true;

static void app_init(void)
{
    menu_init(&menu);
    display = ssd1306_menu_display_create();
}

static void app_handle_event(menu_event_t event)
{
    menu_handle_event(&menu, event);
    redraw_required = true;
}

static void app_loop(void)
{
    if (redraw_required) {
        redraw_required = false;
        menu_render(&menu, &display);
    }
}

/*
 * Map GPIO/UART events to:
 * app_handle_event(MENU_EVENT_UP);
 * app_handle_event(MENU_EVENT_DOWN);
 * app_handle_event(MENU_EVENT_SELECT);
 * app_handle_event(MENU_EVENT_BACK);
 */
