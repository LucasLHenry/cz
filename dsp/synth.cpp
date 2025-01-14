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
HighSyncAlgo sync_high1;

void Synth::init(float volume, UI::Params* params) {
    volume_ = volume;
    params_ = params;
    PDAlgo* algos1[4] = {
        &kink1,
        &double_kink1,
        &sync1,
        &sync_high1,
    };
    PDAlgo* algos2[2] = {
        &kink2,
        &double_kink2,
    };
    phase_distorter1_.init(algos1, 4);
    // phase_distorter2_.init(algos2, 2);
    osc_.init();
    lpf_coeff_ = ewma_filter_coefficient(20000);
    hpf_coeff_ = ewma_filter_coefficient(10);
}

void Synth::process(AudioDAC::Frame* buf, size_t size) {
    freq_ = params_->freq_hz * k_hz_phasor_f;
    phase_distorter1_.update_params(params_->warp, params_->algo);
    // phase_distorter2_.update_params(params.warp, params.algo);
    osc_.update_params(params_->wave);
    
    for (uint i = 0; i < size; i++) {
        phase_ += freq_;
        if (phase_ > 1.0) phase_ -= 1.0;
        // pha = phase_distorter1_.process_phase(pha);
        // pha = phase_distorter2_.process_phase(pha);
        // pha += rand_i32() >> 13;  // dithering
        int16_t val = osc_.process_sample(phase_);
        // ONE_POLE_LPF(lpf_val_, val, lpf_coeff_);
        float out_val = val;

        out_val *= volume_;
        buf[i].l = out_val;
        buf[i].r = out_val;
    }
}