#include "sine_fold.hpp"

void SinefoldAlgo::update_params(float warp) {
    passthrough_ = warp < 0.01;
    warp_ = warp * 0.95;
}

float SinefoldAlgo::process_phase(float pha) {
    if (passthrough_) return pha;
    float sine_val = interpolate(sine_pd_lut, pha, pd_lut_length);
    return (sine_val - pha)*warp_ + pha;
}