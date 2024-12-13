#ifndef PHASE_DISTORTION_REVERSE_H_
#define PHASE_DISTORTION_REVERSE_H_

#include "pd_algo.hpp"

class ReverseAlgo : public PDAlgo {
    public:
        ReverseAlgo() {}
        ~ReverseAlgo() {}

        virtual void update_params(float warp);
        virtual uint32_t process_phase(uint32_t pha);

    private:
        uint64_t reverse_point_;
};

#endif  // PHASE_DISTORTION_REVERSE_H_