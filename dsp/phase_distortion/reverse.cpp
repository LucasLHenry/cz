#include "reverse.hpp"

void ReverseAlgo::update_params_() {
    reverse_point_ = (1 - warp_ * 0.5);
}

float ReverseAlgo::process_phase(float pha) {
    if (pha < reverse_point_) return pha;
    else {
        return reverse_point_*2.0 - pha;
    }
}