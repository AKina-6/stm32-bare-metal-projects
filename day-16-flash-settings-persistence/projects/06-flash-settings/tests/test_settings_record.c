#include <assert.h>
#include "settings/settings_record.h"
int main(void){ app_settings_t s; app_settings_defaults(&s); settings_record_t r; assert(settings_record_build(&r,&s,7U)); assert(settings_record_is_valid(&r)); assert(r.sequence==7U); r.payload.light_threshold_lux++; assert(!settings_record_is_valid(&r)); return 0; }
