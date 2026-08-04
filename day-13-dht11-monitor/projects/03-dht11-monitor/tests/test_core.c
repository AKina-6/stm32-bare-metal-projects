#include <assert.h>
#include <math.h>
#include "environment_monitor.h"
int main(void){dht11_frame_t f={58,0,26,0,84};assert(dht11_checksum(&f)==84);assert(dht11_frame_valid(&f));dht11_measurement_t v;assert(dht11_decode(&f,&v));assert(fabsf(v.temperature_c-26.0F)<0.01F);environment_monitor_t m;environment_monitor_init(&m);assert(environment_monitor_accept(&m,&f,1000));f.checksum=0;assert(!environment_monitor_accept(&m,&f,2000));environment_monitor_refresh(&m,7001,5000);assert(m.status==ENV_STALE);return 0;}
