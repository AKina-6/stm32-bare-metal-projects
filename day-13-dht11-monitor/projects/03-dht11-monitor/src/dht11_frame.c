#include "dht11_frame.h"
#include <stddef.h>
uint8_t dht11_checksum(const dht11_frame_t *f){return f?(uint8_t)(f->h_int+f->h_dec+f->t_int+f->t_dec):0U;}
bool dht11_frame_valid(const dht11_frame_t *f){return f&&dht11_checksum(f)==f->checksum&&f->h_int<=100U&&f->h_dec<=9U&&f->t_int<=80U&&f->t_dec<=9U;}
bool dht11_decode(const dht11_frame_t *f,dht11_measurement_t *m){if(!m||!dht11_frame_valid(f))return false;m->humidity_percent=(float)f->h_int+(float)f->h_dec/10.0F;m->temperature_c=(float)f->t_int+(float)f->t_dec/10.0F;return true;}
