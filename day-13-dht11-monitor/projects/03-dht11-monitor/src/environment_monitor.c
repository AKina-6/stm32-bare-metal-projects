#include "environment_monitor.h"
#include <stddef.h>
void environment_monitor_init(environment_monitor_t *m){if(!m)return;m->latest.temperature_c=0;m->latest.humidity_percent=0;m->last_update_ms=0;m->success=0;m->fail=0;m->status=ENV_STALE;m->has_value=false;}
bool environment_monitor_accept(environment_monitor_t *m,const dht11_frame_t *f,uint32_t now_ms){if(!m)return false;dht11_measurement_t v;if(!dht11_decode(f,&v)){m->fail++;m->status=ENV_SENSOR_ERROR;return false;}m->latest=v;m->last_update_ms=now_ms;m->success++;m->status=ENV_OK;m->has_value=true;return true;}
void environment_monitor_refresh(environment_monitor_t *m,uint32_t now_ms,uint32_t stale_ms){if(m&&m->has_value&&(uint32_t)(now_ms-m->last_update_ms)>stale_ms)m->status=ENV_STALE;}
