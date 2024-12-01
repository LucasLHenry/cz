#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/dma.h"
 
#include "drivers/audio_dac.hpp"
 
const uint SAMPLE_RATE = 48000;

AudioDAC audio_dac;
AudioDAC* DAC_REF_ = &audio_dac;
 
#define BUFFER_SIZE 8


uint32_t idx = 0;

static int16_t sine_wave_table[2048];
 
void buffer_fill(AudioDAC::Frame* buf, size_t size) {
    for (uint i = 0; i < BUFFER_SIZE; i++) {
        buf[i].l = sine_wave_table[idx];
        buf[i].r = sine_wave_table[idx];
        idx++;
        idx %= 2048;
    }
}
 
int main() {
    set_sys_clock_khz(128 * 1000, true);
    sleep_ms(100);
 
    stdio_init_all();

    for (int i = 0; i < 2048; i++) {
        sine_wave_table[i] = 32767 * cosf(i * 4 * (float) (M_PI / 2048));
    }

    audio_dac.init(SAMPLE_RATE, BUFFER_SIZE);
    audio_dac.start(buffer_fill);

    // Main loop
    while (true) {}
}