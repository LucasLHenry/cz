#include "dds_core.hpp"

void DDSCore::init(bool dither) {
    dither_ = dither;
    dither_shift_ = (32 - k_dds_downshift) + 1;
}

uint32_t DDSCore::update() {
    acc_ += pha_;
    if (dither_) {
        int32_t dither_val_ = rand_i32() >> dither_shift_;
        return (acc_ + dither_val_) >> k_dds_downshift;
    }
    return acc_; // >> k_dds_downshift;
}

void DDSCore::set_freq(float freq_hz) {
    pha_ = static_cast<uint32_t>(freq_hz * k_hz_phasor);
}