#ifndef PHASE_DISTORTION_ALGO_H_
#define PHASE_DISTORTION_ALGO_H_

#include <stdint.h>

class PDAlgo {
    public:
        PDAlgo() {}
        virtual ~PDAlgo();

        virtual void update_params(float warp);
        virtual uint32_t process_phase(uint32_t pha);
};


#endif  // PHASE_DISTORTION_ALGO_H_