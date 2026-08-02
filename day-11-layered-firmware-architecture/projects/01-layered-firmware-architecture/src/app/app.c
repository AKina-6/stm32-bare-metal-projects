#include "app/app.h"
#include <stddef.h>
bool app_init(app_t *app,const app_platform_t *platform,uint32_t blink_period_ms){
 if(app==NULL||platform==NULL||platform->led_set==NULL||platform->button_pressed==NULL||platform->millis==NULL||blink_period_ms==0U)return false;
 app->platform=*platform;app->led_on=false;app->previous_button=false;app->last_blink_ms=platform->millis(platform->context);app->blink_period_ms=blink_period_ms;app->button_toggle_count=0U;app->platform.led_set(app->platform.context,false);return true;
}
void app_step(app_t *app){
 if(app==NULL)return;uint32_t now=app->platform.millis(app->platform.context);bool current=app->platform.button_pressed(app->platform.context);
 if(current&&!app->previous_button){app->led_on=!app->led_on;app->button_toggle_count++;app->platform.led_set(app->platform.context,app->led_on);app->last_blink_ms=now;}
 app->previous_button=current;
 if((uint32_t)(now-app->last_blink_ms)>=app->blink_period_ms){app->last_blink_ms=now;app->led_on=!app->led_on;app->platform.led_set(app->platform.context,app->led_on);}
}
