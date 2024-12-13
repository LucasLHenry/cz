#include "phase_distorter.hpp"


KinkAlgo kink;
SyncAlgo sync;
ReverseAlgo reverse;

void PhaseDistorter::init() {
    dds_.init(true);
    algos_[0] = &reverse;
    max_warp_ = 0.8;
}

void PhaseDistorter::update(float freq, float warp) {
    dds_.set_freq(freq);
    warp *= max_warp_;
    algos_[0]->update_params(warp);
}

uint16_t PhaseDistorter::distort() {
    uint32_t phase = dds_.update();
    return algos_[0]->process_phase(phase) >> k_dds_downshift;
}