#ifndef PHASE_DISTORTION_SYNC_H_
#define PHASE_DISTORTION_SYNC_H_

#include "pd_algo.hpp"

class SyncAlgo : public PDAlgo {
    public:
        SyncAlgo() {}
        ~SyncAlgo() {}

        virtual float process_phase(float pha);
        virtual void update_params(float warp);

    private:
        float slope_;
};

#endif  // PHASE_DISTORTION_SYNC_H_