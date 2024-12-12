#include <stdio.h>
#include <math.h>

#include "pico/stdlib.h"
#include "pico/multicore.h"

#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/dma.h"
#include "hardware/adc.h"
 
#include "drivers/audio_dac.hpp"
#include "drivers/adc_input.hpp"
#include "dsp/variable_wave_oscillator.hpp"
#include "hw_config.h"

AudioDAC audio_dac;
AudioDAC* DAC_REF_ = &audio_dac;

VariWaveOsc osc;

ADCInput wave_pot, freq_pot, warp_pot;

float freq;
 
void buffer_fill(AudioDAC::Frame* buf, size_t size) {
    osc.process(buf, size, freq, wave_pot.value_f, warp_pot.value_f);
}

void core1_entry_point() {
    audio_dac.init(OUTPUT_SAMPLE_RATE, DAC_BUFFER_SIZE);
    audio_dac.start(buffer_fill);
    while (true) {}
}

int main() {
    set_sys_clock_khz(CLK_FREQ_Hz, true);
    sleep_ms(100);
 
    stdio_init_all();
    adc_init();
    wave_pot.init(ADC_OVERSAMPLE_AMT, 26, POT);
    warp_pot.init(ADC_OVERSAMPLE_AMT, 27, POT);
    freq_pot.init(ADC_OVERSAMPLE_AMT, 28, POT);

    osc.init();

    multicore_launch_core1(core1_entry_point);

    // Main loop
    while (true) {
        wave_pot.read();
        warp_pot.read();
        freq_pot.read();
        freq = 40 + 100*freq_pot.value_f;
    }
    return 0;
}