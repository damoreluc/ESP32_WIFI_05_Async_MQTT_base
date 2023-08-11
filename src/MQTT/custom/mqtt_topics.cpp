#include <MQTT/custom/mqtt_topics.h>

//Dizionario dei subscribed topics (topic in ingresso alla ESP32)
Dictionary<String, String> subscribedTopics = Dictionary<String, String>();

//Dizionario dei published topics (topic in uscita dalla ESP32)
Dictionary<String, String> publishedTopics = Dictionary<String, String>();

// compila il dizionario dei subscribed topics (da personalizzare)
void compileSubTopics(Dictionary<String, String> &subTopics) {
  // subscribed topic di comando led rgb
  subTopics.set("rgbPwmTopic", thisClient "/rgb/pwm"); 
  // subscribed topic per stampa messaggi
  subTopics.set("inputTopic", thisClient "/input");
}

// compila il dizionario dei published topics (da personalizzare)
void compilePubTopics(Dictionary<String, String> &pubTopics) {
  // topic di pubblicazione messaggi
  pubTopics.set("outTopic", thisClient "/output");
}