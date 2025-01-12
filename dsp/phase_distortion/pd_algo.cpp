#include "pd_algo.hpp"

PDAlgo::~PDAlgo() = default;

void PDAlgo::update_params(float warp) {
    if (fabsf(warp - _warp) > 0.01) {
        _warp = warp;
        _update_params();
    } else if (!_started) {
        _warp = warp;
        _started = true;
        _update_params();
    }
}