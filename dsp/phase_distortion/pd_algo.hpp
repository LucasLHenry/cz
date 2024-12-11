#ifndef DSP_PHASE_DISTORTION_ALGORITHM_H_
#define DSP_PHASE_DISTORTION_ALGORITHM_H_

#include <stdint.h>

class PDAlgo {
    public:
        PDAlgo() {}
        virtual ~PDAlgo();
        virtual void update(float warp_amt);
        virtual uint32_t get_phase(uint32_t input_phase);
};


#endif  // DSP_PHASE_DISTORTION_ALGORITHM_H_