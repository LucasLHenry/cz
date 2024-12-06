#include "variable_wave_oscillator.hpp"

void VariWaveOsc::init(uint32_t* wave_pos) {
    wave_pos_ = wave_pos;
}

void VariWaveOsc::process(AudioDAC::Frame* buf, size_t size, float freq) {
    phasor_ = static_cast<uint32_t>(freq * k_hz_phasor);
    float wave_amt = 2 * (*wave_pos_ / 4096.0);
    uint32_t wave_idx = static_cast<uint32_t>(wave_amt);
    float wave_fractional = wave_amt - wave_idx;
    for (uint idx = 0; idx < size; idx++) {
        accumulator_ += phasor_;
        uint32_t shifted_accumulator = accumulator_ >> k_dds_downshift;
        int32_t val1, val2;
        if (wave_idx < 1) {
            val1 = sine_table[shifted_accumulator];
            val2 = tri_table[shifted_accumulator];
        } else {
            val1 = tri_table[shifted_accumulator];
            val2 = saw_table[shifted_accumulator];
        }
        int16_t wave_val = static_cast<int32_t>(val1 + (val2 - val1) * wave_fractional) >> 16;
        buf[idx].l = static_cast<int16_t>(wave_val * 0.7);
        buf[idx].r = static_cast<int16_t>(wave_val * 0.7);
    }
}

/*
sine
tri
saw
*/