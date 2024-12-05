#include <stdio.h>
#include <math.h>

#include "pico/stdlib.h"
#include "pico/multicore.h"

#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/dma.h"
#include "hardware/adc.h"
 
#include "drivers/audio_dac.hpp"
 
const uint SAMPLE_RATE = 48000;

AudioDAC audio_dac;
AudioDAC* DAC_REF_ = &audio_dac;
 
#define BUFFER_SIZE 8


uint32_t idx = 0;
uint16_t increment = 1;

static int16_t sine_wave_table[2048];
 
void buffer_fill(AudioDAC::Frame* buf, size_t size) {
    for (uint i = 0; i < BUFFER_SIZE; i++) {
        buf[i].l = sine_wave_table[idx];
        buf[i].r = sine_wave_table[idx];
        idx += increment;
        idx %= 2048;
    }
}

void core1_entry_point() {
    audio_dac.init(SAMPLE_RATE, BUFFER_SIZE);
    audio_dac.start(buffer_fill);
    while (true) {}
}
 
int main() {
    set_sys_clock_khz(CLK_FREQ_Hz, true);
    sleep_ms(100);
 
    stdio_init_all();
    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);
    adc_gpio_init(28);

    for (int i = 0; i < 2048; i++) {
        sine_wave_table[i] = 32767 * cosf(i * 4 * (float) (M_PI / 2048));
    }

    multicore_launch_core1(core1_entry_point);

    // Main loop
    while (true) {
        adc_select_input(0);
        uint32_t val = adc_read();
        adc_select_input(1);
        val += adc_read();
        adc_select_input(2);
        val += adc_read();
        increment = (val >> 10) + 1;
        printf("Hello World\n");
    }
    return 0;
}