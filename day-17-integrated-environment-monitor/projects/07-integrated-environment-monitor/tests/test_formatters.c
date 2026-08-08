#include <assert.h>
#include <string.h>
#include "app/environment_app.h"
#include "app/telemetry_formatter.h"
#include "app/ui_model.h"
int main(void){ const environment_config_t c={200U,30.0F,90U,150U}; environment_app_t a; assert(environment_app_init(&a,&c)); const environment_snapshot_t s={25.5F,58.0F,320.0F,true,true}; environment_app_update(&a,&s); char b[128]; assert(telemetry_format_status(&a,b,sizeof b)); assert(strstr(b,"TEMP=25.5")&&strstr(b,"STATUS=NORMAL")&&strstr(b,"SERVO=90")); environment_ui_model_t ui; assert(environment_ui_build(&a,&ui)); assert(strstr(ui.line1,"25.5")&&strstr(ui.line4,"NORMAL")); return 0; }
