#ifndef PHASE_DISTORTION_SYNC_H_
#define PHASE_DISTORTION_SYNC_H_

#include "pd_algo.hpp"

class SyncAlgo : public PDAlgo {
    public:
        SyncAlgo() {}
        ~SyncAlgo() {}

        virtual uint32_t process_phase(uint32_t pha);

    private:
        virtual void _update_params();
        float slope_;
};

#endif  // PHASE_DISTORTION_SYNC_H_