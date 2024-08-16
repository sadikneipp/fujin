/***************************************************************************************************
 * INCLUDES
 **************************************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "ble_service.h"
#include "bsp_ble.h"

/***************************************************************************************************
 * LOCAL DEFINES
 **************************************************************************************************/
#define VALIDATOR_NUM 0x14
/***************************************************************************************************
 * LOCAL TYPEDEFS
 **************************************************************************************************/

/***************************************************************************************************
 * LOCAL FUNCTION PROTOTYPES
 **************************************************************************************************/

static void ble_callback(uint8_t *ble_data, uint8_t rcv_size);
static void ble_process_events(ble_rcv_packet_t rcv_packet);

/***************************************************************************************************
 * LOCAL VARIABLES
 **************************************************************************************************/

static volatile ble_rcv_packet_t ble_last_data;

/***************************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************************/

/***************************************************************************************************
 * LOCAL FUNCTIONS
 **************************************************************************************************/

static int8_t validate_data(uint8_t *data, uint8_t size)
{
    if (size != BLE_RECEIVE_PACKET_SIZE) {
        return -1;
    }

    uint8_t validator = data[BLE_RECEIVE_PACKET_SIZE - 1];
    if (validator != VALIDATOR_NUM) {
        return -1;
    }

    return 0;
}

static void ble_process_events(ble_rcv_packet_t rcv_packet)
{
    switch (rcv_packet.header) {
    case BLE_STOP_SIG:
        break;
    case BLE_REQUEST_DATA:
        break;
    case BLE_UPDATE_PARAMETERS:
        break;
    case BLE_BUTTON_1_SHORT:
        break;
    case BLE_BUTTON_2_SHORT:
        break;
    case BLE_BUTTON_1_LONG:
        break;
    case BLE_BUTTON_2_LONG:
        break;
    default:
        break;
    }
}

static void ble_callback(uint8_t *ble_data, uint8_t rcv_size)
{
    if (validate_data(ble_data, rcv_size) != 0) {
        return;
    }

    memcpy((void *restrict)ble_last_data.packet, ble_data, BLE_RECEIVE_PACKET_SIZE);

    ble_process_events(ble_last_data);
}

/***************************************************************************************************
 * GLOBAL FUNCTIONS
 **************************************************************************************************/

void ble_service_init(void)
{
    bsp_ble_init();
    bsp_ble_register_callback(ble_callback);
}

void ble_service_send_data(uint8_t *data, uint8_t size)
{
    bsp_ble_transmit(data, size);
}

void ble_service_send_string(char *str)
{
    uint8_t len = strlen(str);

    if (len <= BLE_MAX_PACKET_SIZE) {
        char buffer[20] = { 0 };
        snprintf(buffer, 20, "%s", str);
        ble_service_send_data((uint8_t *)buffer, 20);
    }
}

void ble_service_last_packet(ble_rcv_packet_t *data)
{
    *data = ble_last_data;
}

ble_header_t ble_service_last_packet_type()
{
    return (ble_header_t)ble_last_data.header;
}
