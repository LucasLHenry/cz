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
    raw_params_.wave = wave_pot_.value_f;
    raw_params_.warp = warp_pot_.value_f;
    raw_params_.algo = algo_pot_.value_f;
    raw_params_.freq_hz = get_freq(pitch_enc_.value_i32, 0);
}

UI::Params UI::get_params() {
    interpolated_params_.wave = raw_params_.wave;
    interpolated_params_.warp = raw_params_.warp;
    interpolated_params_.algo = raw_params_.algo;
    ONE_POLE_LPF(interpolated_params_.freq_hz, raw_params_.freq_hz, pitch_filter_coefficient_);
    return interpolated_params_;
}

float UI::get_freq(int32_t enc_course, int32_t enc_fine) {
    // lets say one encoder click in course mode is a semitone
    // and one encoder click in fine mode is 5 cents
    float raw_freq = 40.0+5*(enc_course >> 1);
    return (raw_freq < 5)? 5.0 : raw_freq;
    // float num_semitones = enc_course + enc_fine * 0.05;
    // num_semitones = CLAMP(num_semitones, min_semitones, max_semitones);
    // uint32_t octave = 0;
    // while (num_semitones > 12) {
    //     num_semitones -= 12.0;
    //     octave++;
    // }
    // num_semitones *= pitch_multiplier;
    // MAKE_INTEGRAL_FRACTIONAL(num_semitones);
    // float ratio1 = pitch_lut[num_semitones_integral];
    // float ratio2 = pitch_lut[num_semitones_integral+1];
    // float pitch = xfade(ratio1, ratio2, num_semitones_fractional);
    // while (octave > 0) {
    //     pitch *= 2;
    //     octave--;
    // }
    // return pitch;
}