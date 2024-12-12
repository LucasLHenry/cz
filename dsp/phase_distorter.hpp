#ifndef DSP_PHASE_DISTORTER_H_
#define DSP_PHASE_DISTORTER_H_

#include "../tables/warps.h"
#include "../tables/waves.h"
#include "../utils.h"
#include "dds_core.hpp"
#include "phase_distortion/pd_algo.hpp"

class PhaseDistorter {
    public:
        PhaseDistorter() {}
        ~PhaseDistorter() {}

        void init();
        void update(float freq, float warp);
        uint16_t distort();
    
    private:
        DDSCore dds_;
        float max_warp_;
        float s1, s2, o2, kink_amt;
        uint32_t kink_point;
        uint32_t kink_value(uint32_t input_phase);
};


#endif  // DSP_PHASE_DISTORTER_H_