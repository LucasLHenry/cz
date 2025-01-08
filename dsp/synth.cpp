#include "synth.hpp"

void Synth::init(float volume) {
    volume_ = volume;
    dds_core_.init();
    phase_distorter_.init();
    osc_.init();
    lpf_coeff_ = ewma_filter_coefficient(24000);
    hpf_coeff_ = ewma_filter_coefficient(10);
}

void Synth::process(AudioDAC::Frame* buf, size_t size, UI::Params params) {
    dds_core_.update_params(params.freq_hz);
    phase_distorter_.update_params(params.warp, params.algo);
    osc_.update_params(params.wave);
    
    for (uint i = 0; i < size; i++) {
        uint32_t pha = dds_core_.gen_phase();
        pha = phase_distorter_.process_phase(pha);
        // pha += rand_i32() >> 12;  // dithering
        int16_t val = osc_.process_sample(pha);
        ONE_POLE_LPF(lpf_val_, val, lpf_coeff_);
        // ONE_POLE_HPF(hpf_val_, lpf_val_, hpf_coeff_);
        float out_val = lpf_val_;

        out_val *= volume_;
        buf[i].l = out_val;
        buf[i].r = out_val;
    }
}