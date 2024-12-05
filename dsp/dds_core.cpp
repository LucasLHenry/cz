#include "dds_core.hpp"

inline void DDSCore::update() {
    previous_shifted_acc_ = shifted_acc_;
    acc += pha;
    shifted_acc_ = acc >> shift_amount_;
    overflow = (previous_shifted_acc_ > shifted_acc_);
}

void DDSCore::reset(uint32_t new_acc) {
    acc = new_acc;
    shifted_acc_ = acc >> shift_amount_;
    shifted_acc_ = shifted_acc_;
}

inline uint32_t DDSCore::get_acc() {
    return shifted_acc_;
}