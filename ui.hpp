#ifndef UI_H_
#define UI_H_

#include <math.h>

#include "hardware/adc.h"

#include "utils.h"
#include "hw_config.h"
#include "drivers/adc_input.hpp"
#include "drivers/encoder.hpp"
#include "tables/pitch_lut.h"

class UI {
    public:
        UI() {}
        ~UI() {}

        typedef struct {
            float freq_hz;
            float wave;
            float warp;
            float algo;
        } Params;
    
        void init();
        void poll();
        Params params;
    
    private:
        ADCInput wave_pot_;
        ADCInput warp_pot_;
        ADCInput algo_pot_;
        Encoder pitch_enc_;

        float get_note(int32_t enc_course, int32_t enc_fine);
        float get_freq(float note);
        float pitch_filter_coefficient_;
        float smoothed_note_;
};

#endif  // UI_H_