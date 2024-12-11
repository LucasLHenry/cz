#include "phase_distorter.hpp"

Kink kink_;

void PhaseDistorter::init(float* warp_amt) {
    warp_amt_ = warp_amt;
    dds_.init(true);
    algos_[0] = &kink_;
}

void PhaseDistorter::update_params(float freq) {
    dds_.set_freq(freq);
    algos_[0]->update(*warp_amt_);
}

uint16_t PhaseDistorter::get_phase() {
    uint32_t pha = dds_.update();
    return pha >> k_dds_downshift;//algos_[0]->get_phase(pha) >> k_dds_downshift;
    // return xfade(pha, kink_value(input_phase), blend_amt_); // + (rand_i32() >> 30);
}

// uint16_t PhaseDistorter::kink_value(uint16_t input_phase) {
//     if (input_phase < kink_point) {
//         return static_cast<uint16_t>(s1 * input_phase);
//     } else {
//         return static_cast<uint16_t>(s2 * input_phase + o2);
//     }
// }