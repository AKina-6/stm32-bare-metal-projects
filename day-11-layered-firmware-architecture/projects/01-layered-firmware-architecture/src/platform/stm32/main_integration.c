#include "app/app.h"
#include "stm32f1xx_hal.h"
static app_t application;
static void led_set(void*ctx,bool on){(void)ctx;HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,on?GPIO_PIN_SET:GPIO_PIN_RESET);}
static bool button_pressed(void*ctx){(void)ctx;return HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_RESET;}
static uint32_t millis(void*ctx){(void)ctx;return HAL_GetTick();}
static void application_init(void){const app_platform_t p={NULL,led_set,button_pressed,millis};(void)app_init(&application,&p,500U);}
static void application_loop(void){app_step(&application);}
/* CubeMX: PB0 output, PA0 pull-up input. Call application_init() once and application_loop() in while(1). */
