#include "pico/stdlib.h"
#include "pico/multicore.h"
 
#include "rplib/drivers/audio_dac.hpp"
#include "ui.hpp"
#include "dsp/synth.hpp"
#include "hw_config.h"

UI ui;
Synth synth;
extern AudioDAC audio_dac;
 
void buffer_fill(AudioDAC::Frame* buf, size_t size) {
    synth.process(buf, size);
}

void core1_entry_point() {
    audio_dac.init(OUTPUT_SAMPLE_RATE, DAC_BUFFER_SIZE, DAC_PIO_SM,
                   I2S_DATA_PIN, I2S_BASE_CLK_PIN);
    audio_dac.start(buffer_fill);
    while (true) {}
}

int main() {
    set_sys_clock_khz(CLK_FREQ_kHz, true);
    sleep_ms(100);
 
    stdio_init_all();
    ui.init();
    synth.init(0.4, &ui.params);
    multicore_launch_core1(core1_entry_point);

    while (true) ui.poll();
    return 0;
}