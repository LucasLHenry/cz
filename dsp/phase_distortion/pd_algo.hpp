#ifndef PHASE_DISTORTION_ALGO_H_
#define PHASE_DISTORTION_ALGO_H_

#include <stdint.h>
#include <math.h>

class PDAlgo {
    public:
        PDAlgo() {}
        virtual ~PDAlgo();

        void update_params(float warp);
        virtual float process_phase(float pha);
        float max_warp = 1.0;
    
    protected:
        float warp_;
        virtual void update_params_();
    
    private:
        bool started_;
};


#endif  // PHASE_DISTORTION_ALGO_H_