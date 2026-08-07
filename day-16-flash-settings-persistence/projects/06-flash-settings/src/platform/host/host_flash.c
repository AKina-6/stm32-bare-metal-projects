#include "host_flash.h"
#include <stddef.h>
bool host_flash_read_slot(void *ctx,uint8_t slot,settings_record_t *r){ host_flash_t *f=(host_flash_t*)ctx; if(!f||!r||slot>1||!f->present[slot])return false; *r=f->slots[slot]; return true; }
bool host_flash_write_slot(void *ctx,uint8_t slot,const settings_record_t *r){ host_flash_t *f=(host_flash_t*)ctx; if(!f||!r||slot>1)return false; f->slots[slot]=*r; f->present[slot]=true; f->write_count++; return true; }
void host_flash_corrupt_slot(host_flash_t *f,uint8_t slot){ if(f&&slot<2&&f->present[slot])f->slots[slot].crc32^=1U; }
