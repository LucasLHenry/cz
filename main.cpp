#include <stdio.h>
#include <math.h>

#include "pico/stdlib.h"
#include "pico/multicore.h"

#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/dma.h"
#include "hardware/adc.h"
 
#include "drivers/audio_dac.hpp"
#include "dsp/variable_wave_oscillator.hpp"
 
const uint SAMPLE_RATE = 48000;

AudioDAC audio_dac;
AudioDAC* DAC_REF_ = &audio_dac;

VariWaveOsc osc;
 
#define BUFFER_SIZE 8


uint32_t idx = 0;
uint16_t increment = 1;
 
void buffer_fill(AudioDAC::Frame* buf, size_t size) {
    osc.process(buf, size, increment * 30);
}

void core1_entry_point() {
    audio_dac.init(SAMPLE_RATE, BUFFER_SIZE);
    audio_dac.start(buffer_fill);
    while (true) {}
}
 
uint32_t wave_pot;
uint32_t warp_pot;
uint32_t freq_pot;

int main() {
    set_sys_clock_khz(CLK_FREQ_Hz, true);
    sleep_ms(100);
 
    stdio_init_all();
    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);
    adc_gpio_init(28);

    osc.init(&wave_pot);

    multicore_launch_core1(core1_entry_point);

    // Main loop
    while (true) {
        adc_select_input(0);
        uint32_t val = adc_read();
        adc_select_input(1);
        val += adc_read();
        increment = (val >> 10) + 1;
        adc_select_input(2);
        wave_pot = adc_read();
    }
    return 0;
}