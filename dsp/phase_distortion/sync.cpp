#include "sync.hpp"

void SyncAlgo::update_params_() {
    slope_ = 1.0 - (warp_ * 0.5);
}

float SyncAlgo::process_phase(float pha) {
    return pha * slope_;
}