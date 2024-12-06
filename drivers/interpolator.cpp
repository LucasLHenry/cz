#include "interpolator.hpp"

void interpolator_init() {
    interp_config cfg = interp_default_config();
    interp_config_set_blend(&cfg, true);
    interp_config_set_signed(&cfg, true);
    interp_set_config(interp0, 0, &cfg);

    cfg = interp_default_config();
    interp_set_config(interp0, 1, &cfg);
}

uint32_t interpolate(int32_t x1, int32_t x2, uint8_t blend_amt) {
    interp0->base[0] = x1;
    interp0->base[1] = x2;
    interp0->accum[1] = blend_amt;
    return interp0->peek[1];
}