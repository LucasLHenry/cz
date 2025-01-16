#include "bitcrush.hpp"

void BitcrushAlgo::update_params_() {
    passthrough_ = warp_ == 0;
    if (!passthrough_) {
        slope_ = pow2f(1.0 / warp_);
        inv_slope_ = 1.0 / slope_;
    }
}

float BitcrushAlgo::process_phase(float pha) {
    uint64_t high_pha = slope_ * pha;
    return static_cast<float>(inv_slope_ * high_pha);
}