#ifndef HW_CONFIG_H_
#define hW_CONFIG_H_


#define I2S_DATA_PIN 9
#define I2S_BASE_CLK_PIN 10

#define DAC_PIO_SM 0

#define ENC_PIO_SM 1

#define CLK_FREQ_kHz 200000
#define OUTPUT_SAMPLE_RATE 48000
#define ADC_OVERSAMPLE_AMT 32
#define ADC_POT_LPF_AMT 0.1
#define DAC_BUFFER_SIZE 8
#define ADC_BITS 12

#define ENC_BTN_PIN 2
#define ENC_PIN_BASE 3


#define MUX_PIN 28
#define ALGO_MUX_IDX 1
#define WAVE_MUX_IDX 2
#define WARP_MUX_IDX 0

#endif // hW_CONFIG_H_