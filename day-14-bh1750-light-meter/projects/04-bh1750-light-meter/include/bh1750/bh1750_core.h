#ifndef BH1750_CORE_H
#define BH1750_CORE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum {
    BH1750_STATUS_OK = 0,
    BH1750_STATUS_BUS_ERROR,
    BH1750_STATUS_INVALID_ARGUMENT
} bh1750_status_t;

typedef bh1750_status_t (*bh1750_write_fn)(
    void *context,
    uint8_t address_7bit,
    const uint8_t *data,
    size_t length
);

typedef bh1750_status_t (*bh1750_read_fn)(
    void *context,
    uint8_t address_7bit,
    uint8_t *data,
    size_t length
);

typedef void (*bh1750_delay_fn)(
    void *context,
    uint32_t delay_ms
);

typedef struct {
    void *context;
    bh1750_write_fn write;
    bh1750_read_fn read;
    bh1750_delay_fn delay_ms;
} bh1750_bus_t;

typedef struct {
    bh1750_bus_t bus;
    uint8_t address_7bit;
    bool initialized;
} bh1750_device_t;

bool bh1750_init(
    bh1750_device_t *device,
    const bh1750_bus_t *bus,
    uint8_t address_7bit
);

bool bh1750_read_lux(
    bh1750_device_t *device,
    float *lux
);

float bh1750_raw_to_lux(uint16_t raw);

#endif
