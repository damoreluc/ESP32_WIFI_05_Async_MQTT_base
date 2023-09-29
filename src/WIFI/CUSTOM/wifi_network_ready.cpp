#include <WIFI/wifi_functions.h>
#include <HWCONFIG/hwConfig.h>
#include <LOCALTIME/localTime.h>
#include <MQTT/mqtt_functions.h>

// Top layer operations to perform when the IP layer is ready
void WiFiNetworkReady()
{
    digitalWrite(pinWiFiConnected, HIGH);

    // connect to NTP server
    connectToNTP();
    // pretty print local time and date
    printLocalTime();
    
    // connect to MQTT broker
    connectToMqtt();
}