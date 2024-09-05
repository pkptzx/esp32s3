#include <Arduino.h>
#include <LiteLED.h>


// Choose the LED type from the list below.
// Comment out all but one LED_TYPE.
#define LED_TYPE        LED_STRIP_WS2812
// #define LED_TYPE        LED_STRIP_SK6812
// #define LED_TYPE        LED_STRIP_APA106
// #define LED_TYPE        LED_STRIP_SM16703

#define LED_TYPE_IS_RGBW 0   // if the LED is an RGBW type, change the 0 to 1

#define LED_GPIO 4     // change this number to be the GPIO pin connected to the LED

#define LED_BRIGHT 30   // sets how bright the LED is. O is off; 255 is burn your eyeballs out (not recommended)


static const crgb_t L_RED = 0xff0000;
static const crgb_t L_GREEN = 0x00ff00;
static const crgb_t L_BLUE = 0x0000ff;
static const crgb_t L_WHITE = 0xe0e0e0;

LiteLED myLED( LED_TYPE, LED_TYPE_IS_RGBW );    // create the LiteLED object; we're calling it "myLED"
 

void setup() {
  Serial.begin(115200); 
  Serial.println("Welcome to Wokwi, ESP32-S3");
  // put your setup code here, to run once:
   
  Serial.printf("version: %s\n",VERSION);

    Serial.println("开发板信息:");
  Serial.print("芯片ID: 0x");
  Serial.println(ESP.getChipRevision(), HEX);
  Serial.printf("核心数: %d\n",ESP.getChipCores());
  Serial.println("SDK版本: " + String(ESP.getSdkVersion()));
  Serial.println("CPU频率: " + String(ESP.getCpuFreqMHz()) + " MHz");
  Serial.println("Flash 容量: " + String(ESP.getFlashChipSize()/1024/1024) + " MB");
  Serial.println("Flash 速度: " + String(ESP.getFlashChipSpeed()/1000000) + " MHz");
  Serial.println("Flash 模式: " + String(ESP.getFlashChipMode()));
  Serial.println("PSRAM 容量: " + String(ESP.getPsramSize()/1024/1024) + " MB");

   myLED.begin( LED_GPIO, 1 );         // initialze the myLED object. Here we have 1 LED attached to the LED_GPIO pin
    myLED.brightness( LED_BRIGHT );     // set the LED photon intensity level
    myLED.setPixel( 0, L_GREEN, 1 );    // set the LED colour and show it
    delay( 2000 );

}

void loop() {
      // flash the LED
    myLED.brightness( 0, 1 );           // turn the LED off
    delay( 1000 );

    myLED.brightness( LED_BRIGHT, 1 );  // turn the LED on
    delay( 1000 );
} 