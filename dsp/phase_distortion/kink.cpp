#include "kink.hpp"

void KinkAlgo::update_params(float warp) {
    passthrough_ = warp == 0;
    if (passthrough_) return;
    float sub = 1.0 - warp;
    s1 = 1.0 / sub;
    s2 = 1.0 / (1.0 + warp);
    o2 =  (1.0 - s2*sub) * 0.5;
    kink_point = sub * 0.5;
}

float KinkAlgo::process_phase(float pha) {
    if (passthrough_) return pha;
    
    if (pha < kink_point) {
        return s1 * pha;
    } else {
        return s2 * pha + o2;
    }
}