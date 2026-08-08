#include <stdio.h>
#include "app/environment_app.h"
#include "app/telemetry_formatter.h"
#include "app/ui_model.h"
static void run_case(environment_app_t *app,const environment_snapshot_t *s,const char *label){ char t[128]; environment_ui_model_t ui; environment_app_update(app,s); telemetry_format_status(app,t,sizeof t); environment_ui_build(app,&ui); printf("[%s]\n%s\nOLED: %s | %s | %s | %s\nupdates=%lu alarms=%lu\n",label,t,ui.line1,ui.line2,ui.line3,ui.line4,(unsigned long)app->update_count,(unsigned long)app->alarm_count); }
int main(void){ const environment_config_t c={200U,30.0F,90U,150U}; environment_app_t app; if(!environment_app_init(&app,&c)) return 1; const environment_snapshot_t normal={25.5F,58.0F,320.0F,true,true}; const environment_snapshot_t dark={26.0F,59.0F,80.0F,true,true}; const environment_snapshot_t hot={33.0F,61.0F,500.0F,true,true}; const environment_snapshot_t fault={0.0F,0.0F,0.0F,false,true}; run_case(&app,&normal,"NORMAL"); run_case(&app,&dark,"DARK"); run_case(&app,&hot,"HOT"); run_case(&app,&fault,"FAULT"); return 0; }
