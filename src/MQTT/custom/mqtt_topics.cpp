#include <MQTT/custom/mqtt_topics.h>

//Dizionario dei subscribed topics (topic in ingresso alla ESP32)
Dictionary<String, String> subscribedTopics = Dictionary<String, String>();

//Dizionario dei published topics (topic in uscita dalla ESP32)
Dictionary<String, String> publishedTopics = Dictionary<String, String>();

// compila il dizionario dei subscribed topics (da personalizzare)
void compileSubTopics(Dictionary<String, String> &subTopics) {
  // // subscribed topic di comando del led verde  
  // subTopics.set("greenOnOffTopic", thisClient "/greenTopic/onoff");
  // // subscribed topic di comando del led rosso
  // subTopics.set("redOnOffTopic", thisClient "/redTopic/onoff");
  // // subscribed topic di comando on/off del led blu
  // subTopics.set("blueOnOffTopic", thisClient "/blueTopic/onoff");
  // // subscribed topic di comando pwm del led blu
  // subTopics.set("bluePwmTopic", thisClient "/blueTopic/pwm"); 
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