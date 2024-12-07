#ifndef DSP_VARIABLE_WAVE_OSCILLATOR_H_
#define DSP_VARIABLE_WAVE_OSCILLATOR_H_

#include "../drivers/audio_dac.hpp"
#include "../tables/waves.h"
#include "../hw_config.h"
#include "prng.hpp"
#include "dds_core.hpp"

#define ONE_POLE(out, in, coefficient) out += (in - out) * coefficient

class VariWaveOsc {
    public:
        VariWaveOsc() {}
        ~VariWaveOsc() {}

        void init(uint16_t* wave_pos);
        void process(AudioDAC::Frame* buf, size_t size, float freq_hz);
    
    private:
        DDSCore dds;
        uint16_t* wave_pos_;
        uint32_t xfade_margin_;
        float volume_;
        float aaf_coefficient_;
        float value_;
};

#endif  // DSP_VARIABLE_WAVE_OSCILLATOR_H_