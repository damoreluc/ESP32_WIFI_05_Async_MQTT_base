#include <MQTT/custom/custom.h>
#include <MQTT/custom/mqtt_topics.h>

// Upload the list of topics on which you will publish
// It is invoked by configMqttClient()
void topicsToPublish() {
  // build the publishing topics dictionary
  compilePubTopics(publishedTopics);    
}