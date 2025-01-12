#include "sync.hpp"

void SyncAlgo::_update_params() {
    slope_ = 1.0 - (_warp / 2.0);
}

uint32_t SyncAlgo::process_phase(uint32_t pha) {
    return static_cast<uint32_t>(pha * slope_);
}