#include <MQTT/custom/mqtt_topics.h>

// Dictionary of subscribed topics (ESP32 incoming topic)
Dictionary<String, String> subscribedTopics = Dictionary<String, String>();

// Dictionary of published topics (topic coming out of ESP32)
Dictionary<String, String> publishedTopics = Dictionary<String, String>();

// Compile the dictionary of subscribed topics (to be customized)
void compileSubTopics(Dictionary<String, String> &subTopics) {
  // Yellow LED control subscribed topic  
  subTopics.set("yellowOnOffTopic", thisClient "/yellowTopic");
  // Red LED control subscribed topic
  subTopics.set("redOnOffTopic", thisClient "/redTopic");
  // Blue LED control subscribed topic
  subTopics.set("blueOnOffTopic", thisClient "/blueTopic");
  // Subscribed topic for printing messages
  subTopics.set("inputTopic", thisClient "/input");
}

// Compile the dictionary of published topics (to be customized)
void compilePubTopics(Dictionary<String, String> &pubTopics) {
  // Message Publishing Topic
  pubTopics.set("outTopic", thisClient "/output");
}