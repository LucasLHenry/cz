#ifndef PHASE_DISTORTION_SINE_FOLD_H_
#define PHASE_DISTORTION_SINE_FOLD_H_

#include "pd_algo.hpp"
#include "../../utils.h"
#include "../../tables/warps.h"

class SinefoldAlgo : public PDAlgo {
    public:
        SinefoldAlgo();
        ~SinefoldAlgo() {}

        virtual float process_phase(float pha);
        virtual void update_params(float warp);
        
    private:
        float warp_;
};

#endif  // PHASE_DISTORTION_SINE_FOLD_H_