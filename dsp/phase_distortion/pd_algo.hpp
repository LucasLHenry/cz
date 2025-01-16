#ifndef PHASE_DISTORTION_ALGO_H_
#define PHASE_DISTORTION_ALGO_H_

#include <stdint.h>
#include <math.h>

class PDAlgo {
    public:
        PDAlgo() {}
        virtual ~PDAlgo();

        virtual void update_params(float warp);
        virtual float process_phase(float pha);
    
    protected:
        bool passthrough_;
        float prev_warp_;
};


#endif  // PHASE_DISTORTION_ALGO_H_