#include <stdio.h>
#include <string.h>
#include "bh1750/bh1750_core.h"
#include "app/light_meter.h"
#include "stm32f1xx_hal.h"

extern UART_HandleTypeDef huart1;
extern bh1750_bus_t bh1750_stm32_bus_create(void);

static bh1750_device_t sensor;
static light_meter_t meter;
static uint32_t last_read_ms = 0U;

static void uart_send(const char *text)
{
    HAL_UART_Transmit(
        &huart1,
        (uint8_t *)text,
        (uint16_t)strlen(text),
        100U
    );
}

static void app_init(void)
{
    const bh1750_bus_t bus = bh1750_stm32_bus_create();
    light_meter_init(&meter);

    if (!bh1750_init(&sensor, &bus, 0x23U)) {
        uart_send("BH1750 INIT ERROR\r\n");
    }
}

static void app_loop(void)
{
    const uint32_t now = HAL_GetTick();

    if ((uint32_t)(now - last_read_ms) < 500U) {
        light_meter_update_status(&meter, now, 3000U);
        return;
    }

    last_read_ms = now;

    float lux = 0.0F;
    char message[112];

    if (bh1750_read_lux(&sensor, &lux) &&
        light_meter_accept(&meter, lux, now)) {
        const int length = snprintf(
            message,
            sizeof(message),
            "LIGHT latest=%.2f avg=%.2f level=%s\r\n",
            (double)meter.latest_lux,
            (double)meter.average_lux,
            light_level_name(meter.level)
        );

        if (length > 0) uart_send(message);
    } else {
        light_meter_mark_error(&meter);
        uart_send("BH1750 READ ERROR\r\n");
    }
}
