#include "sync_high.hpp"

void HighSyncAlgo::update_params_() {
    slope_ = 1.0 / (1.0 - warp_);
}

float HighSyncAlgo::process_phase(float pha) {
    float warped_phase = pha * slope_;
    return warped_phase - static_cast<uint32_t>(warped_phase);
}