#ifndef TELEMETRY_FORMATTER_H
#define TELEMETRY_FORMATTER_H
#include <stdbool.h>
#include <stddef.h>
#include "app/environment_app.h"
bool telemetry_format_status(const environment_app_t *app,char *buffer,size_t buffer_size);
#endif
