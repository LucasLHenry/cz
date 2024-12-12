#ifndef DSP_PHASE_DISTORTER_H_
#define DSP_PHASE_DISTORTER_H_

#include "../tables/warps.h"
#include "../tables/waves.h"
#include "../utils.h"
#include "dds_core.hpp"

class PhaseDistorter {
    public:
        PhaseDistorter() {}
        ~PhaseDistorter() {}

        void init(uint16_t* warp_amt);
        void update(float freq);
        uint16_t distort();
    
    private:
        DDSCore dds_;
        uint16_t* warp_amt_;
        float blend_amt_;
        float s1, s2, o2, kink_amt;
        uint16_t kink_point;
        uint16_t kink_value(uint16_t input_phase);
};


#endif  // DSP_PHASE_DISTORTER_H_