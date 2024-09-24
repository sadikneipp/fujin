#pragma once

#include <cstdint>

namespace bsp::leds {

/// @section Constants

#define LED_STRIPE_AMOUNT 2 ///< Number of LEDs in the stripe

typedef enum {
    EMMITER_IR_LEFT_SIDE,
    EMMITER_IR_LEFT_FRONT,
    EMMITER_IR_RIGHT_FRONT,
    EMMITER_IR_RIGHT_SIDE,
} bsp_led_ir_t;


/// @section Interface definition

/// @brief Initializes LEDs peripherals
/// @note Doesn't need to be called directly as bsp_init() already calls this
void init(void);

void indication_on(void);
void indication_off(void);
void indication_toggle(void);

void ir_emmiter_on(bsp_led_ir_t led);
void ir_emmiter_off(bsp_led_ir_t led);
void ir_emmiter_all_on(void);
void ir_emmiter_all_off(void);

/// @brief Sets the color of a LED in the stripe
/// @param num LED number [0, LED_STRIPE_AMOUNT)
/// @param r Red value. [0, 255]
/// @param g Green value. [0, 255]
/// @param b Blue value. [0, 255]
void stripe_set(uint8_t num, uint8_t r, uint8_t g, uint8_t b);

} // namespace
