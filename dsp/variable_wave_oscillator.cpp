#include "variable_wave_oscillator.hpp"

void VariWaveOsc::init() {
    for (uint i = 0; i < NUM_RESO_WAVES; i++) {
        reso_waves_[i] = &reso_waves[NUM_RESO_WAVES-1 - i][0];
    }
}

void VariWaveOsc::update_params(float wave) {
    wave *= NUM_RESO_WAVES - 1;
    MAKE_INTEGRAL_FRACTIONAL(wave);
    wave_val_i_ = wave_integral;
    wave_val_f_ = wave_fractional;
}

int16_t VariWaveOsc::process_sample(float phase) {
    float val1 = interpolate_wrap(reso_waves_[wave_val_i_], phase, k_wave_table_len);
    float val2 = interpolate_wrap(reso_waves_[wave_val_i_+1], phase, k_wave_table_len);
    return static_cast<int16_t>((val1 + (val2 - val1)*wave_val_f_)*INT16_MAX);
}