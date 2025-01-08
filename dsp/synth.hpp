#ifndef DSP_SYNTH_H_
#define DSP_SYNTH_H_

#include "dds_core.hpp"
#include "phase_distorter.hpp"
#include "variable_wave_oscillator.hpp"
#include "../drivers/audio_dac.hpp"
#include "../tables/waves.h"
#include "../utils.h"

class Synth {
    public:
        Synth() {}
        ~Synth() {}

        void init();
        void process(AudioDAC::Frame* buf, size_t size, float freq, float wave, float warp, float algo);

    private:
        DDSCore dds_core_;
        PhaseDistorter phase_distorter_;
        VariWaveOsc osc_;
};


#endif  // DSP_SYNTH_H_