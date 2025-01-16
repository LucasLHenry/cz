#include "double_kink.hpp"

DoubleKinkAlgo::DoubleKinkAlgo () {
    kink_point_1_ = 1.0 / 6.0;
    kink_point_2_ = 0.9;
    offset_1_ = 0.25;
    offset_2_ = 1.0 / 3.0;
}

void DoubleKinkAlgo::update_params(float warp) {
    interp_ = warp;
    passthrough_ = warp == 0;
}

float DoubleKinkAlgo::process_phase(float pha) {
    if (passthrough_) return pha;
    
    if (pha < kink_point_1_) {
        float warped_phase = 2*pha;
        return xfade(pha, 2*pha, interp_);
    }
    if (pha < kink_point_2_) {
        float warped_phase = 0.5*pha + offset_1_;
        return xfade(pha, warped_phase, interp_);
    }
    float warped_phase = 3*(pha - offset_2_);
    return xfade(pha, warped_phase, interp_);
}