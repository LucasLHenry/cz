#ifndef PHASE_DISTORTION_SYNC_HIGH_H_
#define PHASE_DISTORTION_SYNC_HIGH_H_

#include "pd_algo.hpp"

class HighSyncAlgo : public PDAlgo {
    public:
        HighSyncAlgo() {}
        ~HighSyncAlgo() {}

        virtual uint32_t process_phase(uint32_t pha);

    private:
        virtual void update_params_();
        float slope_;
};

#endif  // PHASE_DISTORTION_SYNC_HIGH_H_