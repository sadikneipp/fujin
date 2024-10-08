#pragma once

#include "bsp/ble.hpp"

namespace services {

class Config {
public:
    static float kp;
    static float ki;
    static float kd;

    static float min_move_speed;
    static float min_turn_speed;
    static float fix_position_speed;
    static float search_speed;
    static float angular_speed;
    static float run_speed;

    static float linear_acceleration;
    static float angular_acceleration;

    static void parse_packet(uint8_t packet[bsp::ble::max_packet_size]);
};

}