#ifndef PHASE_DISTORTION_SYNC_H_
#define PHASE_DISTORTION_SYNC_H_

#include "pd_algo.hpp"

class SyncAlgo : public PDAlgo {
    public:
        SyncAlgo() {}
        ~SyncAlgo() {}

        virtual float process_phase(float pha);

    private:
        virtual void update_params_();
        float slope_;
};

#endif  // PHASE_DISTORTION_SYNC_H_