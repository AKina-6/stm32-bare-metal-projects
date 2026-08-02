#ifndef HOST_PLATFORM_H
#define HOST_PLATFORM_H
#include <stdbool.h>
#include <stdint.h>
typedef struct{uint32_t now_ms;bool button_pressed;bool led_on;uint32_t led_write_count;}host_platform_state_t;
void host_platform_led_set(void *context,bool on);bool host_platform_button_pressed(void *context);uint32_t host_platform_millis(void *context);
#endif
