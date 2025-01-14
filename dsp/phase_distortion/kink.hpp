#ifndef PHASE_DISTORTION_KINK_H_
#define PHASE_DISTORTION_KINK_H_

#include "pd_algo.hpp"

class KinkAlgo : public PDAlgo {
    public:
        KinkAlgo() {}
        ~KinkAlgo() {}

        virtual float process_phase(float pha);

    private:
        virtual void update_params_();
        float s1, s2, o2;
        float kink_point;
};

#endif  // PHASE_DISTORTION_KINK_H_