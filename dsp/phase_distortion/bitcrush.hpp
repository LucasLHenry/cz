#ifndef PHASE_DISTORTION_BITCRUSH_H_
#define PHASE_DISTORTION_BITCRUSH_H_

#include "pd_algo.hpp"
#include "../../rplib/utils/utils.h"

class BitcrushAlgo : public PDAlgo {
    public:
        BitcrushAlgo() {}
        ~BitcrushAlgo() {}

        virtual float process_phase(float pha);

    private:
        virtual void update_params(float warp);
        float slope_, inv_slope_;
        bool passthrough_;
};

#endif  // PHASE_DISTORTION_BITCRUSH_H_