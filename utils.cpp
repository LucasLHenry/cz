#include "utils.h"

uint32_t rand_u32() {
    static uint64_t val = 1234;  // seed
    val = (val*134775813 + 1) % (1 << 31);
    return static_cast<uint32_t>(val);
}

int32_t rand_i32() {
    return static_cast<int32_t>(rand_u32() - (1 << 31));
}

float ewma_filter_coefficient(float freq_hz) {
    return (freq_hz / OUTPUT_SAMPLE_RATE) / (1 + (freq_hz / OUTPUT_SAMPLE_RATE));
}