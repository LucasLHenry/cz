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

        void init(float* wave_pos, uint16_t* warp_amt);
        void process(AudioDAC::Frame* buf, size_t size, float freq_hz);
    
    private:
        PhaseDistorter pd;
        float* wave_pos_;
        uint32_t xfade_margin_;
        float volume_;
        float aaf_coefficient_;
        float value_;
        const int16_t* waves_[NUM_WAVES];
};

#endif  // DSP_VARIABLE_WAVE_OSCILLATOR_H_