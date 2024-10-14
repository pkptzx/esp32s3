
### 推荐:  
ESP32模拟: Wokwi  
OneNet平台: 有100台的免费数量,以及一些免费额度的功能,比如OTA 等
阿里云物联网平台: https://iot.console.aliyun.com 公共实例免费500个设备,在线50个  


RBD_Button  

### 默认分区表位置
C:\Users\用户名\.platformio\packages\framework-arduinoespressif32\tools\partitions
%USERPROFILE%\.platformio\packages\framework-arduinoespressif32\tools\partitions

### 查看flash信息
C:\Users\loyal\.platformio\penv\Scripts\python C:\Users\loyal\.platformio\packages\tool-esptoolpy\esptool.py flash_id

%USERPROFILE%\.platformio\penv\Scripts\python %USERPROFILE%\.platformio\packages\tool-esptoolpy\esptool.py flash_id

#### 查看flash详细信息
 --chip esp32s3 image_info firmware.bin --version 2
esptool.py --chip esp32s3 image_info .pio/build/esp32s3/firmware.bin --version 2


### 资料地址
对方给的链接: 
https://www.123pan.com/s/iN6kjv-WYphd
Gstv

我转存后分享的链接:
https://www.123pan.com/s/6HGejv-YMYwA

#### 小板子,无屏
    esptool.py v4.5.1
    Found 3 serial ports
    Serial port COM5    
    Connecting....      
    Detecting chip type... ESP32-S3
    Chip is ESP32-S3 (revision v0.2)
    Features: WiFi, BLE
    Features: WiFi, BLE
    Crystal is 40MHz
    MAC: 64:e8:33:78:fb:b0
    Uploading stub...
    Running stub...
    Stub running...
    Manufacturer: ef
    Device: 7019
    Detected flash size: 32MB
    Flash type set in eFuse: quad (4 data lines)

#### 板子,有屏
esptool.py v4.5.1
Found 3 serial ports
Serial port COM5
Connecting....
Detecting chip type... ESP32-S3
Chip is ESP32-S3 (revision v0.2)
Features: WiFi, BLE
Crystal is 40MHz
MAC: e4:b0:63:89:8f:f0
Uploading stub...
Running stub...
Stub running...
Manufacturer: ef
Device: 7019
Detected flash size: 32MB
Flash type set in eFuse: quad (4 data lines)
