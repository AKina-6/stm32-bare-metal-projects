#include "app/ui_model.h"
#include <stdio.h>
bool environment_ui_build(const environment_app_t *app,environment_ui_model_t *m){ if(!app||!m) return false; snprintf(m->line1,sizeof m->line1,"T: %.1f C",(double)app->latest.temperature_c); snprintf(m->line2,sizeof m->line2,"H: %.1f %%",(double)app->latest.humidity_percent); snprintf(m->line3,sizeof m->line3,"L: %.0f lx",(double)app->latest.light_lux); snprintf(m->line4,sizeof m->line4,"%s S:%u",environment_app_status_name(app->status),app->servo_target_deg); return true; }
