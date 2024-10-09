#pragma once

#include <cstdint>

namespace bsp::eeprom {

/// @section Custom types

enum EepromResult {
    OK,
    ERROR,
    DATA_NOT_FOUND,
};

typedef enum : uint16_t {
    ADDR_MEMORY_CLEAR = 0x0000,
    ADDR_ANGULAR_KP = 0x0004,
    ADDR_ANGULAR_KI = 0x0008,
    ADDR_ANGULAR_KD = 0x000C,
    ADDR_MIN_MOVE_SPEED = 0x0010,
    ADDR_MIN_TURN_SPEED = 0x0014,
    ADDR_FIX_POSITION_SPEED = 0x0018,
    ADDR_SEARCH_SPEED = 0x001C,
    ADDR_ANGULAR_SPEED = 0x0020,
    ADDR_RUN_SPEED = 0x0024,
    ADDR_LINEAR_ACCELERATION = 0x0028,
    ADDR_ANGULAR_ACCELERATION = 0x002C,

    ADDR_MAZE_START = 0x1000,
    ADDR_MAZE_END = 0x1400,

    ADDR_MAX = 0xFFFF,
} param_addresses_t;

/// @section Interface definition

EepromResult init(void);

EepromResult read_u8(uint16_t address, uint8_t* data);
EepromResult write_u8(uint16_t address, uint8_t data);
EepromResult read_u16(uint16_t address, uint16_t* data);
EepromResult write_u16(uint16_t address, uint16_t data);
EepromResult read_u32(uint16_t address, uint32_t* data);
EepromResult write_u32(uint16_t address, uint32_t data);

void clear(void);
void print_all(void);

}
