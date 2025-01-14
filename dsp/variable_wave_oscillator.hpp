#ifndef DSP_VARIABLE_WAVE_OSCILLATOR_H_
#define DSP_VARIABLE_WAVE_OSCILLATOR_H_

#include "../drivers/audio_dac.hpp"
#include "../tables/waves.h"
#include "../hw_config.h"
#include "../utils.h"
#include "dds_core.hpp"
#include "phase_distorter.hpp"

#define NUM_WAVES 3

class VariWaveOsc {
    public:
        VariWaveOsc() {}
        ~VariWaveOsc() {}

        void init();
        void update_params(float wave);
        int16_t process_sample(float phase);
    
    private:
        const float* reso_waves_[NUM_RESO_WAVES];
        int32_t wave_val_i_;
        float wave_val_f_;
};

#endif  // DSP_VARIABLE_WAVE_OSCILLATOR_H_