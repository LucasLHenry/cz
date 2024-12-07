#include "variable_wave_oscillator.hpp"

void VariWaveOsc::init(uint16_t* wave_pos) {
    wave_pos_ = wave_pos;
    xfade_margin_ = 1 << (ADC_BITS - 1);
    volume_ = 0.4;
    float ctf_freq_hz = 24000;
    aaf_coefficient_ = (ctf_freq_hz / OUTPUT_SAMPLE_RATE) / (1 + (ctf_freq_hz / OUTPUT_SAMPLE_RATE));
}

void VariWaveOsc::process(AudioDAC::Frame* buf, size_t size, float freq) {
    phasor_ = static_cast<uint32_t>(freq * k_hz_phasor);
    
    // two sections: sine to tri, tri to saw
    bool in_sec_one = *wave_pos_ < xfade_margin_;
    float blend = static_cast<float>(*wave_pos_ % xfade_margin_) / xfade_margin_;

    for (uint idx = 0; idx < size; idx++) {
        accumulator_ += phasor_;
        int32_t dither_val = PRNG::centered_lcg() >> 12;
        uint32_t shifted_accumulator = (accumulator_ + dither_val) >> k_dds_downshift;
        int32_t val1, val2;
        if (in_sec_one) {
            val1 = sine_table[shifted_accumulator];
            val2 = tri_table[shifted_accumulator];
        } else {
            val1 = tri_table[shifted_accumulator];
            val2 = saw_table[shifted_accumulator];
        }
        int16_t wave_val = static_cast<int16_t>((val1 + (val2 - val1)*blend) * volume_);
        ONE_POLE(value_, wave_val, aaf_coefficient_);
        buf[idx].l = static_cast<int16_t>(value_);
        buf[idx].r = static_cast<int16_t>(value_);
    }
}