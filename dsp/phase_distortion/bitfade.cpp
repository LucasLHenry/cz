#include "bitfade.hpp"

#define NUM_STEPS 16.0f

void BitfadeAlgo::update_params(float warp) {
    passthrough_ = warp < 0.05;
    if (passthrough_) return;

    warp_ = warp;
}

float BitfadeAlgo::process_phase(float pha) {
    if (passthrough_) return pha;
    uint64_t high_pha = NUM_STEPS * pha;
    return xfade(pha, static_cast<float>(high_pha) / NUM_STEPS, warp_);
}