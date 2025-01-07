#include "dds_core.hpp"

void DDSCore::init(bool dither) {
    dither_ = dither;
}

uint32_t DDSCore::gen_phase() {
    acc_ += pha_;
    if (dither_) {
        int32_t dither_val_ = rand_i32() >> 12;
        return acc_ + dither_val_;
    }
    return acc_;
}

void DDSCore::update_params(float freq_hz) {
    pha_ = static_cast<uint32_t>(freq_hz * k_hz_phasor);
}