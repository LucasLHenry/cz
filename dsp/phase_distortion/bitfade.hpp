#ifndef PHASE_DISTORTION_BITFADE_H_
#define PHASE_DISTORTION_BITFADE_H_

#include "pd_algo.hpp"
#include "../../utils.h"

class BitfadeAlgo : public PDAlgo {
    public:
        BitfadeAlgo() {}
        ~BitfadeAlgo() {}

        virtual float process_phase(float pha);

    private:
        virtual void update_params(float warp);
        float warp_;
        bool passthrough_;
};

#endif  // PHASE_DISTORTION_BITFADE_H_