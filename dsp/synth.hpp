#ifndef DSP_SYNTH_H_
#define DSP_SYNTH_H_

#include "phase_distorter.hpp"
#include "phase_distortion/pd_algo.hpp"
#include "phase_distortion/all_algos.hpp"

#include "../drivers/audio_dac.hpp"
#include "../tables/waves.h"
#include "../utils.h"
#include "../ui.hpp"
#include "../tables/waves.h"

class Synth {
    public:
        Synth() {}
        ~Synth() {}

        void init(float volume, UI::Params* params);
        void process(AudioDAC::Frame* buf, size_t size);

    private:
        PhaseDistorter phase_distorter1_;
        PhaseDistorter phase_distorter2_;
        UI::Params* params_;
        float lpf_coeff_;
        float lpf_val_;
        float volume_;
        float phase_;
        float freq_;
};


#endif  // DSP_SYNTH_H_