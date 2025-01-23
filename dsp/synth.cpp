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
BitcrushAlgo bitcrush1;
BitfadeAlgo bitfade1;
SinefoldAlgo sinefold1;

void Synth::init(float volume, UI::Params* params) {
    volume_ = volume;
    params_ = params;
    PDAlgo* algos1[7] = {
        &sinefold1,
        &double_kink1,
        &reverse1,
        &sync1,
        &sync_high1,
        &bitfade1,
        &bitcrush1,
    };
    PDAlgo* algos2[3] = {
        &default1,
        &bitfade1,
        &bitcrush1,
    };
    phase_distorter1_.init(algos1, 7);
    phase_distorter2_.init(algos2, 3);
    lpf_coeff_ = ewma_filter_coefficient(20000);
}

void Synth::process(AudioDAC::Frame* buf, size_t size) {
    // update params
    freq_ = params_->freq_hz * k_hz_phasor_f;
    phase_distorter1_.update_params(params_->warp, params_->algo);
    // phase_distorter2_.update_params(params_->warp, params_->algo);
    float wave = params_->wave * (NUM_RESO_WAVES - 1);
    MAKE_INTEGRAL_FRACTIONAL(wave);
    
    for (uint i = 0; i < size; i++) {
        // phase accumulation
        phase_ += freq_;
        if (phase_ > 1.0) phase_ -= 1.0;

        // phase distortion
        float distorted_phase = phase_distorter1_.process_phase(phase_);
        // distorted_phase = phase_distorter2_.process_phase(distorted_phase);

        // distorted_phase += params_->phase_offset;
        // if (distorted_phase > 1.0) distorted_phase -= 1.0;
        
        // waveform generation
        float val1 = interpolate(reso_waves[wave_integral], distorted_phase, k_wave_table_len);
        float val2 = interpolate(reso_waves[wave_integral+1], distorted_phase, k_wave_table_len);
        float val = val1 + (val2 - val1)*wave_fractional;

        // post-processing and output
        ONE_POLE_LPF(lpf_val_, val, lpf_coeff_);
        int16_t out_val = soft_limit(lpf_val_ * params_->volume)*0.4 * INT16_MAX;
        buf[i].l = out_val;
        buf[i].r = out_val;
    }
}