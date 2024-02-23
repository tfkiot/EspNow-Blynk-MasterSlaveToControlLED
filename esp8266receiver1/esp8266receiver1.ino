#include <ESP8266WiFi.h>
#include <espnow.h>

#define led1 D2
#define led2 D5

typedef struct myData {
  int x;
  int y;
} myData;
myData dataObj;

// Callback function
void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&dataObj, incomingData, sizeof(dataObj));
  Serial.println("_______________");

  Serial.print("x value: ");
  Serial.println(dataObj.x);
  dataObj.x ? digitalWrite(led1, HIGH) : digitalWrite(led1, LOW);

  Serial.print("y value: ");
  Serial.println(dataObj.y);
  dataObj.y ? digitalWrite(led2, HIGH) : digitalWrite(led2, LOW);
}

void setup() {
  Serial.begin(115200);  // Initialize Serial Monitor
  WiFi.mode(WIFI_STA);   // Set device as a Wi-Fi Station

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);  // Set role

  esp_now_register_recv_cb(OnDataRecv);  // Set callback
}

void loop() {
  //
}