#include "phase_distorter.hpp"


KinkAlgo kink;
SyncAlgo sync;
ReverseAlgo reverse;
DoubleKinkAlgo double_kink;

void PhaseDistorter::init() {
    algos_[0] = &kink;
    algos_[1] = &sync;
    algos_[2] = &reverse;
    algos_[3] = &double_kink;
    max_warp_ = 0.8;
}

void PhaseDistorter::update_params(float warp, float algo) {
    warp *= max_warp_;
    algo *= NUM_ALGOS - 1;
    MAKE_INTEGRAL_FRACTIONAL(algo);
    algo_idx_ = algo_integral;
    algo_xfade_amt_ = algo_fractional;
    algos_[algo_idx_]->update_params(warp);
    algos_[algo_idx_+1]->update_params(warp);
}

uint32_t PhaseDistorter::process_phase(uint32_t pha) {
    uint32_t val1 = algos_[algo_idx_]->process_phase(pha);
    uint32_t val2 = algos_[algo_idx_+1]->process_phase(pha);
    return xfade(val1, val2, algo_xfade_amt_);
}