#include "settings/crc32.h"
#include <stdint.h>
uint32_t crc32_compute(const void *data,size_t length){ const uint8_t *b=(const uint8_t*)data; uint32_t crc=0xFFFFFFFFU; for(size_t i=0;i<length;++i){ crc^=b[i]; for(uint8_t bit=0;bit<8U;++bit){ uint32_t mask=(uint32_t)(-(int32_t)(crc&1U)); crc=(crc>>1U)^(0xEDB88320U&mask);} } return ~crc; }
