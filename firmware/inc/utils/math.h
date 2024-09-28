#pragma once

#include <cmath>
#include <stdint.h>

/**
 * @brief Constrains v between x and y, returning at least x and at most y.
 */
#define constrain(v, x, y) ((v) < (x) ? (x) : ((v) > (y) ? (y) : (v)))

/**
 * @brief Checks if v is between a and b inclusive
 */
#define IS_BETWEEN(x, a, b) ((x) >= (a) && (x) <= (b))

#define TWO_BYTES_TO_UINT16(b1, b2) ((b1 << 8) | (b2))

#define FOUR_BYTES_TO_UINT32(b1, b2, b3, b4) ((b1 << 24) | (b2 << 16) | (b3 << 8) | (b4))

/**
 * @brief Maps an integer value from one scale to another.
 *
 * @param former_value Value in former scale.
 * @param former_min   Former scale minimum value.
 * @param former_max   Former scale maximum value.
 * @param new_min      New scale minimum value.
 * @param new_max      New scale maximum value.
 *
 * @return Value in new scale
 */
static inline int map(int former_value, int former_min, int former_max, int new_min, int new_max) {
    long int new_value;

    new_value = (long int)(former_value - former_min) * (new_max - new_min);
    new_value /= (former_max - former_min);
    new_value += new_min;

    return (int)new_value;
}

static inline uint16_t map_u16(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max) {
    return constrain((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min, out_min, out_max);
}

static inline int16_t map_i16(int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max) {
    return constrain((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min, out_min, out_max);
}

static inline double deg2rad(double degrees) {
    static constexpr double pi_on_180 = M_PI / 180.0;
    return degrees * pi_on_180;
}
