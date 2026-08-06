/* TIM3_CH1 on PA6; timer tick 1 MHz; ARR=19999; 50 Hz PWM. */
#include "servo_controller.h"
#include "stm32f1xx_hal.h"
extern TIM_HandleTypeDef htim3;
static servo_controller_t servo;
static uint32_t last_ms;
static const servo_config_t cfg={0U,180U,500U,2500U,20000U};
static void write_pulse(uint16_t us){__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,servo_pulse_us_to_compare(us,1000000U));}
static void app_init(void){(void)servo_controller_init(&servo,&cfg,90U,2U);write_pulse(servo_angle_to_pulse_us(&cfg,90U));HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);}
static void app_set_angle(int32_t deg){servo_controller_set_target(&servo,deg);}
static void app_loop(void){uint32_t now=HAL_GetTick();if((uint32_t)(now-last_ms)<20U)return;last_ms=now;write_pulse(servo_controller_step(&servo));}
