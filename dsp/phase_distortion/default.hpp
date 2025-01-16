#ifndef PHASE_DISTORTION_DEFAULT_H_
#define PHASE_DISTORTION_DEFAULT_H_

#include "pd_algo.hpp"

class DefaultAlgo : public PDAlgo {
    public:
        DefaultAlgo() {}
        ~DefaultAlgo() {}

        virtual float process_phase(float pha);
        virtual void update_params(float warp);
};

#endif  // PHASE_DISTORTION_KINK_H_