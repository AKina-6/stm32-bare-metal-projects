#include "bh1750/bh1750_core.h"
#include "stm32f1xx_hal.h"

extern I2C_HandleTypeDef hi2c1;

static bh1750_status_t stm32_write(
    void *context,
    uint8_t address,
    const uint8_t *data,
    size_t length
) {
    I2C_HandleTypeDef *handle = (I2C_HandleTypeDef *)context;

    if (handle == NULL || data == NULL || length == 0U) {
        return BH1750_STATUS_INVALID_ARGUMENT;
    }

    return HAL_I2C_Master_Transmit(
        handle,
        (uint16_t)(address << 1U),
        (uint8_t *)data,
        (uint16_t)length,
        100U
    ) == HAL_OK ? BH1750_STATUS_OK : BH1750_STATUS_BUS_ERROR;
}

static bh1750_status_t stm32_read(
    void *context,
    uint8_t address,
    uint8_t *data,
    size_t length
) {
    I2C_HandleTypeDef *handle = (I2C_HandleTypeDef *)context;

    if (handle == NULL || data == NULL || length == 0U) {
        return BH1750_STATUS_INVALID_ARGUMENT;
    }

    return HAL_I2C_Master_Receive(
        handle,
        (uint16_t)(address << 1U),
        data,
        (uint16_t)length,
        100U
    ) == HAL_OK ? BH1750_STATUS_OK : BH1750_STATUS_BUS_ERROR;
}

static void stm32_delay(void *context, uint32_t delay_ms)
{
    (void)context;
    HAL_Delay(delay_ms);
}

bh1750_bus_t bh1750_stm32_bus_create(void)
{
    const bh1750_bus_t bus = {
        .context = &hi2c1,
        .write = stm32_write,
        .read = stm32_read,
        .delay_ms = stm32_delay
    };

    return bus;
}
