#include "sync_high.hpp"

void HighSyncAlgo::update_params_() {
    slope_ = 1.0 / (1.0 - warp_);
}

uint32_t HighSyncAlgo::process_phase(uint32_t pha) {
    return static_cast<uint64_t>(pha * slope_) % UINT32_MAX;
}