#define BLYNK_TEMPLATE_ID "TMPL3EPAAWVsV"
#define BLYNK_TEMPLATE_NAME "EspNow"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

#include "BlynkEdgent.h"
#include <espnow.h>
#include <ESP8266WiFi.h>

typedef struct myData {
  int x;
  int y;
} myData;
myData dataObj; 

uint8_t macAddr[] = {0xC8, 0xC9, 0xA3, 0x6B, 0x07, 0xAF};

void setup()
{
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
  
  WiFi.mode(WIFI_STA); // Set device as a Wi-Fi Station

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER); //set role
 
  // add NodeMCU 2 as a peer
  esp_now_add_peer(macAddr, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
}

void loop() {
  BlynkEdgent.run();
  esp_now_send(macAddr, (uint8_t *) &dataObj, sizeof(dataObj));
  delay(800);
}

BLYNK_WRITE(V0){
  dataObj.x = param.asInt();
  Serial.print("x value: ");
  Serial.println(dataObj.x);
}

BLYNK_WRITE(V1){
 dataObj.y = param.asInt();
   Serial.print("y value: ");
   Serial.println(dataObj.y);
}

