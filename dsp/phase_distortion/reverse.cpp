#include "reverse.hpp"

void ReverseAlgo::_update_params() {
    reverse_point_ = static_cast<uint64_t>(UINT32_MAX*(1 - _warp / 2.0));
}

uint32_t ReverseAlgo::process_phase(uint32_t pha) {
    if (pha < reverse_point_) return pha;
    else {
        return (reverse_point_ << 1) - pha;
    }
}