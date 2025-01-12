#ifndef PHASE_DISTORTION_ALGO_H_
#define PHASE_DISTORTION_ALGO_H_

#include <stdint.h>
#include <math.h>

class PDAlgo {
    public:
        PDAlgo() {}
        virtual ~PDAlgo();

        void update_params(float warp);
        virtual uint32_t process_phase(uint32_t pha);
    
    protected:
        float _warp;
        virtual void _update_params();
    
    private:
        bool _started;
};


#endif  // PHASE_DISTORTION_ALGO_H_