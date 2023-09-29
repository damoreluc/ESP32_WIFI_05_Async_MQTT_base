#ifndef _MQTT_TOPICS_H
#define _MQTT_TOPICS_H

#include <Arduino.h>
#include <dependencies/Dictionary/Dictionary.h>
#include <MQTT/custom/clientID.h>

// Dictionary of subscribed topics (ESP32 incoming topic)
extern Dictionary<String, String> subscribedTopics;

// Dictionary of published topics (topic coming out of ESP32)
extern Dictionary<String, String> publishedTopics;

// Compile the dictionary of subscribed topics (to be customized)
void compileSubTopics(Dictionary<String, String> &subTopics);

// Compile the dictionary of published topics (to be customized)
void compilePubTopics(Dictionary<String, String> &pubTopics);

#endif