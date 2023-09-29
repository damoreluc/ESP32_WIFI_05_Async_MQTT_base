#ifndef __CUSTOM_H
#define __CUSTOM_H

#include <MQTT/mqtt_functions.h>
// Functions to customize according to the project

// Upload the list of topics you want to subscribe to
// It is invoked in the configMqttClient()
void topicsToSubscribe();

// Upload the list of topics on which you will publish
// It is invoked in the configMqttClient()
void topicsToPublish();

// What to do when a message is received
// It is invoked by mqtt_onMqttMessage()
void parseMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);

#endif