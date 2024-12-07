#ifndef DSP_PHASE_DISTORTER_H_
#define DSP_PHASE_DISTORTER_H_

#include "../tables/warps.h"
#include "../utils.h"

class PhaseDistorter {
    public:
        PhaseDistorter() {}
        ~PhaseDistorter() {}

        void init(uint16_t* warp_amt);
        void update();
        uint16_t distort(uint16_t input_phase);
    
    private:
        uint16_t* warp_amt_;
        float blend_amt_;
};


#endif  // DSP_PHASE_DISTORTER_H_