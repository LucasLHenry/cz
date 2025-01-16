#include "sync.hpp"

void SyncAlgo::update_params(float warp) {
    passthrough_ = warp < 0.01;
    if (passthrough_) return;
    slope_ = 1.0 - (warp * 0.5);
}

float SyncAlgo::process_phase(float pha) {
    if (passthrough_) return pha;
    return pha * slope_;
}