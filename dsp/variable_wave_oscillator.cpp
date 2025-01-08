#include "variable_wave_oscillator.hpp"

void VariWaveOsc::init() {
    waves_[0] = &sine_table[0];
    waves_[1] = &tri_table[0];
    waves_[2] = &saw_table[0];
    for (uint i = 0; i < NUM_RESO_WAVES; i++) {
        reso_waves_[i] = &reso_waves[i][0];
    }
}

void VariWaveOsc::update_params(float wave) {
    knob_left_ = wave < 0.5;
    if (knob_left_) wave *= 2*(NUM_RESO_WAVES - 1);
    else wave = (wave - 0.5)*2*(NUM_WAVES - 1);
    MAKE_INTEGRAL_FRACTIONAL(wave);
    wave_val_i_ = wave_integral;
    wave_val_f_ = wave_fractional;
}

int16_t VariWaveOsc::process_sample(uint32_t phase) {
    phase >>= k_dds_downshift;
    int16_t val1, val2;
    if (knob_left_) {
        val1 = reso_waves_[wave_val_i_][phase];
        val2 = reso_waves_[wave_val_i_+1][phase];
    } else {
        val1 = waves_[wave_val_i_][phase];
        val2 = waves_[wave_val_i_+1][phase];
    }
    return xfade(val1, val2, wave_val_f_);
}