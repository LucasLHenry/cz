#ifndef DSP_PHASE_DISTORTER_H_
#define DSP_PHASE_DISTORTER_H_

#include "../tables/warps.h"
#include "../tables/waves.h"
#include "../utils.h"
#include "dds_core.hpp"
#include "phase_distortion/pd_algo.hpp"
#include "phase_distortion/kink.hpp"
#include "phase_distortion/sync.hpp"
#include "phase_distortion/reverse.hpp"

#define NUM_ALGOS 1

class PhaseDistorter {
    public:
        PhaseDistorter() {}
        ~PhaseDistorter() {}

        void init();
        void update(float freq, float warp);
        uint16_t distort();
    
    private:
        DDSCore dds_;
        PDAlgo* algos_[NUM_ALGOS];
        float max_warp_;
};


#endif  // DSP_PHASE_DISTORTER_H_