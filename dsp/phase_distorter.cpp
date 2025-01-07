#include "phase_distorter.hpp"


KinkAlgo kink;
SyncAlgo sync;
ReverseAlgo reverse;
DoubleKinkAlgo double_kink;

void PhaseDistorter::init() {
    dds_.init(false);
    algos_[0] = &kink;
    algos_[1] = &sync;
    algos_[2] = &reverse;
    algos_[3] = &double_kink;
    max_warp_ = 0.8;
}

void PhaseDistorter::update(float freq, float warp, float algo) {
    dds_.set_freq(freq);
    warp *= max_warp_;
    algo *= NUM_ALGOS - 1;
    MAKE_INTEGRAL_FRACTIONAL(algo);
    algo_idx_ = algo_integral;
    algo_xfade_amt_ = algo_fractional;
    algos_[algo_idx_]->update_params(warp);
    algos_[algo_idx_+1]->update_params(warp);
}

uint16_t PhaseDistorter::distort() {
    uint32_t phase = dds_.update();
    uint32_t val1 = algos_[algo_idx_]->process_phase(phase);
    uint32_t val2 = algos_[algo_idx_+1]->process_phase(phase);
    return xfade(val1, val2, algo_xfade_amt_) >> k_dds_downshift;
}