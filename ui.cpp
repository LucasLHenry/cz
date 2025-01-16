#include "ui.hpp"

void UI::init() {
    adc_init();

    wave_pot_.init(ADC_OVERSAMPLE_AMT, MUX_PIN, POT);
    warp_pot_.init(ADC_OVERSAMPLE_AMT, MUX_PIN, POT);
    algo_pot_.init(ADC_OVERSAMPLE_AMT, MUX_PIN, POT);

    uint mux_pins[3] = {21, 20, 19};
    wave_pot_.configure_mux(WAVE_MUX_IDX, 3, mux_pins);
    warp_pot_.configure_mux(WARP_MUX_IDX, 3, mux_pins);
    algo_pot_.configure_mux(ALGO_MUX_IDX, 3, mux_pins);

    pitch_enc_.init(3, true, true);

    pitch_filter_coefficient_ = ewma_filter_coefficient(200);
}

void UI::poll() {
    wave_pot_.read();
    warp_pot_.read();
    algo_pot_.read();
    pitch_enc_.read();
    params.wave = wave_pot_.value_f;
    params.warp = warp_pot_.value_f;
    params.algo = algo_pot_.value_f;
    ONE_POLE_LPF(smoothed_note_, get_note(pitch_enc_.value_i32, 0), pitch_filter_coefficient_);
    params.freq_hz = get_freq(smoothed_note_);
}

float UI::get_note(int32_t enc_course, int32_t enc_fine) {
    float num_semitones = min_semitones + (enc_course >> 1) + 0.1 * enc_fine;
    return CLAMP(num_semitones, min_semitones, max_semitones);
}

float UI::get_freq(float note) {
    float octave = note * pitch_multiplier;
    return pow2f(octave);
}