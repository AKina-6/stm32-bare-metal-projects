/* STM32 integration skeleton: reuse Day 13 DHT11, Day 14 BH1750, Day 12 OLED, Day 15 servo, Day 16 Flash. */
#include <stdio.h>
#include <string.h>
#include "app/environment_app.h"
#include "app/telemetry_formatter.h"
#include "app/ui_model.h"
#include "stm32f1xx_hal.h"
extern UART_HandleTypeDef huart1;
static environment_app_t app;
static uint32_t last_sensor_ms=0U,last_telemetry_ms=0U;
static void uart_send(const char *s){ HAL_UART_Transmit(&huart1,(uint8_t*)s,(uint16_t)strlen(s),100U); }
static void app_init(void){ const environment_config_t c={200U,30.0F,90U,150U}; (void)environment_app_init(&app,&c); /* load persisted settings and init sensors/display/servo here */ }
static void app_loop(void){ uint32_t now=HAL_GetTick(); if((uint32_t)(now-last_sensor_ms)>=1000U){ last_sensor_ms=now; environment_snapshot_t snap={0}; /* fill with real DHT11/BH1750 data */ environment_app_update(&app,&snap); /* servo_set_target(app.servo_target_deg); build OLED model */ } if((uint32_t)(now-last_telemetry_ms)>=2000U){ last_telemetry_ms=now; char buf[128]; if(telemetry_format_status(&app,buf,sizeof buf)){ uart_send(buf); uart_send("\r\n"); } } }
