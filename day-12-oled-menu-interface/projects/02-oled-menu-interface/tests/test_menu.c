#include <assert.h>
#include <string.h>
#include "app/menu.h"

int main(void)
{
    menu_state_t state;
    menu_init(&state);

    assert(state.selected_index == 0U);
    assert(!state.page_open);

    menu_handle_event(&state, MENU_EVENT_UP);
    assert(state.selected_index == 3U);

    menu_handle_event(&state, MENU_EVENT_DOWN);
    assert(state.selected_index == 0U);

    menu_handle_event(&state, MENU_EVENT_DOWN);
    assert(state.selected_index == 1U);

    menu_handle_event(&state, MENU_EVENT_SELECT);
    assert(state.page_open);
    assert(state.current_page == MENU_PAGE_SENSOR);

    menu_handle_event(&state, MENU_EVENT_BACK);
    assert(!state.page_open);

    assert(strcmp(menu_item_label(2U), "Settings") == 0);
    return 0;
}
