#include "host_platform.h"
#include <stddef.h>
void host_platform_led_set(void *context,bool on){host_platform_state_t*s=context;if(s){s->led_on=on;s->led_write_count++;}}
bool host_platform_button_pressed(void *context){host_platform_state_t*s=context;return s&&s->button_pressed;}
uint32_t host_platform_millis(void *context){host_platform_state_t*s=context;return s?s->now_ms:0U;}
