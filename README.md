# BLE_NRF
Create Service & Characteristic 

* [Install and Compile NRF52 by SEGGER Embedded Studio](#install-and-compile-nrf52-by-segger-embedded-studio)
* [Create Beacon nRF SDK](#create-beacon-nrf-sdk)
* [Create Service nRF SDK](#create-service-nrf-sdk)
* [Create Characteristic on Service BLE nRF SDK](#create-characteristic-on-service-ble-nrf-sdk)

## Install and Compile NRF52 by SEGGER Embedded Studio
* Download โปรแกรม Segger Embedded Studio จาก https://www.segger.com/downloads/embedded-studio
  ![install-1](https://user-images.githubusercontent.com/27261111/47130455-f1ae7c80-d2c3-11e8-854e-56ccbae629ef.png)

* ทำการติดตั้งโปรแกรม เมื่อเปิดโปรแกรมขึ้นมาจะได้ดังภาพ โดยโปรแกรมนี้จะเป็นตัว compile และ แล้ว flash โปรแกรมไปยังบอร์ด BLE nRF52832
  ![install-2](https://user-images.githubusercontent.com/27261111/47130492-20c4ee00-d2c4-11e8-946c-3bd56e9ab98d.png)
  
* Download nRF5-SDK จาก https://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF5-SDK
  ![install-3](https://user-images.githubusercontent.com/27261111/47130546-58cc3100-d2c4-11e8-9a83-70eee5cb0919.png)
  
* ทำการ unzip เป็นอันเสร็จ จากนั้นเข้าไปยัง folder ที่ได้ทำการ unzip ไว้ เข้าไปที่ nRF5_SDK/exsamples/ble_peripheral/ble_app_blinky/pca10040/s132/ses แล้วทำการเปิดไฟล์ ble_app_blinky_pca10040_s132.emProject โดยโปรแกรม Segger Embedded
  ![install-4](https://user-images.githubusercontent.com/27261111/47135903-2af2e680-d2dc-11e8-84cc-838c3d657066.png)
* ทำการ compile โดยการกด F7 เมื่อ compile ผ่านจะแสดงขนาดของ Flash โปรแกรม
  ![install-5](https://user-images.githubusercontent.com/27261111/47136011-8c1aba00-d2dc-11e8-9a15-2d5066dc5f55.png)
* ทำการ Flash โปรแกรมลงบอร์ดnRF52832 โดยเชื่อมต่อ บอร์ดเข้ากับคอมพิวเตอร์ และทำการกด F5  เมื่อเสร็จแล้วทำการกดปุ่ม Shift+F5 เพื่อให้บอร์ดเริ่มทำงาน 
  ![install-6](https://user-images.githubusercontent.com/27261111/47136051-af456980-d2dc-11e8-9cda-18d22df22d17.png)
* จากนั้นทำการ Download Application nRF Connect บนมือถือ เพื่อใช้ตรวจจับ สัญญาณ BLE ที่ปล่อยออกมา 

   nRF Connnect : Anddroid
    https://play.google.com/store/apps/details?id=no.nordicsemi.android.mcp&hl=th

   nRF Connnect : iOS
    https://itunes.apple.com/th/app/nrf-connect/id1054362403?mt=8
    
    เมื่อเปิด App nRF Connect ขึ้นมา จะเห็น บอร์ดปล่อยสัญญาณออกมาชื่อ Nordic_Blinky เป็นอันเสร็จขึ้นตอนการ Compile และ การFlash โปรแกรมลงบอร์ด nRF52832 
    
    ![install-7](https://user-images.githubusercontent.com/27261111/47136094-d0a65580-d2dc-11e8-8d0f-e6daae3d35f6.png)

## Create Beacon nRF SDK
* BLE Beacon คือการที่ตัวอุปกรณ์ อยู่ใน State Advertising ข้อมูล นั้นๆออกมาตลอดเวลาไม่มีการ Connect โดยเมื่อเทียบเคียงกับอุปกรณ์อื่นจะทำหน้าที่คล้ายๆ RFID card หรือ จะเป็น Barcode เป็นต้น

* เข้าไปที่ nRF5_SDK/exsamples/ble_peripheral/ble_app_beacon และนี้คือข้อมูลที่เราต้องการ Advertise 

  ![beacon-1](https://user-images.githubusercontent.com/27261111/47136409-cfc1f380-d2dd-11e8-9b63-859f5372f2bb.png)
  
* จากนั้นทำการ Compile และ Flash โปรแกรมตามที่ผ่านมา

* เมื่อเปิด App nRF Connect ขึ้นมา จะมีชื่อสำหรับ beacon เพราะไม่มีใส่เอาไว้ เมื่อกดเข้าไปดูข้อมูลภายใน จะเห็นว่า เหมือนกับที่เราได้ตั้งค่าเอาไว้

  ![image](https://user-images.githubusercontent.com/27261111/47136617-6abacd80-d2de-11e8-8dfb-5ea66417f153.png)
  
## Create Service nRF SDK
* เข้าไปที่ nRF5_SDK/exsamples/ble_peripheral/ble_app_template เราจะทำการเพิ่ม Service ตัวใหม่เข้าไปใน application นี้

* ทำการสร้างไฟล์ใหม่ขึ้นมา ชื่อ ble_ser.h และทำการเพิ่มไฟล์ include ที่จำเป็นเข้ามา

  ```
  #include <stdint.h>
  #include <stdbool.h>
  #include "ble.h"
  #include "ble_srv_common.h"

  #define BLE_SER_DEF(_name)       	\
  static ble_ser_t _name;   		\
  ```

* จากนั้นทำการใส่ UUID สำหรับ ble service นี้ โดยที่ UUID จะมีขนาดเท่ากับ 128 bit โดยเราสามารถสร้าง UUID นี้ได้จาก https://www.uuidgenerator.net/version4  
  โดยที่ UUID ที่ได้รับการสร้างขึ้นจะเป็นตัวเดียวในโลกโดยที่ไม่ซ้ำกัน ดังนั้นเราจะได้เป็น 9b14ffd3-7f8f-4a29-84c0-856110610544  และรูปแบบของ UUID จะเป็น 8-4-4-4-12 โดยการใส่ UUID เราจะใส่แบบเรียงจากหลังมาหน้า ดังนี้

  ```
    #define MY_SERVICE_UUID_BASE         {0x44, 0x05, 0x61, 0x10, 0x61, 0x85, 0xc0, 0x84, 0x29, 0x4a, 0x8f, 0x7f, 0xd3, 0xff,     0x14, 0x9b}
    #define MY_SERVICE_UUID               0xABCD
  ```
  
* จากนั้นทำการ สร้าง struct สำหรับเก็บค่าต่างๆ ตามนี้

  ```
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
  ```
  
* ตั่งชื่อ function ที่จะต้องไปใช้ ใน ble_ser.c สำหรับเชื่อมโยงการทำงาน เป็นอันเสร็จ สำหรับ ไฟล์ ble_ser.h

  ```
    uint32_t ble_ser_init(ble_ser_t * p_ser, const ble_ser_init_t * p_ser_init);
  ```
  
* ต่อไปเป็นการสร้างจัดการในส่วนไฟล์ ble_ser.c อันดับแรกสร้างไฟล์ ble_ser.c ขึ้นมา พร้อมเปิดไฟล์ขึ้นมาและทำการ Include ไฟล์ต่างๆ

  ```
    #include "sdk_common.h"
    #include "ble_ser.h"
    #include <string.h>
    #include "ble_srv_common.h"
    #include "nrf_gpio.h"
    #include "boards.h"
    #include  "nrf_log.h"
  ```
* สร้าง Function ใน ble_ser.c ตามชื่อ ble_ser_init() ที่ได้ประกาศไว้ใน ble_ser.h และใส่ค่าคงไปตามนี้ เป็นอันเสร็จ

  ```
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

          ble_uuid128_t base_uuid = {MY_SERVICE_UUID_BASE};
          err_code =  sd_ble_uuid_vs_add(&base_uuid, &p_ser->uuid_type);
          VERIFY_SUCCESS(err_code);
          ble_uuid.type = p_ser->uuid_type;
          ble_uuid.uuid = MY_SERVICE_UUID;
          err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_ser->service_handle);
          if (err_code != NRF_SUCCESS)
          {
              return err_code;
          }
      }
  ```
  
* ทำการเพิ่ม function สำหรับการจัดการ event ภายใน ble state
  
  ```
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
  ```
  
* จากนั้นทำการเปิดไฟล์ main.c ขึ้นมา ทำการ include file ที่เราได้สร้างขึ้นมาเข้าไป
  
  ```
    #include "ble_ser.h"
  ```

  และเพิ่ม macro ที่เราสร้างไว้ใน ble_ser.h เข้าไป main.c
  
  ```
      BLE_SER_DEF(m_ser);

    static ble_uuid_t m_adv_uuids[] =                
    {
        { MY_SERVICE_UUID_BASE, BLE_UUID_TYPE_BLE }
    };
  ```
  
* ทำการไปที่ function static void services_init(void) และทำการเพิ่ม code ดังนี้เพื่อเป็นการเปิดใช้ service ใน main programs

  ```
    ble_ser_init_t                     ser_init;

      memset(&ser_init, 0, sizeof(ser_init));

      err_code = ble_ser_init(&m_ser, &ser_init);
      APP_ERROR_CHECK(err_code);
  ```

* ทำการเพิ่ม ไฟล์libery ble_ser.c ที่เราสร้างขึ้นมาใหม่เพื่อให้โปรแกรมสามารถดึงไฟล์ไป compile ได้ โดยเข้าที่ไป        nRF_SDK/nRF5_SDK/examples/ble_peripheral/ble_my_service/pca10040/s132/ses/ble_app_template_pca10040_s132.emProject และทำการเพิ่มคำสั่งนี้ลงไป 

  ```
    <folder Name="nRF_BLE_Services">
        <file file_name="../../../ble_ser.c" />
      </folder>
  ```

* เมื่อเสร็จแล้วทำการ compile และ flash program และ ทำการเปิด application nRF Connect ในเมือถือ และการ Scan หา BLE ที่เราได้สร้างขึ้นมา

![service-1](https://user-images.githubusercontent.com/27261111/47137535-0baa8800-d2e1-11e8-8483-b1e8bd5508fc.png)

* ทำการ Connect จะเห็นว่า service ที่เราสร้างขึ้นมาปรากฏขึ้นมา และเป็น UUID ที่เราทำการเพิ่มเข้าไป ดังภาพ

![service-2](https://user-images.githubusercontent.com/27261111/47137573-241aa280-d2e1-11e8-9c9a-5f9af4d95ab1.png)

* จะเห็นได้ว่าเรา Service ที่เราสร้างขึ้นมาจะแสดงเป็น Unknown Service เพราะว่าเลข UUID ที่เรา สร้างขึ้นมาไม่ได้ลงทะเบียนไว้ และเราสามารถใช้เลข UUID ที่ ทาง Bluetooth SIG ได้ลงทะเบียนไว้เพื่อเป็น มาตรฐานในอุปกรณ์แต่ละประเภท โดยเข้าไปดูที่ https://www.bluetooth.com/specifications/gatt/services

* เมื่อได้ UUID แล้ว ในที่นี้เราจะใช้ Environmental Sensing ที่มี UUID = 0x181A โดยเราต้องเข้าไปเพิ่ม #defin ใน ble_ser.h

  ```
      #define Environmental_Sensing_UUID  0x181A

      ทำการแก้การดึงค่า define ble_ser.c ใน function ble_ser_init() โดยทำการลบ

      ble_uuid128_t base_uuid = {MY_SERVICE_UUID_BASE};
      err_code =  sd_ble_uuid_vs_add(&base_uuid, &p_ser->uuid_type);
      VERIFY_SUCCESS(err_code);

      ble_uuid.type = p_ser->uuid_type;
      ble_uuid.uuid = MY_SERVICE_UUID;
  ```
  
  พิ่มคำสั่งนี้เข้าไปแทนที่
  
  ```
    BLE_UUID_BLE_ASSIGN(ble_uuid, Environmental_Sensing_UUID);
  ```
  
  สุดท้ายทำการแก้ file main.c โดยการแก้ MY_SERVICE_UUID_BASE เป็น Environmental_Sensing_UUID
  
  ```
      static ble_uuid_t m_adv_uuids[] =                                            
    {
        { MY_SERVICE_UUID_BASE, BLE_UUID_TYPE_BLE } 
        {Environmental_Sensing_UUID, BLE_UUID_TYPE_BLE }
    };
  ```
* เมื่อเสร็จแล้วทำการ compile และ flash program และ ทำการเปิด application nRF Connect ในเมือถือ และการ Scan หา BLE ที่เราได้สร้างขึ้นมา จะเห็นว่าเป็น Environmental_Sensing Service

  ![service-3](https://user-images.githubusercontent.com/27261111/47137748-b28f2400-d2e1-11e8-89cf-8745f64f9a82.png)
  
  
  ## Create Characteristic on Service BLE nRF SDK
* เมื่อเราได้ Service มาแล้วต่อไปจะเป็นการสร้าง Characteristic ใน Service ที่เราสร้างมา
* ในการสร้าง Characteristic จะเป็นการสร้างส่วนเพิ่มเข้าไปใน Service ที่เราได้สร้างมาแล้ว ดังนั้นทำการ copy folder ble_my_service และทำการตั้งชื่อใหม่เป็น ble_my_service_characteristic เริ่มต้นจากการตั้งชื่อ function ใน ble_ser.h โดยฟังก์ชั่นนี้เป็นการเพิ่ม characteristic ใหม่เข้าไปใน Service ที่สร้างมาก่อนแล้ว

    ```
    static uint32_t ble_value_char_add(ble_cus_t * p_ser, const ble_ser_init_t * p_ser_init)
    ```
* ทำการเปิดใช้งาน softdevice โดยการเพิ่มคำสั่งนี้ลงไป 
  ```
    NRF_SDH_BLE_OBSERVER(_name ## _obs,              \
                       BLE_HRS_BLE_OBSERVER_PRIO,         \
                       ble_ser_on_ble_evt, &_name)
  ```
  ทำการเพิ่มชื่อฟังก์ชั่น ใน ble_ser.h เพื่อเป็นการเปิดใช้งาน softdevice
  ```
  void ble_ser_on_ble_evt( ble_evt_t const * p_ble_evt, void * p_context);
  ```
  จากนั้นทำการเพิ่ม function ที่ได้ตั้งชื่อไว้แล้วเข้าไปใน ble_ser.c โดนฟังก์ชั่นจะแสดงดังนี้
  ```
          void ble_ser_on_ble_evt( ble_evt_t const * p_ble_evt, void * p_context)
        {
            ble_ser_t * p_ser = (ble_ser_t *) p_context;

            NRF_LOG_INFO("BLE event received. Event type = %d\r\n", p_ble_evt->header.evt_id);
            if (p_ser == NULL || p_ble_evt == NULL)
            {
                return;
            }

            switch (p_ble_evt->header.evt_id)
            {
                case BLE_GAP_EVT_CONNECTED:
                    on_connect(p_ser, p_ble_evt);
                    break;

                   case BLE_GAP_EVT_DISCONNECTED:
                        on_disconnect(p_ser, p_ble_evt);
                        break;

                    case BLE_GATTS_EVT_WRITE:
                        on_write(p_ser, p_ble_evt);
                        break;
        /* Handling this event is not necessary
                    case BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST:
                        NRF_LOG_INFO("EXCHANGE_MTU_REQUEST event received.\r\n");
                        break;
        */
                    default:
                        // No implementation needed.
                        break;
                }
        }
  ```
* จากนั้นไปยัง ไฟล์ ble_ser.c ทำการเพิ่มฟังก์ชั่นที่ได้ตั้งชื่อไว้แล้วไว้ในนั้น

  ```
    static uint32_t ble_value_char_add(ble_cus_t * p_ser, const ble_ser_init_t * p_ser_init)

      uint32_t            err_code;
      ble_gatts_char_md_t char_md;
      ble_gatts_attr_md_t cccd_md;
      ble_gatts_attr_t    attr_char_value;
      ble_uuid_t          ble_uuid;
      ble_gatts_attr_md_t attr_md;

      memset(&cccd_md, 0, sizeof(cccd_md));

  ```
* จากนั้นทำการ ทำการ ตั้งค่าให้ Characteristic ที่สร้างขึ้นให้มี สามารถ Read Write และ Notify ค่าสำหรับ BLE Device โดนในการเปิดการงานจะเป็น 1 และ 0 เป็นการปิด

  ```
    char_md.char_props.read   = 1;
    char_md.char_props.write  = 1;
    char_md.char_props.notify = 1;
  ```
* ทำการกำหนดค่าให้ BLE Device สามารถส่งและรับค่าได้ โดยการตั้งค่าเป็น
  ```
    custom_value_char_attr_md.read_perm
    custom_value_char_attr_md.write_perm
  ```
  
* ทำการ add ค่า UUID ให้กับ Characteristic ที่เราได้สร้างขึ้นมา

  ```
    BLE_UUID_BLE_ASSIGN(ble_uuid, Temperature_Characteristic_UUID);

    memset(&attr_char_value, 0, sizeof(attr_char_value));
    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = len_s;//sizeof(uint8_t);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = len_s;//sizeof(uint8_t);
  ```
  
* แล้วจะทำการ add Characteristic ที่เราสร้างขึ้นมาเข้าไปใน ble_gatt โดย sd_ble_gatts_characteristic_add กับ struct ที่ได้สร้างขึ้นมา

  ```
      err_code = sd_ble_gatts_characteristic_add(p_ser->service_handle, &char_md,
                                               &attr_char_value,
                                               &p_ser->custom_value_handles);
  ```
  
* ทำการเพิ่ม คำสั่ง add characteristic เข้าไป ใน ble_ser_init() 

  ```
    return ble_value_char_add(p_ser, p_ser_init);
  ```
  
* สุดท้ายแล้ว Function ทั้งหมดจะได้ดังนี้

  ```
          static uint32_t ble_value_char_add(ble_ser_t * p_ser, const ble_ser_init_t * p_ser_init)
        {
            uint32_t            err_code;
            ble_gatts_char_md_t char_md;
            ble_gatts_attr_md_t cccd_md;
            ble_gatts_attr_t    attr_char_value;
            ble_uuid_t          ble_uuid;
            ble_gatts_attr_md_t attr_md;

            // Add Custom Value characteristic
            memset(&cccd_md, 0, sizeof(cccd_md));

            //  Read  operation on cccd should be possible without authentication.
            BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
            BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);

            cccd_md.write_perm = p_ser_init->custom_value_char_attr_md.cccd_write_perm;
            cccd_md.vloc       = BLE_GATTS_VLOC_STACK;

            memset(&char_md, 0, sizeof(char_md));

            char_md.char_props.read   = 1;
            char_md.char_props.write  = 1;
            char_md.char_props.notify = 1;
            char_md.p_char_user_desc  = NULL;
            char_md.p_char_pf         = NULL;
            char_md.p_user_desc_md    = NULL;
            char_md.p_cccd_md         = &cccd_md;
            char_md.p_sccd_md         = NULL;

            BLE_UUID_BLE_ASSIGN(ble_uuid, Temperature_Characteristic_UUID);

            memset(&attr_md, 0, sizeof(attr_md));

            attr_md.read_perm  = p_ser_init->custom_value_char_attr_md.read_perm;
            attr_md.write_perm = p_ser_init->custom_value_char_attr_md.write_perm;
            attr_md.vloc       = BLE_GATTS_VLOC_STACK;
            attr_md.rd_auth    = 0;
            attr_md.wr_auth    = 0;
            attr_md.vlen       = 0;

            memset(&attr_char_value, 0, sizeof(attr_char_value));

            attr_char_value.p_uuid    = &ble_uuid;
            attr_char_value.p_attr_md = &attr_md;
            attr_char_value.init_len  = sizeof(uint8_t);
            attr_char_value.init_offs = 0;
            attr_char_value.max_len   = sizeof(uint8_t);

            err_code = sd_ble_gatts_characteristic_add(p_ser->service_handle, &char_md,
                                                       &attr_char_value,
                                                       &p_ser->custom_value_handles);
            if (err_code != NRF_SUCCESS)
            {
                return err_code;
            }

            return NRF_SUCCESS;
        }
  ```
  
* ทำการแก้ไฟล์ main.c ตามนี้

  ```
    ble_ser_init_t      ser_init = {0};
    ser_init.evt_handler                = on_ser_evt;

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&ser_init.custom_value_char_attr_md.cccd_write_perm);
            BLE_GAP_CONN_SEC_MODE_SET_OPEN(&ser_init.custom_value_char_attr_md.read_perm);
            BLE_GAP_CONN_SEC_MODE_SET_OPEN(&ser_init.custom_value_char_attr_md.write_perm);

    err_code = ble_ser_init(&m_ser, &ser_init);
    APP_ERROR_CHECK(err_code);
  ```
* เมื่อเสร็จแล้วทำการ compile และ flash program และ ทำการเปิด application nRF Connect ในเมือถือ และการ Scan หา BLE ที่เราได้สร้างขึ้นมา จะเห็นว่าเป็น Environmental_Sensing Service กดเข้าไปจะเห็น characteristic ที่เราสร้างขึ้นที่สามารถ read write และ notify ได้

  ![char-1](https://user-images.githubusercontent.com/27261111/47138485-ba4fc800-d2e3-11e8-8dd2-792b286ff665.png)
  
* จากนั้นทำการเพื่อฟังก์ชั่นเพื่อให้สามารถส่งข้อมูลออกไปทาง read characteristic ได้ โดยการตั้งชื่อฟังก์ชั่น ble_ser_custom_value_update() เข้าใน ble_ser.h เข้าไป

  ```
    uint32_t ble_ser_custom_value_update(ble_ser_t * p_ser, uint8_t custom_value);
  ```
  
  ทำการเปิดไฟล์ ble_ser.c และสร้างฟังก์ชั่น การทำงาน ตามข้างล่างนี้ 
  
  ```
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
  ```
  
 * ทำการเพิ่มฟังก์ชั่น on_ser_evt() สำหรับการรับค่าการ event ที่ส่งใน BLE
  ```
              static void on_ser_evt(ble_ser_t     * p_ser_service,
                                   ble_ser_evt_t * p_evt)
            {
                ret_code_t err_code;

                switch(p_evt->evt_type)
                {
                    case BLE_SER_EVT_NOTIFICATION_ENABLED:

                         err_code = app_timer_start(m_notification_timer_id, NOTIFICATION_INTERVAL, NULL);
                         APP_ERROR_CHECK(err_code);
                         break;

                    case BLE_SER_EVT_NOTIFICATION_DISABLED:

                        err_code = app_timer_stop(m_notification_timer_id);
                        APP_ERROR_CHECK(err_code);
                        break;

                    case BLE_SER_EVT_CONNECTED:
                        break;

                    case BLE_SER_EVT_DISCONNECTED:
                          break;

                    default:
                          // No implementation needed.
                          break;
                }
            }
  ```
  
* จากนั้นทำการเพิ่ม timer สำหรับการอัพเดตข้อมูลที่เราต้องการส่ง โดยเพิ่มในไฟล์ main.c

  ```
    #define NOTIFICATION_INTERVAL           APP_TIMER_TICKS(1000)
    APP_TIMER_DEF(m_notification_timer_id);
  ```
  
  ทำการเพิ่ม timer ใน timers_init()
  
  ```
     err_code = app_timer_create(&m_notification_timer_id,  APP_TIMER_MODE_REPEATED, notification_timeout_handler);

     APP_ERROR_CHECK(err_code);
  ```
  ทำการเพิ่มฟังก์ชั่น notification_timeout_handler() เขาไปใน main.c ดังนี้
  ```
    UNUSED_PARAMETER(p_context);
    ret_code_t err_code;

    // Increment the value of m_custom_value before nortifing it.
    m_custom_value++;

    err_code = ble_ser_custom_value_update(&m_ser, m_custom_value);
    APP_ERROR_CHECK(err_code);
  ```
  
* เมื่อเสร็จแล้วทำการ compile และ flash program และ ทำการเปิด application nRF Connect ในเมือถือ และการ Scan หา BLE ที่เราได้สร้างขึ้นมา จะเห็นว่าเป็น Environmental_Sensing Service กดเข้าไปจะเห็น characteristic แล้วกดปุ่ม read ค่าที่ได้จะมีค่าเพิ่มขึ้นเรื่อยๆ เพราะคำสั่งเราได้ตั่งค่าให้เพิ่มขึ้นไปเรื่อยๆ m_custom_value++; ดังนี้

  ![char-2](https://user-images.githubusercontent.com/27261111/47138772-7a3d1500-d2e4-11e8-9c23-a72a7af8d202.png)
  
  เราสามารถเขียนค่าส่งไปยัง ble device ได้ และเมื่อทำการอ่านค่าจะเห็นได้ว่าค่าที่ได้จะเป็นค่าที่เราส่งไปนั้นเอง
  
  ![char-3](https://user-images.githubusercontent.com/27261111/47138793-8c1eb800-d2e4-11e8-9e73-47db08ee5a14.png)
  
  เมื่อเราลองทำการกดปุ่ม notify แล้วค่าจะมีการบวกเพิ่มขึ้นที่ละ 1 ตามโปรแกรมที่เราได้เขียนไว้
  
  ![char-4](https://user-images.githubusercontent.com/27261111/47138842-ac4e7700-d2e4-11e8-9d1f-3b7411f0c030.png)
