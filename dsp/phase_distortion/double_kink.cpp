#include "double_kink.hpp"

DoubleKinkAlgo::DoubleKinkAlgo () {
    kink_point_1_ = UINT32_MAX * 0.166666;
    kink_point_2_ = UINT32_MAX * 0.9;
    offset_1_ = UINT32_MAX * 0.25;
    offset_2_ = UINT32_MAX * 0.666666;
}

void DoubleKinkAlgo::update_params(float warp) {
    interp_ = warp;
}

uint32_t DoubleKinkAlgo::process_phase(uint32_t pha) {
    if (pha < kink_point_1_) {
        uint32_t warped_phase = 2*pha;
        return xfade(pha, 2*pha, interp_);
    }
    if (pha < kink_point_2_) {
        uint32_t warped_phase = 0.5*pha + offset_1_;
        return xfade(pha, warped_phase, interp_);
    }
    uint32_t warped_phase = 3*(pha - offset_2_);
    return xfade(pha, warped_phase, interp_);
}