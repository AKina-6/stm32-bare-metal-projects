#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H
#include <stdbool.h>
#include <stdint.h>
#include "settings/settings_record.h"
typedef struct { settings_storage_t storage; app_settings_t settings; uint32_t sequence; uint8_t active_slot; bool dirty; uint32_t save_count; uint32_t recovery_count; } settings_manager_t;
bool settings_manager_init(settings_manager_t*,const settings_storage_t*);
void settings_manager_set_light_threshold(settings_manager_t*,uint16_t);
void settings_manager_set_telemetry_period(settings_manager_t*,uint16_t);
void settings_manager_set_servo_home(settings_manager_t*,uint16_t);
bool settings_manager_save_if_dirty(settings_manager_t*);
#endif
