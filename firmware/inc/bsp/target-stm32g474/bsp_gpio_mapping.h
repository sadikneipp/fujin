#ifndef BSP_GPIO_MAPPING_H
#define BSP_GPIO_MAPPING_H

#include "bsp_gpio.h"

// Buttons

#define GPIO_BUTTON_1_PIN  IO_PIN_9
#define GPIO_BUTTON_1_PORT IO_PORTB

#define GPIO_BUTTON_2_PIN  IO_PIN_13
#define GPIO_BUTTON_2_PORT IO_PORTC

// Led
#define GPIO_LED_PIN  IO_PIN_13
#define GPIO_LED_PORT IO_PORTB


// ENCODERS
#define ENCODER_LEFT_A_PIN  IO_PIN_2
#define ENCODER_LEFT_A_PORT IO_PORTA

#define ENCODER_LEFT_B_PIN  IO_PIN_3
#define ENCODER_LEFT_B_PORT IO_PORTA

#define ENCODER_RIGHT_A_PIN  IO_PIN_7
#define ENCODER_RIGHT_A_PORT IO_PORTC

#define ENCODER_RIGHT_B_PIN  IO_PIN_15
#define ENCODER_RIGHT_B_PORT IO_PORTB

#endif /* BSP_GPIO_MAPPING_H */