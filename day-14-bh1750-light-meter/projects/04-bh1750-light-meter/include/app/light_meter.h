#ifndef LIGHT_METER_H
#define LIGHT_METER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define LIGHT_FILTER_CAPACITY 8U

typedef enum {
    LIGHT_LEVEL_DARK = 0,
    LIGHT_LEVEL_DIM,
    LIGHT_LEVEL_NORMAL,
    LIGHT_LEVEL_BRIGHT,
    LIGHT_LEVEL_VERY_BRIGHT
} light_level_t;

typedef enum {
    LIGHT_METER_OK = 0,
    LIGHT_METER_STALE,
    LIGHT_METER_SENSOR_ERROR
} light_meter_status_t;

typedef struct {
    float samples[LIGHT_FILTER_CAPACITY];
    size_t count;
    size_t next_index;
    float sum;
} light_filter_t;

typedef struct {
    light_filter_t filter;
    float latest_lux;
    float average_lux;
    light_level_t level;
    light_meter_status_t status;
    uint32_t last_update_ms;
    uint32_t successful_reads;
    uint32_t failed_reads;
    bool has_measurement;
} light_meter_t;

void light_filter_init(light_filter_t *filter);
float light_filter_push(light_filter_t *filter, float lux);

void light_meter_init(light_meter_t *meter);

bool light_meter_accept(
    light_meter_t *meter,
    float lux,
    uint32_t now_ms
);

void light_meter_mark_error(light_meter_t *meter);

void light_meter_update_status(
    light_meter_t *meter,
    uint32_t now_ms,
    uint32_t stale_timeout_ms
);

light_level_t light_meter_classify(float lux);
const char *light_level_name(light_level_t level);
const char *light_meter_status_name(light_meter_status_t status);

#endif
