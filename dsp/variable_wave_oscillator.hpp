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
        int16_t process_sample(uint32_t phase);
    
    private:
        const int16_t* waves_[NUM_WAVES];
        const int16_t* reso_waves_[NUM_RESO_WAVES];
        bool knob_left_;
        int32_t wave_val_i_;
        float wave_val_f_;
};

#endif  // DSP_VARIABLE_WAVE_OSCILLATOR_H_