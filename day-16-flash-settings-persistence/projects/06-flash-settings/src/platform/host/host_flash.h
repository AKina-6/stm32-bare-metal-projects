#ifndef HOST_FLASH_H
#define HOST_FLASH_H
#include <stdbool.h>
#include "settings/settings_record.h"
typedef struct { settings_record_t slots[2]; bool present[2]; uint32_t write_count; } host_flash_t;
bool host_flash_read_slot(void*,uint8_t,settings_record_t*);
bool host_flash_write_slot(void*,uint8_t,const settings_record_t*);
void host_flash_corrupt_slot(host_flash_t*,uint8_t);
#endif
