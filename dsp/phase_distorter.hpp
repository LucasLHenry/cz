#ifndef DSP_PHASE_DISTORTER_H_
#define DSP_PHASE_DISTORTER_H_

#include "../tables/warps.h"
#include "../tables/waves.h"
#include "../utils.h"
#include "dds_core.hpp"
#include "phase_distortion/pd_algo.hpp"
#include "phase_distortion/kink.hpp"

#define NUM_PD_ALGOS 1

class PhaseDistorter {
    public:
        PhaseDistorter() {}
        ~PhaseDistorter() {}

        void init(float* warp_amt);
        void update_params(float freq);
        uint16_t get_phase();
    
    private:
        DDSCore dds_;
        float* warp_amt_;
        PDAlgo* algos_[NUM_PD_ALGOS];
};

#endif  // DSP_PHASE_DISTORTER_H_