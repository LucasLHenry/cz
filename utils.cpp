#include "utils.h"

const uint32_t max_u32 = 4294967295;

int16_t xfade(int16_t a, int16_t b, float blend) {
    return static_cast<int16_t>(a + (b - a)*blend);
}

uint32_t rand_u32() {
    static uint64_t val = 1234;  // seed
    val = (val*134775813 + 1) % (1 << 31);
    return static_cast<uint32_t>(val);
}

int32_t rand_i32() {
    return static_cast<int32_t>(rand_u32() - (1 << 31));
}