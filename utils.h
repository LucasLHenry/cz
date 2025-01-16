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

uint32_t rand_u32();
int32_t rand_i32();

float ewma_filter_coefficient(float freq_hz);

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

#endif  // UTILS_H_