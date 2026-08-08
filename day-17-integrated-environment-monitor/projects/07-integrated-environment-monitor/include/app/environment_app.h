#ifndef ENVIRONMENT_APP_H
#define ENVIRONMENT_APP_H
#include <stdbool.h>
#include <stdint.h>
typedef enum { ENV_APP_NORMAL=0, ENV_APP_TOO_DARK, ENV_APP_TOO_HOT, ENV_APP_SENSOR_FAULT } environment_app_status_t;
typedef struct { float temperature_c; float humidity_percent; float light_lux; bool temperature_valid; bool light_valid; } environment_snapshot_t;
typedef struct { uint16_t light_threshold_lux; float temperature_alarm_c; uint16_t servo_normal_deg; uint16_t servo_alarm_deg; } environment_config_t;
typedef struct { environment_config_t config; environment_snapshot_t latest; environment_app_status_t status; uint16_t servo_target_deg; uint32_t update_count; uint32_t alarm_count; } environment_app_t;
bool environment_app_init(environment_app_t *app,const environment_config_t *config);
void environment_app_update(environment_app_t *app,const environment_snapshot_t *snapshot);
const char *environment_app_status_name(environment_app_status_t status);
#endif
