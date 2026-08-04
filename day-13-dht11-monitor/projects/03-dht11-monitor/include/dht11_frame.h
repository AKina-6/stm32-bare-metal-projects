#ifndef DHT11_FRAME_H
#define DHT11_FRAME_H
#include <stdbool.h>
#include <stdint.h>
typedef struct { uint8_t h_int,h_dec,t_int,t_dec,checksum; } dht11_frame_t;
typedef struct { float temperature_c, humidity_percent; } dht11_measurement_t;
uint8_t dht11_checksum(const dht11_frame_t *f);
bool dht11_frame_valid(const dht11_frame_t *f);
bool dht11_decode(const dht11_frame_t *f,dht11_measurement_t *m);
#endif
