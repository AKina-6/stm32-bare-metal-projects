#include "app/telemetry_formatter.h"
#include <stdio.h>
bool telemetry_format_status(const environment_app_t *app,char *buffer,size_t n){ if(!app||!buffer||n==0U) return false; int k=snprintf(buffer,n,"TEMP=%.1f HUM=%.1f LIGHT=%.1f STATUS=%s SERVO=%u",(double)app->latest.temperature_c,(double)app->latest.humidity_percent,(double)app->latest.light_lux,environment_app_status_name(app->status),app->servo_target_deg); return k>0 && (size_t)k<n; }
