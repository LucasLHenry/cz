#ifndef UTILS_H_
#define UTILS_H_

#include <stdint.h>
#include "hw_config.h"
#include "tables/pitch_lut.h"

// courtesy of Emilie Gillet
#define ONE_POLE_LPF(out, in, coefficient) out += (in - out) * coefficient
#define MAKE_INTEGRAL_FRACTIONAL(x) \
    int32_t x ## _integral = static_cast<int32_t>(x); \
    float x ## _fractional = x - static_cast<float>(x ## _integral);

#define CLAMP(x, a, b) MAX(MIN(x, b), a)

inline uint32_t rand_u32() {
    static uint64_t val = 1234;  // seed
    val = (val*134775813 + 1) % (1 << 31);
    return static_cast<uint32_t>(val);
}

inline int32_t rand_i32() {
    return static_cast<int32_t>(rand_u32() - (1 << 31));
}

inline float ewma_filter_coefficient(float freq_hz) {
    return (freq_hz / OUTPUT_SAMPLE_RATE) / (1 + (freq_hz / OUTPUT_SAMPLE_RATE));
}

template <typename T>
inline T xfade(T a, T b, float blend);
#include "utils_impl.h"

inline float interpolate(const float* table, float index, float size) {
    index *= size - 1;
    MAKE_INTEGRAL_FRACTIONAL(index)
    float a = table[index_integral];
    float b = table[index_integral + 1];
    return a + (b - a) * index_fractional;
}

inline float pow2f(float x) {
    MAKE_INTEGRAL_FRACTIONAL(x);
    float lut_val = interpolate(pitch_lut, x_fractional, pitch_lut_table_len);
    lut_val *= static_cast<float>(1 << x_integral);
    return lut_val;
}

inline float soft_limit(float x) {
    if (x >= 3.0) return 1.0;
    if (x <= -3.0) return -1.0;
    return x * (27.0f + x * x) / (27.0f + 9.0f * x * x);
}

#endif  // UTILS_H_