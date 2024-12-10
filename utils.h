#ifndef UTILS_H_
#define UTILS_H_

#include <stdint.h>

#define ONE_POLE(out, in, coefficient) out += (in - out) * coefficient
int16_t xfade(int16_t a, int16_t b, float blend);
uint32_t rand_u32();
int32_t rand_i32();

#endif  // UTILS_H_