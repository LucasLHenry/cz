#ifndef PHASE_DISTORTION_KINK_H_
#define PHASE_DISTORTION_KINK_H_

#include "pd_algo.hpp"

class KinkAlgo : public PDAlgo {
    public:
        KinkAlgo() {}
        ~KinkAlgo() {}

        virtual float process_phase(float pha);
        virtual void update_params(float warp);

    private:
        float s1, s2, o2;
        float kink_point;
};

#endif  // PHASE_DISTORTION_KINK_H_