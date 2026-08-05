#include <stdio.h>
#include <string.h>
#include "bh1750/bh1750_core.h"
#include "app/light_meter.h"

typedef struct {
    uint8_t commands[8];
    size_t command_count;
    uint16_t raw_values[5];
    size_t read_index;
    uint32_t delay_ms;
} mock_bus_t;

static bh1750_status_t mock_write(
    void *context,
    uint8_t address,
    const uint8_t *data,
    size_t length
) {
    mock_bus_t *mock = (mock_bus_t *)context;

    if (mock == NULL || address != 0x23U ||
        data == NULL || length != 1U) {
        return BH1750_STATUS_BUS_ERROR;
    }

    mock->commands[mock->command_count++] = data[0];
    return BH1750_STATUS_OK;
}

static bh1750_status_t mock_read(
    void *context,
    uint8_t address,
    uint8_t *data,
    size_t length
) {
    mock_bus_t *mock = (mock_bus_t *)context;

    if (mock == NULL || address != 0x23U ||
        data == NULL || length != 2U ||
        mock->read_index >= 5U) {
        return BH1750_STATUS_BUS_ERROR;
    }

    const uint16_t raw = mock->raw_values[mock->read_index++];
    data[0] = (uint8_t)(raw >> 8U);
    data[1] = (uint8_t)(raw & 0xFFU);
    return BH1750_STATUS_OK;
}

static void mock_delay(void *context, uint32_t delay_ms)
{
    mock_bus_t *mock = (mock_bus_t *)context;
    if (mock != NULL) mock->delay_ms += delay_ms;
}

int main(void)
{
    mock_bus_t mock = {
        .raw_values = {12U, 120U, 360U, 720U, 1440U}
    };

    const bh1750_bus_t bus = {
        .context = &mock,
        .write = mock_write,
        .read = mock_read,
        .delay_ms = mock_delay
    };

    bh1750_device_t sensor;
    light_meter_t meter;

    if (!bh1750_init(&sensor, &bus, 0x23U)) return 1;
    light_meter_init(&meter);

    printf("commands=");
    for (size_t i = 0U; i < mock.command_count; ++i) {
        printf("%s0x%02X", i == 0U ? "" : ",", mock.commands[i]);
    }
    printf(" delay_ms=%lu\n", (unsigned long)mock.delay_ms);

    for (uint32_t i = 0U; i < 5U; ++i) {
        float lux = 0.0F;
        if (!bh1750_read_lux(&sensor, &lux)) return 2;
        light_meter_accept(&meter, lux, (i + 1U) * 500U);

        printf(
            "sample=%lu latest=%.2f avg=%.2f level=%s status=%s\n",
            (unsigned long)(i + 1U),
            (double)meter.latest_lux,
            (double)meter.average_lux,
            light_level_name(meter.level),
            light_meter_status_name(meter.status)
        );
    }

    light_meter_mark_error(&meter);
    printf(
        "after_error status=%s success=%lu fail=%lu\n",
        light_meter_status_name(meter.status),
        (unsigned long)meter.successful_reads,
        (unsigned long)meter.failed_reads
    );

    light_meter_update_status(&meter, 8000U, 3000U);
    printf(
        "after_timeout status=%s\n",
        light_meter_status_name(meter.status)
    );

    return 0;
}
