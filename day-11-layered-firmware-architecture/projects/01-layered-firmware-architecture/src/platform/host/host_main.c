#include <stdio.h>
#include "app/app.h"
#include "host_platform.h"
static void step(app_t*a,host_platform_state_t*s,uint32_t t,bool b){s->now_ms=t;s->button_pressed=b;app_step(a);printf("t=%lu button=%s led=%s toggles=%lu writes=%lu\n",(unsigned long)t,b?"pressed":"released",s->led_on?"on":"off",(unsigned long)a->button_toggle_count,(unsigned long)s->led_write_count);}
int main(void){host_platform_state_t s={0};app_platform_t p={&s,host_platform_led_set,host_platform_button_pressed,host_platform_millis};app_t a;if(!app_init(&a,&p,500U))return 1;step(&a,&s,100,false);step(&a,&s,500,false);step(&a,&s,600,true);step(&a,&s,650,true);step(&a,&s,700,false);step(&a,&s,1100,false);return 0;}
