#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H
#include <stdbool.h>
#include <stdint.h>
typedef struct { uint16_t angle_min_deg, angle_max_deg, pulse_min_us, pulse_max_us, pwm_period_us; } servo_config_t;
typedef struct { servo_config_t config; uint16_t current_angle_deg,target_angle_deg,max_step_deg; uint32_t update_count,clamp_count; } servo_controller_t;
bool servo_config_is_valid(const servo_config_t *config);
uint16_t servo_clamp_angle(const servo_config_t *config,int32_t angle_deg);
uint16_t servo_angle_to_pulse_us(const servo_config_t *config,uint16_t angle_deg);
uint16_t servo_pulse_us_to_compare(uint16_t pulse_us,uint32_t timer_tick_hz);
bool servo_controller_init(servo_controller_t *c,const servo_config_t *cfg,uint16_t initial,uint16_t max_step);
void servo_controller_set_target(servo_controller_t *c,int32_t target);
uint16_t servo_controller_step(servo_controller_t *c);
bool servo_controller_at_target(const servo_controller_t *c);
#endif
