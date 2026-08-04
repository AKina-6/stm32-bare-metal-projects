#ifndef ENVIRONMENT_MONITOR_H
#define ENVIRONMENT_MONITOR_H
#include <stdbool.h>
#include <stdint.h>
#include "dht11_frame.h"
typedef enum { ENV_OK=0, ENV_STALE, ENV_SENSOR_ERROR } env_status_t;
typedef struct { dht11_measurement_t latest; uint32_t last_update_ms,success,fail; env_status_t status; bool has_value; } environment_monitor_t;
void environment_monitor_init(environment_monitor_t *m);
bool environment_monitor_accept(environment_monitor_t *m,const dht11_frame_t *f,uint32_t now_ms);
void environment_monitor_refresh(environment_monitor_t *m,uint32_t now_ms,uint32_t stale_ms);
#endif
