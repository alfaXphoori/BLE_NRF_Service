# BLE_NRF
Create Service & Characteristic 

* [Install and Compile NRF52 by SEGGER Embedded Studio](#install-and-compile-nrf52-by-segger-embedded-studio)
* [Create Beacon nRF SDK](#create-beacon-nrf-sdk)
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
* เมื่อเราทำการ install Contiki เสร็จแล้ว ทำการเข้าไปที่ Folder contiki/example/ipv6 และทำการ make border-router เมื่อเสร็จจะได้ดังภาพ
    ```
    cd contiki/examples/ipv6
    sudo make TARGET=srf06-cc26xx BOARD=launchpad/cc2650 border-router

    ```
    ![br1](https://user-images.githubusercontent.com/27261111/45938769-3ca3df80-bff7-11e8-9c2c-af284da28c76.png)
* ทำการ Flash program border-router.hex โดยใช้โปรแกรม Flash programmer 2 หรือ Uniflash และทำการเชื่อมต่อกับ ubuntu ต่อไป
* จากนั้นทำการใช้ Tunslip6 โดยเข้าไปที่ contiki/tools และทำการ make tunslip6
    ```
    cd contki/tools
    sudo make tunslip6
    ```
* เมื่อ tunslip6 พร้อมแล้ว เราจะทำการเปิดการใช้งาน ด้วยคำสั่ง 
    ```
    sudo ./tunslip6 aaaa::1/64 -s /dev/ttyACM0
    ```
    เสร็จแล้วให้ทำการกด Reset ที่ บอร์ด  2 ครั้ง จะได้ ip ของ boarder-router ตามลูกศร เป็นอันเสร็จสิ้นการเชื่อมต่อ Network ส่วนของ IEEE 802.15.4 เข้าเก็บ Ubuntu
    ![br2](https://user-images.githubusercontent.com/27261111/45938805-9efce000-bff7-11e8-9e94-f8f919b6e1ad.png)
* เมื่อได้ ip boarder-router เสร็จแล้ว จะมาทำการ make โนด client เพื่อทำการเชื่อมต่อกับ boarder-router โดยเข้าไปที่ contiki/examples/ipv6/rpl-udp
  ```
  cd contiki/examples/ipv6/rpl-udp
  sudo make TARGET=srf06-cc26xx BOARD=launchpad/cc2650 udp-client
  ```
  
  เมื่อ make เสร็จทำการ Flash program และทำการเปิด web browser แล้วใส่ ip board-router จะเห็นได้ว่า board-router สามารถมองเห็น client ตัวไหนได้บ้าง
  
  ![br3](https://user-images.githubusercontent.com/27261111/45938858-074bc180-bff8-11e8-9067-4c489aa2dadc.png)
  
  เสร็จแล้วจะทำการ ping ไปยังโนด client แสดงว่า client สามารถเชื่อต่อได้ ดังนั้น border-router และ tunslip6 จะทำหน้าที่เป็นตัวสร้าง network ระหว่างวง IEEE 802.15.4 กับ ubnutu เราโดยการสร้าง interface อีกตัวนึงมาเพื่อเชื่อมต่อกันและกัน
  ![br4](https://user-images.githubusercontent.com/27261111/45938864-192d6480-bff8-11e8-8f8d-becfb6dd23c3.png)
