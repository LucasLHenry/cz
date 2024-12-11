#ifndef DSP_PHASE_DISTORTION_KINK_H_
#define DSP_PHASE_DISTORTION_KINK_H_

#include "pd_algo.hpp"
#include "../../tables/waves.h"

class Kink: public PDAlgo {
    public:
        Kink() {}
        ~Kink() {}
        
        virtual void update(float warp_amt);
        virtual uint32_t get_phase(uint32_t input_phase);

    private:
        float s1, s2, o2, kink_amt;
        uint32_t kink_point;
};


#endif  // DSP_PHASE_DISTORTION_KINK_H_