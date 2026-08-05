#include <assert.h>
#include <math.h>
#include <string.h>
#include "bh1750/bh1750_core.h"

typedef struct {
    uint8_t commands[4];
    size_t count;
    uint8_t response[2];
    uint32_t delay;
} mock_t;

static bh1750_status_t write_mock(
    void *context, uint8_t address,
    const uint8_t *data, size_t length
) {
    mock_t *mock = (mock_t *)context;
    if (address != 0x23U || data == NULL || length != 1U) {
        return BH1750_STATUS_BUS_ERROR;
    }
    mock->commands[mock->count++] = data[0];
    return BH1750_STATUS_OK;
}

static bh1750_status_t read_mock(
    void *context, uint8_t address,
    uint8_t *data, size_t length
) {
    mock_t *mock = (mock_t *)context;
    if (address != 0x23U || data == NULL || length != 2U) {
        return BH1750_STATUS_BUS_ERROR;
    }
    memcpy(data, mock->response, 2U);
    return BH1750_STATUS_OK;
}

static void delay_mock(void *context, uint32_t delay_ms)
{
    ((mock_t *)context)->delay += delay_ms;
}

int main(void)
{
    mock_t mock = {.response = {0x01U, 0x20U}};
    const bh1750_bus_t bus = {
        .context = &mock,
        .write = write_mock,
        .read = read_mock,
        .delay_ms = delay_mock
    };

    bh1750_device_t device;
    assert(bh1750_init(&device, &bus, 0x23U));
    assert(mock.count == 3U);
    assert(mock.commands[0] == 0x01U);
    assert(mock.commands[1] == 0x07U);
    assert(mock.commands[2] == 0x10U);
    assert(mock.delay == 180U);

    float lux = 0.0F;
    assert(bh1750_read_lux(&device, &lux));
    assert(fabsf(lux - 240.0F) < 0.01F);
    assert(fabsf(bh1750_raw_to_lux(120U) - 100.0F) < 0.01F);
    return 0;
}
