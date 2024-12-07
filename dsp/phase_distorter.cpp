#include "phase_distorter.hpp"

void PhaseDistorter::init(uint16_t* warp_amt) {
    warp_amt_ = warp_amt;
}

void PhaseDistorter::update() {
    blend_amt_ = *warp_amt_ / 4096.0;
}

uint16_t PhaseDistorter::distort(uint16_t input_phase) {
    uint16_t distorted_phase = warp_kink_table[input_phase];
    return xfade(input_phase, distorted_phase, blend_amt_);
}