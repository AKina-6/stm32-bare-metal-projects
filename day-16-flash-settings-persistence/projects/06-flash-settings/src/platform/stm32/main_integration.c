/* STM32 integration sketch: reserve two Flash pages in linker script before use. */
#include "settings/settings_manager.h"
#include "stm32f1xx_hal.h"
extern bool stm32_settings_read_slot(void*,uint8_t,settings_record_t*);
extern bool stm32_settings_write_slot(void*,uint8_t,const settings_record_t*);
static settings_manager_t manager;
static uint32_t dirty_since_ms;
static void app_init(void){ settings_storage_t st={0,stm32_settings_read_slot,stm32_settings_write_slot}; (void)settings_manager_init(&manager,&st); }
static void set_light_threshold(uint16_t lux){ settings_manager_set_light_threshold(&manager,lux); dirty_since_ms=HAL_GetTick(); }
static void app_loop(void){ if(manager.dirty && (uint32_t)(HAL_GetTick()-dirty_since_ms)>=2000U) (void)settings_manager_save_if_dirty(&manager); }
