#include "phase_distorter.hpp"

void PhaseDistorter::init(uint16_t* warp_amt) {
    warp_amt_ = warp_amt;
    dds_.init(true);
}

void PhaseDistorter::update(float freq) {
    dds_.set_freq(freq);
    blend_amt_ = (*warp_amt_ / 4096.0)*0.8;
    s1 = 1.0 / (1.0 - blend_amt_);
    s2 = 1.0 / (1.0 + blend_amt_);
    o2 = UINT32_MAX * (1.0 - s2*(1.0 - blend_amt_)) / 2.0;
    kink_point = static_cast<uint32_t>(UINT32_MAX * (1.0 - blend_amt_) / 2.0);
}

uint16_t PhaseDistorter::distort() {
    uint32_t phase = dds_.update();
    return kink_value(phase) >> k_dds_downshift;
}

uint32_t PhaseDistorter::kink_value(uint32_t input_phase) {
    if (input_phase < kink_point) {
        return static_cast<uint32_t>(s1 * input_phase);
    } else {
        return static_cast<uint32_t>(s2 * input_phase + o2);
    }
}