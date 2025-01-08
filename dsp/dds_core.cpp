#include "dds_core.hpp"

void DDSCore::init() {
}

uint32_t DDSCore::gen_phase() {
    acc_ += pha_;
    return acc_;
}

void DDSCore::update_params(float freq_hz) {
    pha_ = static_cast<uint32_t>(freq_hz * k_hz_phasor);
}