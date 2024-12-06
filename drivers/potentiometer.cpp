#include "potentiometer.hpp"

void Potentiometer::init(size_t oversample, uint adc_sel) {
    oversample_ = oversample;
    adc_sel_ = adc_sel;
    adc_gpio_init(adc_sel + ADC_BASE_PIN);
}

uint16_t Potentiometer::read() {
    adc_select_input(adc_sel_);
    uint64_t output = 0;
    for (uint i = 0; i < oversample_; i++) {
        output += adc_read();
    }
    value = static_cast<uint16_t>(output / oversample_);
    return value;
}