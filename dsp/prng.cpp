#include "prng.hpp"

uint32_t PRNG::lcg() {
    static uint64_t val = 1234;  // seed
    val = (val*134775813 + 1) % (1 << 31);
    return static_cast<uint32_t>(val);
}

int32_t PRNG::centered_lcg() {
    return static_cast<int32_t>(PRNG::lcg() - (1 << 31));
}