#include "bitcrush.hpp"

void BitcrushAlgo::update_params(float warp) {
    passthrough_ = warp < 0.1;
    if (passthrough_) return;

    slope_ = pow2f(1.0 / warp);
    inv_slope_ = 1.0 / slope_;
}

float BitcrushAlgo::process_phase(float pha) {
    if (passthrough_) return pha;
    uint64_t high_pha = slope_ * pha;
    return static_cast<float>(inv_slope_ * high_pha);
}