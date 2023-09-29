#include <WIFI/wifi_functions.h>
#include <HWCONFIG/hwConfig.h>

void initWiFi_STA() {
  // controls an LED to indicate the connection to the WiFi access point
  pinMode(pinWiFiConnected, OUTPUT);

  WiFi.mode(WIFI_STA);

  // WiFi event management
  WiFi.onEvent(WiFiEvent, WiFiEvent_t::ARDUINO_EVENT_MAX);
 // WiFi.onEvent(WiFiStationConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED);
 // WiFi.onEvent(WiFiGotIP, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(WiFiStationDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println(F("Connecting to WiFi "));
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.printf(" \n");
}