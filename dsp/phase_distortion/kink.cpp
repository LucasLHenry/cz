#include "kink.hpp"

void Kink::update(float warp_amt) {
    kink_amt = warp_amt * 0.7;
    s1 = (1 - kink_amt) / (1 + kink_amt);
    s2 = (1 + kink_amt) / (1 - kink_amt);
    o2 = (1<<31) * (1 - kink_amt - s2*(1 + kink_amt));
    kink_point = static_cast<uint32_t>((1<<31) * (0.5 + kink_amt/2)) << 1;
}

uint32_t Kink::get_phase(uint32_t input_phase) {
    if (input_phase < kink_point) {
        return static_cast<uint16_t>(s1 * input_phase);
    } else {
        return static_cast<uint16_t>(s2 * input_phase + o2);
    }  
}
