#ifndef DSP_DDS_CORE_H_
#define DSP_DDS_CORE_H_

#include <stdint.h>
#include "../tables/waves.h"
#include "prng.hpp"

class DDSCore {
    public:
        DDSCore() {}
        ~DDSCore() {}

        void init(bool dither);
        uint32_t update();
        void set_freq(float freq_hz);
    
    private:
        bool dither_;
        uint32_t acc_, pha_;
};

#endif  // DSP_DDS_CORE_H_