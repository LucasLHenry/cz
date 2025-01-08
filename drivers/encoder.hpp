#ifndef DRIVERS_ENCODER_H_
#define DRIVERS_ENCODER_H_

#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "encoder.pio.h"
#include "gpio_irq_handler.hpp"

class Encoder {
    public:
        Encoder() {}
        ~Encoder() {}

        void init(uint gpio_pin_base, bool pullup, bool invert);
        int32_t get();
        uint8_t dma_chan, pio_sm;

    private:
        int32_t prev_count_, count_;
        int32_t out_count_;
        bool invert_;
        
        void init_gpio(uint gpio_pin_base, bool pullup);
        void init_pio(uint gpio_pin_base);
        void init_dma();

        void pin_a_callback(uint gpio_pin, uint32_t events);
        void pin_b_callback(uint gpio_pin, uint32_t events);

        enum { DMA_MAX_TRANSFER_COUNT = 0xFFFFFFFF, DMA_REFRESH_THRESHOLD = 0x80000000 };

        void restart_dma();
};

#endif  // DRIVERS_ENCODER_H_