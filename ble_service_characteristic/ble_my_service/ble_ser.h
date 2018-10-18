#ifndef BLE_SER_H__
#define BLE_SER_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"

#define BLE_SER_DEF(_name)                                                                          \
static ble_ser_t _name;                                                                             \

//UUID 9b14ffd3-7f8f-4a29-84c0-856110610544

#define MY_SERVICE_UUID_BASE         {0x44, 0x05, 0x61, 0x10, 0x61, 0x85, 0xc0, 0x84, \
                                      0x29, 0x4a, 0x8f, 0x7f, 0xd3, 0xff, 0x14, 0x9b}

#define MY_SERVICE_UUID               0xABCD

#define Environmental_Sensing_UUID    0x181A

typedef enum
{
    BLE_SER_EVT_NOTIFICATION_ENABLED,
    BLE_SER_EVT_NOTIFICATION_DISABLED,
    BLE_SER_EVT_DISCONNECTED,
    BLE_SER_EVT_CONNECTED
} ble_ser_evt_type_t;

typedef struct
{
    ble_ser_evt_type_t evt_type;
} ble_ser_evt_t;

typedef struct ble_ser_s ble_ser_t;

typedef void (*ble_ser_evt_handler_t) (ble_ser_t * p_bas, ble_ser_evt_t * p_evt);

typedef struct
{
    ble_ser_evt_handler_t         evt_handler;
    uint8_t                       initial_custom_value;
    ble_srv_cccd_security_mode_t  custom_value_char_attr_md;
} ble_ser_init_t;

struct ble_ser_s
{
    ble_ser_evt_handler_t         evt_handler;
    uint16_t                      service_handle;
    ble_gatts_char_handles_t      custom_value_handles;
    uint16_t                      conn_handle;
    uint8_t                       uuid_type;
};

uint32_t ble_ser_init(ble_ser_t * p_ser, const ble_ser_init_t * p_ser_init);

#endif // BLE_SER_H__
