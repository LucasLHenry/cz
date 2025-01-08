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
}

void UI::poll() {
    wave_pot_.read();
    warp_pot_.read();
    algo_pot_.read();
    pitch_enc_.read();
    raw_params_.wave = wave_pot_.value_f;
    raw_params_.warp = warp_pot_.value_f;
    raw_params_.algo = algo_pot_.value_f;
    raw_params_.freq_hz = get_freq(pitch_enc_.value_i32, 0);
}

UI::Params UI::get_params() {
    return raw_params_;
}

float UI::get_freq(int32_t enc_course, int32_t enc_fine) {
    // lets say one encoder click in course mode is a semitone
    // and one encoder click in fine mode is 5 cents
    float course_pitch = enc_course * 8.333333E-2f;
    float fine_pitch = enc_fine * 4.166666E-3f;
    float freq_hz = pow(2.0, course_pitch + fine_pitch);
    return CLAMP(freq_hz, 20.0f, 1.0E3f);
}