#ifndef PHASE_DISTORTION_DOUBLE_KINK_H_
#define PHASE_DISTORTION_DOUBLE_KINK_H_

#include "pd_algo.hpp"
#include "../../utils.h"

class DoubleKinkAlgo : public PDAlgo {
    public:
        DoubleKinkAlgo();
        ~DoubleKinkAlgo() {}

        virtual void update_params(float warp);
        virtual uint32_t process_phase(uint32_t pha);

    private:
        float interp_;
        uint32_t kink_point_1_, kink_point_2_;
        uint32_t offset_1_, offset_2_;
};

#endif  // PHASE_DISTORTION_DOUBLE_KINK_H_