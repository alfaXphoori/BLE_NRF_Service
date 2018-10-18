# BLE_NRF
Create Service & Characteristic 

* [Install and Compile NRF52 by SEGGER Embedded Studio](#install-and-compile-nrf52-by-segger-embedded-studio)
* [Create Beacon nRF SDK](#create-beacon-nrf-sdk)
* [Boarder router](#boarder-router)

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
  โดยที่ UUID ที่ได้รับการสร้างขึ้นจะเป็นตัวเดียวในโลกโดยที่ไม่ซ้ำกัน ดังนั้นเราจะได้เป็น 
9b14ffd3-7f8f-4a29-84c0-856110610544  
  โดยรูปแบบของ UUID จะเป็น 8-4-4-4-12 โดยการใส่ UUID เราจะใส่แบบเรียงจากหลังมาหน้า ดังนี้

  ```
  #define MY_SERVICE_UUID_BASE         {0x44, 0x05, 0x61, 0x10, 0x61, 0x85, 0xc0, 0x84, 0x29, 0x4a, 0x8f, 0x7f, 0xd3, 0xff, 0x14, 0x9b}
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

  
  ## Boarder-router
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
