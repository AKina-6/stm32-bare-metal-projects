#ifndef UI_MODEL_H
#define UI_MODEL_H
#include <stdbool.h>
#include "app/environment_app.h"
typedef struct { char line1[24]; char line2[24]; char line3[24]; char line4[24]; } environment_ui_model_t;
bool environment_ui_build(const environment_app_t *app,environment_ui_model_t *model);
#endif
