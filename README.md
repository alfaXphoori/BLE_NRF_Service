# BLE_NRF
Create Service & Characteristic 

* [Install and Compile NRF52 by SEGGER Embedded Studio](#install-and-compile-nrf52-by-segger-embedded-studio)
* [Flash program by Ubuntu](#flash-program-by-ubuntu)
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

## Flash program by Ubuntu
* ทำการ Config file ccfg.c ใน Contiki โดยใช้ editor ต่างๆ โดยผู้เขียนจะใช้ vim ในการ edit
  ```
  vim contiki/cpu/cc26xx-cc13xx/lib/cc26xxware/startup_files/ccfg.c
  ```
  Change as:
  ```
  #define SET_CCFG_BL_CONFIG_BOOTLOADER_ENABLE  0xC5
  #define SET_CCFG_BL_CONFIG_BL_LEVEL           0x0
  #define SET_CCFG_BL_CONFIG_BL_PIN_NUMBER      0x0D
  #define SET_CCFG_BL_CONFIG_BL_ENABLE          0xC5
  ```
* เมื่อเสร็จแล้วทำการ compile program ใน folder contiki/example/cc26xx โดยใช้คำสั่ง
  ```
  cd contiki/example/cc26xx
  make BOARD=launchpad/cc2650 cc26xx-demo
  ```
  ![tools-4](https://user-images.githubusercontent.com/27261111/45929470-86031900-bf7c-11e8-8abd-8a4fdba02a48.png)
* เมื่อทำการ compile เสร็จสิ้นจะได้ ไฟล์ cc26xx-demo.hew มา นำไป flash program ครั้งแรกเพื่อทำติดตั้ง bootloder ใหม่ โดยโปรแกรม Flash programmer 2 หรือ Uniflash
  * [FLASH-PROGRAMMER-2](http://www.ti.com/tool/FLASH-PROGRAMMER)
  * [UNIFLASH](http://www.ti.com/tool/UNIFLASH)
* โดยการ Flash program เราจะต้องมีการ config ค่า baudrate ในค่าที่บอร์ดรองรับในทีนี้เป็น 115200 โดยทำตามขั้นตอน
  ```
  vim contiki/platform/srf06-cc26xx/launchpad/Makefile.launchpad
  ```
  add:
  ```
  BSL_FLAGS += -e -w -v -b 115200
  ```
  ![tools-11](https://user-images.githubusercontent.com/27261111/45929592-1d1ca080-bf7e-11e8-8dc0-2950e194b05f.png)
* โดยการ Flash program จะต้องมาการเข้าสู้ bootloader ด้วยการกดปุ่ม BTN-1 + RESET บนบอร์ด และการทำ flash ตามคำสั่ง
  ```
  cd contiki/example/cc26xx
  make BOARD=launchpad/cc2650 cc26xx-demo.upload PORT=/dev/ttyACM0
  ```
  ถ้า Error ตามภาพ ในทุกครั้งที่มีการ flash ผ่าน ubuntu จะต้องมีการกด ปุ่ม BTN-1 + RESET ทุกครั้ง ถ้าไม่กดแสดงว่าเข้าbootloader ไม่ได้มันจึง error
  ![tools-12](https://user-images.githubusercontent.com/27261111/45929628-99af7f00-bf7e-11e8-8cc7-d1d6c536f534.png)
  สุดท้ายถ้าทำตามขั้นตอนทั้งหมด และถูกต้องเราก็จะสามารถ flash program ผ่าน ubuntu ได้ดังรูป
  ![tools-13](https://user-images.githubusercontent.com/27261111/45929638-c368a600-bf7e-11e8-88b7-8fb680412d93.png)
  
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
