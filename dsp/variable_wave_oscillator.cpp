#include "variable_wave_oscillator.hpp"

void VariWaveOsc::init() {
    for (uint i = 0; i < NUM_RESO_WAVES; i++) {
        reso_waves_[i] = &reso_waves[NUM_RESO_WAVES - 1 - i][0];
    }
}

void VariWaveOsc::update_params(float wave) {
    wave *= NUM_RESO_WAVES - 1;
    MAKE_INTEGRAL_FRACTIONAL(wave);
    wave_val_i_ = wave_integral;
    wave_val_f_ = wave_fractional;
}

int16_t VariWaveOsc::process_sample(uint32_t phase) {
    phase >>= k_dds_downshift;
    float remainder = (phase % k_dds_mask) * k_dds_inverse_remainder;
    int16_t val1, val2;
    val1 = xfade(reso_waves_[wave_val_i_][phase], reso_waves_[wave_val_i_][phase+1], remainder);
    val2 = xfade(reso_waves_[wave_val_i_+1][phase], reso_waves_[wave_val_i_+1][phase+1], remainder);
    return xfade(val1, val2, wave_val_f_);
}