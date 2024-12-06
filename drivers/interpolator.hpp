#ifndef DRIVERS_INTERPOLATOR_H_
#define DRIVERS_INTERPOLATOR_H_

#include "pico/stdlib.h"
#include "hardware/interp.h"

#define MAKE_INTEGRAL_FRACTIONAL(x) \
  int32_t x ## _integral = static_cast<int32_t>(x); \
  float x ## _fractional = x - static_cast<float>(x ## _integral);

void interpolator_init(); 
uint32_t interpolate(int32_t x1, int32_t x2, uint8_t blend_amt);

#endif  // DRIVERS_INTERPOLATOR_H_