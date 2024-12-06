#ifndef DSP_VARIABLE_WAVE_OSCILLATOR_H_
#define DSP_VARIABLE_WAVE_OSCILLATOR_H_

#include "../drivers/audio_dac.hpp"
#include "../tables/waves.h"
#include "../drivers/interpolator.hpp"
#include "../hw_config.h"

class VariWaveOsc {
    public:
        VariWaveOsc() {}
        ~VariWaveOsc() {}

        void init(uint16_t* wave_pos);
        void process(AudioDAC::Frame* buf, size_t size, float freq_hz);
    
    private:
        uint32_t accumulator_;
        uint32_t phasor_;
        uint16_t* wave_pos_;
        uint32_t xfade_margin_;
        float volume_;
};

#endif  // DSP_VARIABLE_WAVE_OSCILLATOR_H_