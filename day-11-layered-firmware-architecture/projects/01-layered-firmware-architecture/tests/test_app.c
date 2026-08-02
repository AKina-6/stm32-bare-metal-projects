#include <assert.h>
#include "app/app.h"
#include "host_platform.h"
int main(void){host_platform_state_t s={0};app_platform_t p={&s,host_platform_led_set,host_platform_button_pressed,host_platform_millis};app_t a;assert(app_init(&a,&p,500U));assert(!s.led_on);s.now_ms=500U;app_step(&a);assert(s.led_on);s.now_ms=600U;s.button_pressed=true;app_step(&a);assert(!s.led_on&&a.button_toggle_count==1U);s.now_ms=650U;app_step(&a);assert(a.button_toggle_count==1U);s.now_ms=700U;s.button_pressed=false;app_step(&a);s.now_ms=800U;s.button_pressed=true;app_step(&a);assert(s.led_on&&a.button_toggle_count==2U);return 0;}
