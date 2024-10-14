#include <Arduino.h>
#include <LiteLED.h>
#include <esp_now.h>
#include <LittleFS.h>
#include <time.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include "esp_system.h"
#include "mbedtls/pk.h"
#include "mbedtls/sha256.h"
#include "mbedtls/sha1.h"
#include "mbedtls/aes.h"
#include "mbedtls/base64.h"
#include "mbedtls/md5.h"
// #define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
// #include "esp_log.h"

#include <ArduinoJson.h>
JsonDocument jsonCmdReceive;
JsonDocument configDoc;
JsonDocument axisConfigDoc;
#include "uart_ctrl.h"
#include "utils.h"
#include "esp32_can.h"

const char ssid[] = "Cisco6000";    // WIFI名称 修改这2个就可以了
const char pass[] = "woaideren520"; // WIFI密码

bool loadConfig();
bool saveConfig();

void mDns_init();

static const char* LOG_TAG = "MyModule";

// Choose the LED type from the list below.
// Comment out all but one LED_TYPE.
#define LED_TYPE LED_STRIP_WS2812
// #define LED_TYPE        LED_STRIP_SK6812
// #define LED_TYPE        LED_STRIP_APA106
// #define LED_TYPE        LED_STRIP_SM16703

#define LED_TYPE_IS_RGBW 0 // if the LED is an RGBW type, change the 0 to 1

#define LED_GPIO 48 // change this number to be the GPIO pin connected to the LED

#define LED_BRIGHT 5 // sets how bright the LED is. O is off; 255 is burn your eyeballs out (not recommended)

static const crgb_t L_RED = 0xff0000;
static const crgb_t L_GREEN = 0x00ff00;
static const crgb_t L_BLUE = 0x0000ff;
static const crgb_t L_WHITE = 0xe0e0e0;

LiteLED myLED(LED_TYPE, LED_TYPE_IS_RGBW); // create the LiteLED object; we're calling it "myLED"

// 创建esp_now_peer_info_t类型变量存储有关peer方的信息。
// esp_now_peer_info_t peerInfo;

// 创建一个回调函数，当 ESP32 通过 ESP-NOW 接收到数据时将被调用
// void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
//   memcpy(&myData, incomingData, sizeof(myData));
// }

// 数据发送回调函数-此函数仅打印消息是否成功发送
// void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
// }



void setup()
{
  Serial.begin(115200);
  if(!LittleFS.begin(true)){
        Serial.println("LittleFS Mount Failed");
        return;
    }
  Serial.println("Welcome   ESP32-S3");

  getinfo();

  myLED.begin(LED_GPIO, 1);      // initialze the myLED object. Here we have 1 LED attached to the LED_GPIO pin
  myLED.brightness(LED_BRIGHT);  // set the LED photon intensity level
  myLED.setPixel(0, L_GREEN, 1); // set the LED colour and show it

  Serial.print("正在连接WIFI ");
  Serial.println(ssid);

  WiFi.mode(WIFI_AP_STA);// 将设备设置为 Wi-Fi Station
    
  WiFi.softAPConfig(IPAddress(10, 0, 10, 1), IPAddress(10, 0, 10, 1), IPAddress(255, 255, 255, 0));
  WiFi.softAP("test", "12345678");
  
  WiFi.begin(ssid, pass);
  

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }

  // 初始化 ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // 注册在接收到数据时调用的回调函数 OnDataRecv
  // esp_now_register_recv_cb(OnDataRecv);

  // 注册发送消息时调用的回调函数 OnDataSent
  // esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  // memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  // peerInfo.channel = 0;  
  // peerInfo.encrypt = false;
  
  // Add peer        
  // if (esp_now_add_peer(&peerInfo) != ESP_OK){
  //   Serial.println("Failed to add peer");
  //   return;
  // }
  
   // Send message via ESP-NOW
  // esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  // if (result == ESP_OK) {
  //   Serial.println("Sent with success");
  // }
  // else {
  //   Serial.println("Error sending the data");
  // }
  
  // 一对多通信
  // esp_err_t result = esp_now_send(0, (uint8_t *)&test, sizeof(test_struct));

  // 如果报错, 强制 Arduino 使用默认的 sdkconfig WiFi 设置。一般情况下使用arduino IDE开启esp-now模式一次只能同时发送3到4个消息，然后就会报错ESP_ERR_ESPNOW_INTERNAL提示发送失败
  // WiFi.useStaticBuffers(true);
  
  Serial.println();
  mDns_init();
  // delay(2000);

//   unsigned char encrypt[] = "123456";
//     unsigned char decrypt[16];
//     mbedtls_md5_context md5_ctx;
//     mbedtls_md5_init(&md5_ctx);
//     mbedtls_md5_starts_ret(&md5_ctx);
//     mbedtls_md5_update(&md5_ctx, encrypt, strlen((char *)encrypt));
//     mbedtls_md5_finish(&md5_ctx, decrypt);
//     ESP_LOGI(LOG_TAG, "Md5加密前:[%s] \n md5加密后(32位):", encrypt);
//       for(int i = 0; i < 16; i++)
//       {
//           printf("%02x", decrypt[i]);
//       }
//     mbedtls_md5_free(&md5_ctx);
//     ESP_LOGI(LOG_TAG, "------------------------------md5 end--------------------------------------------\n\n");

//     const char *src = "fdsfdsdddx";
    
    
//     // size_t sz;
//     // int ret;
//     // // 第一次获取长度
//     // ret = mbedtls_base64_encode(NULL, 0, &sz, (unsigned char *)src, strlen(src));

// char token[] = "的撒范德萨范德萨范德萨4165465fdskjfhdkjshfkjdsfkyd89sf789ds7f98dsf09ds80fsd";

//     size_t decodedTokenLen;
//     int ret = mbedtls_base64_encode(NULL, 0, &decodedTokenLen, (unsigned char *) token, strlen(token));
//     ESP_LOGI(LOG_TAG,"ret: [%d] , size: [%d]", ret, decodedTokenLen);
//  unsigned char decodedToken[decodedTokenLen] = {'\0'};
// mbedtls_base64_encode(decodedToken, decodedTokenLen, &decodedTokenLen, (unsigned char *) token, strlen(token));
// ESP_LOGI(LOG_TAG,"ret: [%d] , size: [%d]", ret, decodedTokenLen);
    
    // ESP_LOGI(LOG_TAG,"result: [%s]", decodedToken);


    // 第二次encode
    // if (ret == 0 )
    // {
    //   unsigned char dst[sz];
    //   ret = mbedtls_base64_encode(dst, 17, &sz, reinterpret_cast<const unsigned char*>(src), 10);
    // }
    // ESP_LOGI(LOG_TAG,"ret: [%d] \n", ret);
    // ESP_LOGI(LOG_TAG, "base64加密前:[%s] \n base64加密后(%d位):%s", src, sz, dst);


        loadConfig();
    // configDoc["wifi_mode_on_boot"] = "STA";
    // configDoc["sta_ssid"] = "cabot";
    // configDoc["sta_password"] = "12345678";
    // configDoc["ap_ssid"] = "cabotAp";
    // configDoc["ap_password"] = "12345678";
    // configDoc["r"] = 1.9999999;
    // String jsonStr = "{\"A_loc\":[-0.193000004,-0.216000006,0,0.193000004,-0.216000006,0,0.193000004,0.216000006,0,-0.193000004,0.216000006,0,-0.193000004,-0.216000006,0.400000006,0.193000004,-0.216000006,0.400000006,0.193000004,0.216000006,0.400000006,-0.193000004,0.216000006,0.400000006], \"H_glob\":[0.018999999,0.011,1.24000001,6.019000053,0.018999999,1.24000001,6.011000156,5.919000149,1.24000001,0.011,5.919000149,1.24000001,0.018999999,0.011,1.24000001,6.019000053,0.018999999,1.24000001,6.011000156,5.919000149,1.24000001,0.011,5.919000149,1.24000001],\"B_glob\":[0.022,0.022,3.5,6.007999897,0.022,3.5,6.007999897,5.907999992,3.5,0.022,5.907999992,3.5,0.022,0.022,3.900000095,6.007999897,0.022,3.900000095,6.007999897,5.907999992,3.900000095,0.022,5.907999992,3.900000095],\"weight\":-100, \"d\":0.0185,\"r\":0.015}\n";
    // deserializeJson(configDoc,jsonStr);
    // saveConfig();
    // loadConfig();

    int r = configDoc["weight"].as<int>();
    Serial.printf("weight: %d \n",r);

    float r2 = configDoc["r"].as<float>();
    Serial.printf("r2: %.6f \n",r2);

    #if !defined(CONFIG_IDF_TARGET_ESP32S3)
        log_i("not s3");
    #else
        log_i("s3");
    #endif

    ESP_LOGI(LOG_TAG, "---------------------------------setup end-----------------------------------------\n\n");

}

void loop()
{
  serialCtrl();
  float r = configDoc["r"].as<float>();
    Serial.printf("r: %.6f \n",r);
  // flash the LED
  myLED.brightness(0, 1); // turn the LED off
  delay(500);
  myLED.brightness(LED_BRIGHT, 1); // turn the LED on
  delay(500);
}

void mDns_init(){
  if (!MDNS.begin("cube_claster_1_1")) {
        Serial.println("Error setting up MDNS responder!");
        while(1){
            delay(1000);
        }
    }
    // Add service to MDNS-SD
    MDNS.addService("http", "tcp", 80);// add service, you can access to it by http://cube_claster_1_1.local
}
/****************** * /
bool load_poleFixedParam(){
    JsonArray h_glob=axisConfigDoc["H_glob"];
    JsonArray b_glob=axisConfigDoc["B_glob"];
    JsonArray a_loc=axisConfigDoc["A_loc"];
    
    printf("r=%f,d=%f,weight=%f,h_glob=%f\n",axisConfigDoc["r"],axisConfigDoc["d"],axisConfigDoc["weight"],h_glob[0].as<float>());
    
    // for (const auto& element : cv_config["targets"]) {
    // if(!axisConfigDoc.containsKey("r")) return false;
    // if(!axisConfigDoc.containsKey("d")) return false;
    // if(!axisConfigDoc.containsKey("weight")) return false;
    
    // if(!axisConfigDoc.containsKey("B_glob")) return false;
    // if(!axisConfigDoc.containsKey("H_glob")) return false;
    // if(!axisConfigDoc.containsKey("A_loc")) return false;

    pole_params.r = axisConfigDoc["r"].as<float>();
    pole_params.d = axisConfigDoc["d"].as<float>();
    pole_params.weight = axisConfigDoc["weight"].as<float>();
    
   //配置顺序为左下，逆时针
    for (uint8_t i=0;i<8;i++) {
        pole_params.B_glob[i].x = b_glob[i*3].as<float>();
        pole_params.B_glob[i].y = b_glob[i*3+1].as<float>();
        pole_params.B_glob[i].z = b_glob[i*3+2].as<float>();

        pole_params.H_glob[i].x = h_glob[i*3].as<float>();
        pole_params.H_glob[i].y = h_glob[i*3+1].as<float>();
        pole_params.H_glob[i].z = h_glob[i*3+2].as<float>();

        pole_params.A_loc[i].x = a_loc[i*3].as<float>();
        pole_params.A_loc[i].y = a_loc[i*3+1].as<float>();
        pole_params.A_loc[i].z = a_loc[i*3+2].as<float>();
        
        
    }

    
    for (uint8_t i = 0; i < 8; i++) {
            printf("B_glob[%d]=[%f,%f,%f],A_loc[%d]=[%f,%f,%f]\n",
            pole_params.B_glob[i].x ,pole_params.B_glob[i].y,pole_params.B_glob[i].z,
            pole_params.A_loc[i].x,pole_params.A_loc[i].y,pole_params.A_loc[i].z
            );

    }
    printf("r=%f,d=%f,weight=%f \n",pole_params.r,pole_params.d,pole_params.weight);

    return true;

}
/****************** */

bool loadConfig(){
    if(!LittleFS.exists("/config.json")){
        Serial.println("/config.json not exist.");
        return false;
    }
    File configFile = LittleFS.open("/config.json","r");
    if(configFile){
        Serial.println("/config.json load success.");
        String configText = configFile.readStringUntil('\n');
        Serial.println(configText);
        DeserializationError err = deserializeJson(configDoc,configText);
            if(err == DeserializationError::Ok){
                // Serial.println(receivedData); 
                // JsonObject obj = configDoc.to<JsonObject>();
                Serial.println("/config.json parseToJson success.");
            }else{
                Serial.printf("config.json DeserializationError: %s\n",configText.c_str());
            }
            configFile.close();
return true;
    }else{
        Serial.println("/config.json load fail.");
        return false;
    }
}
bool saveConfig()
{
    File configFile = LittleFS.open("/config.json", "w");
    if (configFile)
    {
        serializeJson(configDoc,configFile);
        Serial.println("/config.json save success.");
        configFile.close();
        return true;
    }
    else
    {
        Serial.println("/config.json load fail.");
        return false;
    }
}