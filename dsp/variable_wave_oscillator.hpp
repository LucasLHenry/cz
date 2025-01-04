#ifndef DSP_VARIABLE_WAVE_OSCILLATOR_H_
#define DSP_VARIABLE_WAVE_OSCILLATOR_H_

#include "../drivers/audio_dac.hpp"
#include "../tables/waves.h"
#include "../hw_config.h"
#include "../utils.h"
#include "dds_core.hpp"
#include "phase_distorter.hpp"

#define NUM_WAVES 3

#define _RESO_TABLE_NAME() RESO_WAVE_TABLE_NAME
#define _VALUE(x) x
#define RESO_TABLE(x) _RESO_TABLE_NAME() ## _VALUE(x)

class VariWaveOsc {
    public:
        VariWaveOsc() {}
        ~VariWaveOsc() {}

        void init();
        void process(AudioDAC::Frame* buf, size_t size, float freq, float wave, float warp, float algo);
    
    private:
        PhaseDistorter pd;
        uint32_t xfade_margin_;
        float volume_;
        float aaf_coefficient_;
        float value_;
        const int16_t* waves_[NUM_WAVES];
        const int16_t* reso_waves_[NUM_RESO_WAVES];
};

#endif  // DSP_VARIABLE_WAVE_OSCILLATOR_H_