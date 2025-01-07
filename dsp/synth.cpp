#include "synth.hpp"

void Synth::init() {
    dds_core_.init(true);
    phase_distorter_.init();
    osc_.init();
}

void Synth::process(AudioDAC::Frame* buf, size_t size, float freq, float wave, float warp, float algo) {
    dds_core_.update_params(freq);
    phase_distorter_.update_params(warp, algo);
    osc_.update_params(wave);
    
    for (uint i = 0; i < size; i++) {
        uint32_t pha = dds_core_.gen_phase();
        pha = phase_distorter_.process_phase(pha);
        int16_t val = osc_.process_sample(pha);
        buf[i].l = val;
        buf[i].r = val;
    }
}