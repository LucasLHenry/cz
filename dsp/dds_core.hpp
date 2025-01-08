#ifndef DSP_DDS_CORE_H_
#define DSP_DDS_CORE_H_

#include <stdint.h>
#include "../tables/waves.h"
#include "../utils.h"

class DDSCore {
    public:
        DDSCore() {}
        ~DDSCore() {}

        void init();
        uint32_t gen_phase();
        void update_params(float freq_hz);
    
    private:
        uint32_t acc_, pha_;
};

#endif  // DSP_DDS_CORE_H_