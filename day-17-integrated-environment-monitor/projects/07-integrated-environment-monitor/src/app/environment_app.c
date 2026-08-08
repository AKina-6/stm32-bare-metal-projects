#include "app/environment_app.h"
#include <stddef.h>
bool environment_app_init(environment_app_t *app,const environment_config_t *config){
 if(app==NULL||config==NULL||config->light_threshold_lux==0U||config->temperature_alarm_c<-40.0F||config->temperature_alarm_c>125.0F||config->servo_normal_deg>180U||config->servo_alarm_deg>180U) return false;
 app->config=*config; app->latest=(environment_snapshot_t){0}; app->status=ENV_APP_SENSOR_FAULT; app->servo_target_deg=config->servo_alarm_deg; app->update_count=0U; app->alarm_count=0U; return true; }
void environment_app_update(environment_app_t *app,const environment_snapshot_t *snapshot){
 if(app==NULL||snapshot==NULL) return; app->latest=*snapshot; app->update_count++;
 environment_app_status_t s;
 if(!snapshot->temperature_valid||!snapshot->light_valid) s=ENV_APP_SENSOR_FAULT;
 else if(snapshot->temperature_c>=app->config.temperature_alarm_c) s=ENV_APP_TOO_HOT;
 else if(snapshot->light_lux<(float)app->config.light_threshold_lux) s=ENV_APP_TOO_DARK;
 else s=ENV_APP_NORMAL;
 if(s!=ENV_APP_NORMAL && s!=app->status) app->alarm_count++;
 app->status=s; app->servo_target_deg=(s==ENV_APP_NORMAL)?app->config.servo_normal_deg:app->config.servo_alarm_deg; }
const char *environment_app_status_name(environment_app_status_t s){ switch(s){case ENV_APP_NORMAL:return "NORMAL";case ENV_APP_TOO_DARK:return "TOO_DARK";case ENV_APP_TOO_HOT:return "TOO_HOT";case ENV_APP_SENSOR_FAULT:return "SENSOR_FAULT";default:return "UNKNOWN";} }
