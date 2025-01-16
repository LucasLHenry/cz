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
    PDAlgo* algos1[6] = {
        &default1,
        &kink1,
        &double_kink1,
        &sync1,
        &sync_high1,
        &reverse1,
    };
    PDAlgo* algos2[2] = {
        &kink2,
        &double_kink2,
    };
    phase_distorter1_.init(algos1, 6);
    phase_distorter2_.init(algos2, 2);
    lpf_coeff_ = ewma_filter_coefficient(20000);
    hpf_coeff_ = ewma_filter_coefficient(10);
}

void Synth::process(AudioDAC::Frame* buf, size_t size) {
    // update params
    freq_ = params_->freq_hz * k_hz_phasor_f;
    phase_distorter1_.update_params(params_->warp, params_->algo);
    phase_distorter2_.update_params(1.0 - params_->warp, params_->algo);
    float wave = params_->wave * (NUM_RESO_WAVES - 1);
    MAKE_INTEGRAL_FRACTIONAL(wave);
    
    for (uint i = 0; i < size; i++) {
        // phase accumulation
        phase_ += freq_;
        if (phase_ > 1.0) phase_ -= 1.0;

        // phase distortion
        float distorted_phase = phase_distorter1_.process_phase(phase_);
        distorted_phase = phase_distorter2_.process_phase(distorted_phase);
        
        // waveform generation
        float val1 = interpolate(reso_waves[wave_integral], distorted_phase, k_wave_table_len);
        float val2 = interpolate(reso_waves[wave_integral+1], distorted_phase, k_wave_table_len);
        int16_t val = static_cast<int16_t>((val1 + (val2 - val1)*wave_fractional)*INT16_MAX);

        // post-processing and output
        ONE_POLE_LPF(lpf_val_, val, lpf_coeff_);
        lpf_val_ *= volume_;
        buf[i].l = lpf_val_;
        buf[i].r = lpf_val_;
    }
}