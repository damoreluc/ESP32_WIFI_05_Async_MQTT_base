#ifndef _WIFI_FUNCTIONS_H
#define _WIFI_FUNCTIONS_H

#include <Arduino.h>
#include <WIFI/credentials.h>
#include <WiFi.h>

// configure the WiFi module as a STATION and connects to an Access Point
// with credentials defined in the credentials.h file
void initWiFi_STA();

// WiFi Event Management
void WiFiEvent(WiFiEvent_t event);

// Print the obtained IP address
void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info);

// Print the access point connection confirmation
void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info);

// Managing disconnection and attempting to reconnect
void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info);

// Top layer operations to perform when the IP layer is ready
void WiFiNetworkReady();

// Operations to be performed on the upper layers if the IP layer has fallen
void WiFiNetworkFail();

#endif
