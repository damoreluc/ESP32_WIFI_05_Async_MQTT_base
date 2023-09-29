#include <WIFI/wifi_functions.h>
#include <MQTT/mqtt_functions.h>

// Operations to be performed on the upper layers if the IP layer has fallen
void WiFiNetworkFail() {
    // stops monitoring the MQTT connection 
    // while WiFi connection is being restored
    stopTimersRTOS();
}