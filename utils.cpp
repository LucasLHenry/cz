#include "utils.h"

int16_t xfade(int16_t a, int16_t b, float blend) {
    return static_cast<int16_t>(a + (b - a)*blend);
}