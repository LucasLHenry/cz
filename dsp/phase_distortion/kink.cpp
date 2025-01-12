#include "kink.hpp"

void KinkAlgo::update_params_() {
    s1 = 1.0 / (1.0 - warp_);
    s2 = 1.0 / (1.0 + warp_);
    o2 = UINT32_MAX * (1.0 - s2*(1.0 - warp_)) / 2.0;
    kink_point = static_cast<uint32_t>(UINT32_MAX * (1.0 - warp_) / 2.0);
}

uint32_t KinkAlgo::process_phase(uint32_t pha) {
    if (pha < kink_point) {
        return static_cast<uint32_t>(s1 * pha);
    } else {
        return static_cast<uint32_t>(s2 * pha + o2);
    }
}