#include "phase_distorter.hpp"

void PhaseDistorter::init(uint16_t* warp_amt) {
    warp_amt_ = warp_amt;
    dds_.init(true);
}

void PhaseDistorter::update(float freq) {
    dds_.set_freq(freq);
    blend_amt_ = *warp_amt_ / 4096.0;
    kink_amt = blend_amt_ * 0.7;
    s1 = (1 - kink_amt) / (1 + kink_amt);
    s2 = (1 + kink_amt) / (1 - kink_amt);
    o2 = (k_wave_table_len/2) * (1 - kink_amt - s2*(1 + kink_amt));
    kink_point = static_cast<uint16_t>(k_wave_table_len * (0.5 + kink_amt/2));
}

uint16_t PhaseDistorter::distort() {
    uint16_t phase = dds_.update();
    return kink_value(phase);
}

uint16_t PhaseDistorter::kink_value(uint16_t input_phase) {
    if (input_phase < kink_point) {
        return static_cast<uint16_t>(s1 * input_phase);
    } else {
        return static_cast<uint16_t>(s2 * input_phase + o2);
    }
}