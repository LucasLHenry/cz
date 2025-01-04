#include "variable_wave_oscillator.hpp"

void VariWaveOsc::init() {
    xfade_margin_ = 1 << (ADC_BITS - 1);
    volume_ = 0.4;
    float ctf_freq_hz = 24000;
    aaf_coefficient_ = (ctf_freq_hz / OUTPUT_SAMPLE_RATE) / (1 + (ctf_freq_hz / OUTPUT_SAMPLE_RATE));
    pd.init();
    waves_[0] = &sine_table[0];
    waves_[1] = &tri_table[0];
    waves_[2] = &saw_table[0];
    for (uint i = 0; i < NUM_RESO_WAVES; i++) {
        reso_waves_[i] = &reso_waves[i][0];
    }
}

void VariWaveOsc::process(AudioDAC::Frame* buf, size_t size, float freq, float wave, float warp, float algo) {
    pd.update(freq, warp, algo);
    bool resonant = wave < 0.5;
    if (resonant) wave *= 2*(NUM_RESO_WAVES - 1);
    else wave = (wave - 0.5)*2*(NUM_WAVES - 1);
    MAKE_INTEGRAL_FRACTIONAL(wave);

    for (uint idx = 0; idx < size; idx++) {
        uint32_t shifted_accumulator = pd.distort();
        int16_t val1, val2;
        if (resonant) {
            val1 = reso_waves_[wave_integral][shifted_accumulator];
            val2 = reso_waves_[wave_integral+1][shifted_accumulator];
        } else {
            val1 = waves_[wave_integral][shifted_accumulator];
            val2 = waves_[wave_integral+1][shifted_accumulator];
        }

        int16_t wave_val = xfade(val1, val2, wave_fractional) * volume_;
        ONE_POLE(value_, wave_val, aaf_coefficient_);

        buf[idx].l = static_cast<int16_t>(value_);
        buf[idx].r = static_cast<int16_t>(value_);
    }
}