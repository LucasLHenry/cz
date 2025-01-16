#include "ui.hpp"

void UI::init() {
    adc_init();

    wave_pot_.init(ADC_OVERSAMPLE_AMT, MUX_PIN, POT);
    warp_pot_.init(ADC_OVERSAMPLE_AMT, MUX_PIN, POT);
    algo_pot_.init(ADC_OVERSAMPLE_AMT, MUX_PIN, POT);
    volume_pot_.init(ADC_OVERSAMPLE_AMT, MUX_PIN, POT);
    phase_pot_.init(ADC_OVERSAMPLE_AMT, MUX_PIN, POT);

    uint mux_pins[3] = {21, 20, 19};
    wave_pot_.configure_mux(WAVE_MUX_IDX, 3, mux_pins);
    warp_pot_.configure_mux(WARP_MUX_IDX, 3, mux_pins);
    algo_pot_.configure_mux(ALGO_MUX_IDX, 3, mux_pins);
    volume_pot_.configure_mux(3, 3, mux_pins);
    phase_pot_.configure_mux(6, 3, mux_pins);

    pitch_enc_.init(ENC_PIN_BASE, true, true);

    pitch_filter_coefficient_ = ewma_filter_coefficient(200);

    gpio_init(ENC_BTN_PIN);
    gpio_set_pulls(ENC_BTN_PIN, true, false);
    gpio_set_dir(ENC_BTN_PIN, false);
}

void UI::poll() {
    wave_pot_.read();
    warp_pot_.read();
    algo_pot_.read();
    pitch_enc_.read();
    volume_pot_.read();
    phase_pot_.read();
    params.wave = wave_pot_.value_f;
    params.warp = warp_pot_.value_f;
    params.algo = algo_pot_.value_f;
    params.volume = volume_pot_.value_f*1.5 + 0.4;
    params.phase_offset = phase_pot_.value_f;

    if (gpio_get(ENC_BTN_PIN) == false) enc_fine_ += pitch_enc_.change;
    else enc_course_ += pitch_enc_.change;
    ONE_POLE_LPF(smoothed_note_, get_note(enc_course_, enc_fine_), pitch_filter_coefficient_);

    params.freq_hz = get_freq(smoothed_note_);
}

float UI::get_note(int32_t enc_course, int32_t enc_fine) {
    float num_semitones = min_semitones + (enc_course >> 1) + 0.05 * enc_fine;
    return CLAMP(num_semitones, min_semitones, max_semitones);
}

float UI::get_freq(float note) {
    float octave = note * pitch_multiplier;
    return pow2f(octave);
}