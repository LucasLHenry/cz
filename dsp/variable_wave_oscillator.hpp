#ifndef DSP_VARIABLE_WAVE_OSCILLATOR_H_
#define DSP_VARIABLE_WAVE_OSCILLATOR_H_

#include "../drivers/audio_dac.hpp"
#include "../tables/waves.h"
#include "../hw_config.h"
#include "../utils.h"
#include "dds_core.hpp"
#include "phase_distorter.hpp"

class VariWaveOsc {
    public:
        VariWaveOsc() {}
        ~VariWaveOsc() {}

        void init(uint16_t* wave_pos, uint16_t* warp_amt);
        void process(AudioDAC::Frame* buf, size_t size, float freq_hz);
    
    private:
        DDSCore dds;
        PhaseDistorter pd;
        uint16_t* wave_pos_;
        uint32_t xfade_margin_;
        float volume_;
        float aaf_coefficient_;
        float value_;
};

#endif  // DSP_VARIABLE_WAVE_OSCILLATOR_H_