#include "sdk_common.h"
#include "ble_ser.h"
#include <string.h>
#include "ble_srv_common.h"
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_log.h"

static void on_connect(ble_ser_t * p_ser, ble_evt_t const * p_ble_evt)
{
    p_ser->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;

    ble_ser_evt_t evt;

    evt.evt_type = BLE_SER_EVT_CONNECTED;

    p_ser->evt_handler(p_ser, &evt);
}

static void on_disconnect(ble_ser_t * p_ser, ble_evt_t const * p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);
    p_ser->conn_handle = BLE_CONN_HANDLE_INVALID;

    ble_ser_evt_t evt;

    evt.evt_type = BLE_SER_EVT_DISCONNECTED;

    p_ser->evt_handler(p_ser, &evt);
}

static void on_write(ble_ser_t * p_ser, ble_evt_t const * p_ble_evt)
{
    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

    if (p_evt_write->handle == p_ser->custom_value_handles.value_handle)
    {
        nrf_gpio_pin_toggle(LED_4);
    }

    if ((p_evt_write->handle == p_ser->custom_value_handles.cccd_handle)
        && (p_evt_write->len == 2)
       )
    {
        // CCCD written, call application event handler
        if (p_ser->evt_handler != NULL)
        {
            ble_ser_evt_t evt;

            if (ble_srv_is_notification_enabled(p_evt_write->data))
            {
                evt.evt_type = BLE_SER_EVT_NOTIFICATION_ENABLED;
            }
            else
            {
                evt.evt_type = BLE_SER_EVT_NOTIFICATION_DISABLED;
            }
            // Call the application event handler.
            p_ser->evt_handler(p_ser, &evt);
        }
    }

}

uint32_t ble_ser_init(ble_ser_t * p_ser, const ble_ser_init_t * p_ser_init)
{
    if (p_ser == NULL || p_ser_init == NULL)
    {
        return NRF_ERROR_NULL;
    }

    uint32_t   err_code;
    ble_uuid_t ble_uuid;

    p_ser->evt_handler               = p_ser_init->evt_handler;
    p_ser->conn_handle               = BLE_CONN_HANDLE_INVALID;
    /*
    ble_uuid128_t base_uuid = {MY_SERVICE_UUID_BASE};
    err_code =  sd_ble_uuid_vs_add(&base_uuid, &p_ser->uuid_type);
    VERIFY_SUCCESS(err_code);

    ble_uuid.type = p_ser->uuid_type;
    ble_uuid.uuid = MY_SERVICE_UUID;
    */
    BLE_UUID_BLE_ASSIGN(ble_uuid, Environmental_Sensing_UUID);

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_ser->service_handle);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }


}


uint32_t ble_ser_custom_value_update(ble_ser_t * p_ser, uint8_t custom_value)
{
    NRF_LOG_INFO("In ble_cus_custom_value_update. \r\n");
    if (p_ser == NULL)
    {
        return NRF_ERROR_NULL;
    }

    uint32_t err_code = NRF_SUCCESS;
    ble_gatts_value_t gatts_value;

    // Initialize value struct.
    memset(&gatts_value, 0, sizeof(gatts_value));

    gatts_value.len     = sizeof(uint8_t);
    gatts_value.offset  = 0;
    gatts_value.p_value = &custom_value;

    // Update database.
    err_code = sd_ble_gatts_value_set(p_ser->conn_handle,
                                      p_ser->custom_value_handles.value_handle,
                                      &gatts_value);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Send value if connected and notifying.
    if ((p_ser->conn_handle != BLE_CONN_HANDLE_INVALID))
    {
        ble_gatts_hvx_params_t hvx_params;

        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = p_ser->custom_value_handles.value_handle;
        hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset = gatts_value.offset;
        hvx_params.p_len  = &gatts_value.len;
        hvx_params.p_data = gatts_value.p_value;

        err_code = sd_ble_gatts_hvx(p_ser->conn_handle, &hvx_params);
        NRF_LOG_INFO("sd_ble_gatts_hvx result: %x. \r\n", err_code);
    }
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
        NRF_LOG_INFO("sd_ble_gatts_hvx result: NRF_ERROR_INVALID_STATE. \r\n");
    }


    return err_code;
}
