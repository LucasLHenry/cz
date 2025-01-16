#include "reverse.hpp"

void ReverseAlgo::update_params(float warp) {
    passthrough_ = warp == 0;
    if (passthrough_) return;

    reverse_point_ = (1 - warp * 0.5);
}

float ReverseAlgo::process_phase(float pha) {
    if (passthrough_) return pha;
    
    if (pha < reverse_point_) return pha;
    else {
        return reverse_point_*2.0 - pha;
    }
}