#include "dds_core.hpp"

uint32_t DDSCore::update() {
    acc_ += pha_;
    int32_t dither_val_ = PRNG::centered_lcg() >> 12;
    return (acc_ + dither_val_) >> k_dds_downshift;
}

void DDSCore::set_freq(float freq_hz) {
    pha_ = static_cast<uint32_t>(freq_hz * k_hz_phasor);
}