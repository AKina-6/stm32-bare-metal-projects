#ifndef APP_H
#define APP_H
#include <stdbool.h>
#include <stdint.h>
typedef struct { void *context; void (*led_set)(void *, bool); bool (*button_pressed)(void *); uint32_t (*millis)(void *); } app_platform_t;
typedef struct { app_platform_t platform; bool led_on; bool previous_button; uint32_t last_blink_ms; uint32_t blink_period_ms; uint32_t button_toggle_count; } app_t;
bool app_init(app_t *app,const app_platform_t *platform,uint32_t blink_period_ms);
void app_step(app_t *app);
#endif
