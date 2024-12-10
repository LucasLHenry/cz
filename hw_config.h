#ifndef HW_CONFIG_H_
#define hW_CONFIG_H_


#define I2S_DATA_PIN 9
#define I2S_BASE_CLK_PIN 10

#define DAC_PIO_SM 0

#define CLK_FREQ_Hz 150000
#define OUTPUT_SAMPLE_RATE 48000
#define ADC_OVERSAMPLE_AMT 8
#define ADC_POT_LPF_AMT 0.1
#define DAC_BUFFER_SIZE 8
#define ADC_BITS 12

#define NUM_ADC_INPUTS 3
#define PITCH_INPUT 0
#define WAVE_INPUT 1
#define WARP_INPUT 2

#endif // hW_CONFIG_H_