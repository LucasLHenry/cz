#ifndef PHASE_DISTORTION_REVERSE_H_
#define PHASE_DISTORTION_REVERSE_H_

#include "pd_algo.hpp"

class ReverseAlgo : public PDAlgo {
    public:
        ReverseAlgo() {}
        ~ReverseAlgo() {}

        virtual float process_phase(float pha);

    private:
        virtual void update_params_();
        float reverse_point_;
};

#endif  // PHASE_DISTORTION_REVERSE_H_