#include <assert.h>
#include <string.h>
#include "app/menu.h"
#include "app/menu_renderer.h"
#include "host_display.h"

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
    menu_render(&state, &display);

    assert(host.line_count == 4U);
    assert(strstr(host.lines[0], "[Home]") != 0);

    menu_handle_event(&state, MENU_EVENT_DOWN);
    menu_handle_event(&state, MENU_EVENT_SELECT);
    menu_render(&state, &display);

    assert(strstr(host.lines[0], "Sensor") != 0);
    assert(host.present_count == 2U);

    return 0;
}
