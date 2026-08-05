#include "bh1750/bh1750_core.h"
#include <stddef.h>

#define BH1750_ADDRESS_LOW 0x23U
#define BH1750_ADDRESS_HIGH 0x5CU
#define BH1750_POWER_ON 0x01U
#define BH1750_RESET 0x07U
#define BH1750_CONTINUOUS_HIGH_RES 0x10U

static bool bus_valid(const bh1750_bus_t *bus)
{
    return bus != NULL &&
           bus->write != NULL &&
           bus->read != NULL &&
           bus->delay_ms != NULL;
}

static bool write_command(
    bh1750_device_t *device,
    uint8_t command
) {
    return device != NULL &&
           device->bus.write(
               device->bus.context,
               device->address_7bit,
               &command,
               1U
           ) == BH1750_STATUS_OK;
}

bool bh1750_init(
    bh1750_device_t *device,
    const bh1750_bus_t *bus,
    uint8_t address_7bit
) {
    if (device == NULL ||
        !bus_valid(bus) ||
        (address_7bit != BH1750_ADDRESS_LOW &&
         address_7bit != BH1750_ADDRESS_HIGH)) {
        return false;
    }

    device->bus = *bus;
    device->address_7bit = address_7bit;
    device->initialized = false;

    if (!write_command(device, BH1750_POWER_ON) ||
        !write_command(device, BH1750_RESET) ||
        !write_command(device, BH1750_CONTINUOUS_HIGH_RES)) {
        return false;
    }

    device->bus.delay_ms(device->bus.context, 180U);
    device->initialized = true;
    return true;
}

bool bh1750_read_lux(
    bh1750_device_t *device,
    float *lux
) {
    if (device == NULL || lux == NULL || !device->initialized) {
        return false;
    }

    uint8_t data[2] = {0U, 0U};

    if (device->bus.read(
            device->bus.context,
            device->address_7bit,
            data,
            sizeof(data)) != BH1750_STATUS_OK) {
        return false;
    }

    const uint16_t raw = (uint16_t)(
        ((uint16_t)data[0] << 8U) | data[1]
    );

    *lux = bh1750_raw_to_lux(raw);
    return true;
}

float bh1750_raw_to_lux(uint16_t raw)
{
    return (float)raw / 1.2F;
}
