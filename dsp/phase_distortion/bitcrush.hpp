#ifndef PHASE_DISTORTION_BITCRUSH_H_
#define PHASE_DISTORTION_BITCRUSH_H_

#include "pd_algo.hpp"
#include "../../utils.h"

class BitcrushAlgo : public PDAlgo {
    public:
        BitcrushAlgo() {}
        ~BitcrushAlgo() {}

        virtual float process_phase(float pha);

    private:
        virtual void update_params_();
        float slope_, inv_slope_;
        bool passthrough_;
};

#endif  // PHASE_DISTORTION_BITCRUSH_H_