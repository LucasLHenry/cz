#ifndef PHASE_DISTORTION_DOUBLE_KINK_H_
#define PHASE_DISTORTION_DOUBLE_KINK_H_

#include "pd_algo.hpp"
#include "../../rplib/utils/utils.h"

class DoubleKinkAlgo : public PDAlgo {
    public:
        DoubleKinkAlgo();
        ~DoubleKinkAlgo() {}

        virtual float process_phase(float pha);
        virtual void update_params(float warp);
        
    private:
        float interp_;
        float kink_point_1_, kink_point_2_;
        float offset_1_, offset_2_;
};

#endif  // PHASE_DISTORTION_DOUBLE_KINK_H_