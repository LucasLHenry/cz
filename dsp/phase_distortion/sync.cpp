#include "sync.hpp"

void SyncAlgo::update_params_() {
    slope_ = 1.0 - (warp_ / 2.0);
}

uint32_t SyncAlgo::process_phase(uint32_t pha) {
    return static_cast<uint32_t>(pha * slope_);
}