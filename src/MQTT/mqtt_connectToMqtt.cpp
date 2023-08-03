#include <MQTT/mqtt_functions.h>

// begin connection to MQTT broker
void connectToMqtt()
{
  Serial.println(F("Connecting to MQTT..."));
  mqttClient.connect();
}