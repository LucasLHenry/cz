#ifndef PHASE_DISTORTION_SYNC_HIGH_H_
#define PHASE_DISTORTION_SYNC_HIGH_H_

#include "pd_algo.hpp"

class HighSyncAlgo : public PDAlgo {
    public:
        HighSyncAlgo() {}
        ~HighSyncAlgo() {}

        virtual float process_phase(float pha);
        virtual void update_params(float warp);

    private:
        float slope_;
};

#endif  // PHASE_DISTORTION_SYNC_HIGH_H_