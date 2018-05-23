#include <stdint.h>
#include "util.h"

uint64_t get_time(void)
{
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    return ((uint64_t)(time.tv_sec)*1000000000 + (uint64_t)(time.tv_nsec));
}
