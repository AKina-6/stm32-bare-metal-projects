#ifndef SETTINGS_RECORD_H
#define SETTINGS_RECORD_H
#include <stdbool.h>
#include <stdint.h>
#include "settings/settings.h"
#define SETTINGS_RECORD_MAGIC 0x53544631UL
#define SETTINGS_RECORD_VERSION 1U
typedef struct { uint32_t magic; uint16_t version; uint16_t payload_size; uint32_t sequence; app_settings_t payload; uint32_t crc32; } settings_record_t;
typedef struct { void *context; bool (*read_slot)(void*,uint8_t,settings_record_t*); bool (*write_slot)(void*,uint8_t,const settings_record_t*); } settings_storage_t;
bool settings_record_build(settings_record_t*,const app_settings_t*,uint32_t);
bool settings_record_is_valid(const settings_record_t*);
bool settings_storage_load_latest(const settings_storage_t*,app_settings_t*,uint32_t*,uint8_t*);
bool settings_storage_save_next(const settings_storage_t*,const app_settings_t*,uint32_t,uint8_t,uint32_t*,uint8_t*);
#endif
