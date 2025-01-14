#include "kink.hpp"

void KinkAlgo::update_params_() {
    float sub = 1.0 - warp_;
    s1 = 1.0 / sub;
    s2 = 1.0 / (1.0 + warp_);
    o2 =  (1.0 - s2*sub) * 0.5;
    kink_point = sub * 0.5;
}

float KinkAlgo::process_phase(float pha) {
    if (pha < kink_point) {
        return s1 * pha;
    } else {
        return s2 * pha + o2;
    }
}