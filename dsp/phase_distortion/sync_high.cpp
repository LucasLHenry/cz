#include "sync_high.hpp"

void HighSyncAlgo::update_params(float warp) {
    passthrough_ = warp == 0;
    if (passthrough_) return;
    slope_ = 1.0 / (1.0 - warp);
}

float HighSyncAlgo::process_phase(float pha) {
    if (passthrough_) return pha;
    
    float warped_phase = pha * slope_;
    return warped_phase - static_cast<uint32_t>(warped_phase);
}