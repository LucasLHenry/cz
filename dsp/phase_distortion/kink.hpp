#ifndef PHASE_DISTORTION_KINK_H_
#define PHASE_DISTORTION_KINK_H_

#include "pd_algo.hpp"

class KinkAlgo : public PDAlgo {
    public:
        KinkAlgo() {}
        ~KinkAlgo() {}

        virtual uint32_t process_phase(uint32_t pha);

    private:
        virtual void _update_params();
        float s1, s2, o2;
        uint32_t kink_point;
};

#endif  // PHASE_DISTORTION_KINK_H_