#ifndef UTILS_H_
#define UTILS_H_

#include <stdint.h>

// courtesy of Emilie Gillet
#define ONE_POLE(out, in, coefficient) out += (in - out) * coefficient
#define MAKE_INTEGRAL_FRACTIONAL(x) \
  int32_t x ## _integral = static_cast<int32_t>(x); \
  float x ## _fractional = x - static_cast<float>(x ## _integral);

int16_t xfade(int16_t a, int16_t b, float blend);
uint32_t rand_u32();
int32_t rand_i32();

#endif  // UTILS_H_