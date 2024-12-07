#ifndef DSP_PRNG_H_
#define DSP_PRNG_H_

#include <stdint.h>

namespace PRNG {
    uint32_t lcg();
    int32_t centered_lcg();
}

#endif  // DSP_PRNG_H_