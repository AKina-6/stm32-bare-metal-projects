#ifndef SETTINGS_H
#define SETTINGS_H
#include <stdbool.h>
#include <stdint.h>
typedef struct {
    uint16_t light_threshold_lux;
    int16_t temperature_alarm_c_x10;
    uint16_t telemetry_period_ms;
    uint16_t servo_home_deg;
} app_settings_t;
void app_settings_defaults(app_settings_t *settings);
bool app_settings_is_valid(const app_settings_t *settings);
#endif
