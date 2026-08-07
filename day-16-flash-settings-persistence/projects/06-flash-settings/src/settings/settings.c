#include "settings/settings.h"
#include <stddef.h>
void app_settings_defaults(app_settings_t *s){ if(!s)return; s->light_threshold_lux=300U; s->temperature_alarm_c_x10=300; s->telemetry_period_ms=1000U; s->servo_home_deg=90U; }
bool app_settings_is_valid(const app_settings_t *s){ if(!s)return false; return s->light_threshold_lux<=65000U && s->temperature_alarm_c_x10>=-400 && s->temperature_alarm_c_x10<=1250 && s->telemetry_period_ms>=100U && s->telemetry_period_ms<=60000U && s->servo_home_deg<=180U; }
