#ifndef DSP_PHASE_DISTORTER_H_
#define DSP_PHASE_DISTORTER_H_

#include <pico/stdlib.h>

#include "../tables/warps.h"
#include "../tables/waves.h"
#include "../rplib/utils/utils.h"
#include "phase_distortion/pd_algo.hpp"

#define MAX_NUM_ALGOS 12

class PhaseDistorter {
    public:
        PhaseDistorter() {}
        ~PhaseDistorter() {}

        void init(PDAlgo** algos, size_t num_algos);
        void update_params(float warp, float algo);
        float process_phase(float pha);
    
    private:
        PDAlgo* algos_[MAX_NUM_ALGOS];
        uint32_t algo_idx_;
        float algo_xfade_amt_;
        uint num_algos_;
};


#endif  // DSP_PHASE_DISTORTER_H_