#include <assert.h>
#include <math.h>
#include "app/light_meter.h"

int main(void)
{
    light_meter_t meter;
    light_meter_init(&meter);

    assert(meter.status == LIGHT_METER_STALE);
    assert(light_meter_accept(&meter, 20.0F, 1000U));
    assert(meter.level == LIGHT_LEVEL_DIM);

    assert(light_meter_accept(&meter, 180.0F, 1500U));
    assert(fabsf(meter.average_lux - 100.0F) < 0.01F);
    assert(meter.level == LIGHT_LEVEL_NORMAL);

    light_meter_mark_error(&meter);
    assert(meter.status == LIGHT_METER_SENSOR_ERROR);
    assert(meter.failed_reads == 1U);

    light_meter_update_status(&meter, 5001U, 3000U);
    assert(meter.status == LIGHT_METER_STALE);

    assert(light_meter_classify(5.0F) == LIGHT_LEVEL_DARK);
    assert(light_meter_classify(50.0F) == LIGHT_LEVEL_DIM);
    assert(light_meter_classify(300.0F) == LIGHT_LEVEL_NORMAL);
    assert(light_meter_classify(700.0F) == LIGHT_LEVEL_BRIGHT);
    assert(light_meter_classify(1500.0F) == LIGHT_LEVEL_VERY_BRIGHT);
    return 0;
}
