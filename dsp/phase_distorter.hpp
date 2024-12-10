#ifndef DSP_PHASE_DISTORTER_H_
#define DSP_PHASE_DISTORTER_H_

#include "../tables/warps.h"
#include "../tables/waves.h"
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
        float s1, s2, o2, kink_amt;
        uint16_t kink_point;
        uint16_t kink_value(uint16_t input_phase);
};


#endif  // DSP_PHASE_DISTORTER_H_