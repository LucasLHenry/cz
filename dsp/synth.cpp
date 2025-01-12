#include "synth.hpp"

DefaultAlgo default1;
KinkAlgo kink1;
SyncAlgo sync1;
ReverseAlgo reverse1;
DoubleKinkAlgo double_kink1;
KinkAlgo kink2;
SyncAlgo sync2;
ReverseAlgo reverse2;
DoubleKinkAlgo double_kink2;

void Synth::init(float volume) {
    volume_ = volume;
    dds_core_.init();
    PDAlgo* algos1[3] = {
        &default1,
        &kink1,
        &double_kink1,
    };
    PDAlgo* algos2[2] = {
        &reverse2,
        &sync2,
    };
    phase_distorter1_.init(algos1, 3);
    phase_distorter2_.init(algos2, 2);
    osc_.init();
    lpf_coeff_ = ewma_filter_coefficient(24000);
    hpf_coeff_ = ewma_filter_coefficient(10);
}

void Synth::process(AudioDAC::Frame* buf, size_t size, UI::Params params) {
    dds_core_.update_params(params.freq_hz);
    phase_distorter1_.update_params(params.warp, params.algo);
    phase_distorter2_.update_params(1 - params.warp, params.algo);
    osc_.update_params(params.wave);
    
    for (uint i = 0; i < size; i++) {
        uint32_t pha = dds_core_.gen_phase();
        pha = phase_distorter1_.process_phase(pha);
        pha = phase_distorter2_.process_phase(pha);
        pha += rand_i32() >> 12;  // dithering
        int16_t val = osc_.process_sample(pha);
        // ONE_POLE_LPF(lpf_val_, val, lpf_coeff_);
        // float out_val = lpf_val_;

        val *= volume_;
        buf[i].l = val;
        buf[i].r = val;
    }
}