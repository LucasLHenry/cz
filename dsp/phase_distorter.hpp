#ifndef DSP_PHASE_DISTORTER_H_
#define DSP_PHASE_DISTORTER_H_

#include "../tables/warps.h"
#include "../tables/waves.h"
#include "../utils.h"
#include "phase_distortion/pd_algo.hpp"
#include "phase_distortion/kink.hpp"
#include "phase_distortion/sync.hpp"
#include "phase_distortion/reverse.hpp"
#include "phase_distortion/double_kink.hpp"

#define NUM_ALGOS 4

class PhaseDistorter {
    public:
        PhaseDistorter() {}
        ~PhaseDistorter() {}

        void init();
        void update_params(float warp, float algo);
        uint32_t process_phase(uint32_t pha);
    
    private:
        PDAlgo* algos_[NUM_ALGOS];
        float max_warp_;
        uint32_t algo_idx_;
        float algo_xfade_amt_;
};


#endif  // DSP_PHASE_DISTORTER_H_