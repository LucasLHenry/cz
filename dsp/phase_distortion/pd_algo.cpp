#include "pd_algo.hpp"

PDAlgo::~PDAlgo() = default;

void PDAlgo::update_params(float warp) {
    if (fabsf(warp - warp_) > 0.01) {
        warp_ = warp;
        update_params_();
    } else if (!started_) {
        warp_ = warp;
        started_ = true;
        update_params_();
    }
}