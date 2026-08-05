#include "app/light_meter.h"
#include <math.h>
#include <stddef.h>

void light_filter_init(light_filter_t *filter)
{
    if (filter == NULL) return;

    for (size_t i = 0U; i < LIGHT_FILTER_CAPACITY; ++i) {
        filter->samples[i] = 0.0F;
    }

    filter->count = 0U;
    filter->next_index = 0U;
    filter->sum = 0.0F;
}

float light_filter_push(light_filter_t *filter, float lux)
{
    if (filter == NULL || !isfinite(lux) || lux < 0.0F) {
        return 0.0F;
    }

    if (filter->count < LIGHT_FILTER_CAPACITY) {
        filter->samples[filter->next_index] = lux;
        filter->sum += lux;
        filter->count++;
    } else {
        filter->sum -= filter->samples[filter->next_index];
        filter->samples[filter->next_index] = lux;
        filter->sum += lux;
    }

    filter->next_index =
        (filter->next_index + 1U) % LIGHT_FILTER_CAPACITY;

    return filter->sum / (float)filter->count;
}

light_level_t light_meter_classify(float lux)
{
    if (lux < 10.0F) return LIGHT_LEVEL_DARK;
    if (lux < 100.0F) return LIGHT_LEVEL_DIM;
    if (lux < 500.0F) return LIGHT_LEVEL_NORMAL;
    if (lux < 1000.0F) return LIGHT_LEVEL_BRIGHT;
    return LIGHT_LEVEL_VERY_BRIGHT;
}

const char *light_level_name(light_level_t level)
{
    switch (level) {
        case LIGHT_LEVEL_DARK: return "DARK";
        case LIGHT_LEVEL_DIM: return "DIM";
        case LIGHT_LEVEL_NORMAL: return "NORMAL";
        case LIGHT_LEVEL_BRIGHT: return "BRIGHT";
        case LIGHT_LEVEL_VERY_BRIGHT: return "VERY_BRIGHT";
        default: return "UNKNOWN";
    }
}

const char *light_meter_status_name(light_meter_status_t status)
{
    switch (status) {
        case LIGHT_METER_OK: return "OK";
        case LIGHT_METER_STALE: return "STALE";
        case LIGHT_METER_SENSOR_ERROR: return "SENSOR_ERROR";
        default: return "UNKNOWN";
    }
}

void light_meter_init(light_meter_t *meter)
{
    if (meter == NULL) return;

    light_filter_init(&meter->filter);
    meter->latest_lux = 0.0F;
    meter->average_lux = 0.0F;
    meter->level = LIGHT_LEVEL_DARK;
    meter->status = LIGHT_METER_STALE;
    meter->last_update_ms = 0U;
    meter->successful_reads = 0U;
    meter->failed_reads = 0U;
    meter->has_measurement = false;
}

bool light_meter_accept(
    light_meter_t *meter,
    float lux,
    uint32_t now_ms
) {
    if (meter == NULL || !isfinite(lux) || lux < 0.0F) {
        return false;
    }

    meter->latest_lux = lux;
    meter->average_lux = light_filter_push(&meter->filter, lux);
    meter->level = light_meter_classify(meter->average_lux);
    meter->status = LIGHT_METER_OK;
    meter->last_update_ms = now_ms;
    meter->successful_reads++;
    meter->has_measurement = true;
    return true;
}

void light_meter_mark_error(light_meter_t *meter)
{
    if (meter == NULL) return;
    meter->failed_reads++;
    meter->status = LIGHT_METER_SENSOR_ERROR;
}

void light_meter_update_status(
    light_meter_t *meter,
    uint32_t now_ms,
    uint32_t stale_timeout_ms
) {
    if (meter == NULL || !meter->has_measurement) return;

    if ((uint32_t)(now_ms - meter->last_update_ms) >
        stale_timeout_ms) {
        meter->status = LIGHT_METER_STALE;
    }
}
