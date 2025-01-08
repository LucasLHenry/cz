#ifndef DSP_SYNTH_H_
#define DSP_SYNTH_H_

#include "dds_core.hpp"
#include "phase_distorter.hpp"
#include "variable_wave_oscillator.hpp"
#include "../drivers/audio_dac.hpp"
#include "../tables/waves.h"
#include "../utils.h"
#include "../ui.hpp"

class Synth {
    public:
        Synth() {}
        ~Synth() {}

        void init(float volume);
        void process(AudioDAC::Frame* buf, size_t size, UI::Params params);

    private:
        DDSCore dds_core_;
        PhaseDistorter phase_distorter_;
        VariWaveOsc osc_;
        float lpf_coeff_, hpf_coeff_;
        int16_t lpf_val_, hpf_val_;
        float volume_;
};


#endif  // DSP_SYNTH_H_