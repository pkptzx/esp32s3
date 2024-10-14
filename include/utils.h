void getinfo()
{
    Serial.printf("version: %s\r\n", VERSION);

    Serial.println("开发板信息:");
    Serial.print("芯片ID: 0x");
    Serial.println(ESP.getChipRevision(), HEX);
    Serial.printf("核心数: %d\r\n", ESP.getChipCores());
    Serial.println("SDK版本: " + String(ESP.getSdkVersion()));
    Serial.println("CPU频率: " + String(ESP.getCpuFreqMHz()) + " MHz");
    Serial.println("Flash 容量: " + String(ESP.getFlashChipSize() / 1024 / 1024) + " MB");
    Serial.println("Flash 速度: " + String(ESP.getFlashChipSpeed() / 1000000) + " MHz");
    // Serial.printf("Flash 模式: %X\r\n", ESP.getFlashChipMode());
    Serial.println("PSRAM 容量: " + String(ESP.getPsramSize() / 1024 / 1024) + " MB");
    Serial.printf("Free PSRAM: %d\r\n", ESP.getFreePsram());
    Serial.printf("Deafult free size: %d\r\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
    Serial.printf("PSRAM free size: %d\r\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
}

void printMacAddress(const uint8_t *macBytes) {
  for (int i = 0; i < 6; i++) {
    Serial.print(macBytes[i], HEX);
    if (i < 5) {
      Serial.print(":");
    }
  }
  Serial.println();
}

// Helper function to convert a MAC address array to a string
String macToString(const uint8_t *mac) {
  String address = "";
  for (int i = 0; i < 6; ++i) {
    address += String(mac[i], HEX);
    if (i < 5) {
      address += ":";
    }
  }
  return address;
}