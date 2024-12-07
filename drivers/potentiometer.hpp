#ifndef DRIVERS_POTENTIOMETER_H_
#define DRIVERS_POTENTIOMETER_H_

#include "hardware/adc.h"
#include "../utils.h"

const size_t k_max_adc_oversample = 32;

class Potentiometer {
    public:
        Potentiometer() {}
        ~Potentiometer() {}

        void init(size_t oversample, uint adc_sel);
        uint16_t read();
        uint16_t value;
    
    private:
        uint16_t values_[k_max_adc_oversample];
        size_t oversample_;
        uint adc_sel_;
};


#endif  // DRIVERS_POTENTIOMETER_H_