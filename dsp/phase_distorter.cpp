#include "phase_distorter.hpp"

void PhaseDistorter::init(PDAlgo** algos, size_t num_algos) {
    for (uint i = 0; i < num_algos; i++) {
        algos_[i] = algos[i];
    }
    num_algos_ = num_algos;
}

void PhaseDistorter::update_params(float warp, float algo) {
    algo *= num_algos_ - 1;
    MAKE_INTEGRAL_FRACTIONAL(algo);
    algo_idx_ = algo_integral;
    algo_xfade_amt_ = algo_fractional;
    algos_[algo_idx_]->update_params(warp);
    algos_[algo_idx_+1]->update_params(warp);
}

float PhaseDistorter::process_phase(float pha) {
    float val1 = algos_[algo_idx_]->process_phase(pha);
    float val2 = algos_[algo_idx_+1]->process_phase(pha);
    return xfade(val1, val2, algo_xfade_amt_);
}