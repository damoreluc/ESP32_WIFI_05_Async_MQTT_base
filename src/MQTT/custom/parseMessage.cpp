#include <MQTT/mqtt_functions.h>
#include <MQTT/custom/custom.h>
#include <MQTT/custom/mqtt_topics.h>
#include <HWCONFIG/hwConfig.h>

// operazioni da eseguire quando viene ricevuto un messaggio
// viene richiamata da mqtt_onMqttMessage()
void parseMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
    // da personalizzare

    // print some information about the received message
    printRcvMsg(topic, payload, properties, len, index, total);

    // comando del led giallo
    // è arrivato un messaggio da yellowTopic
    if (strcmp(topic, subscribedTopics.get("yellowTopic").c_str()) == 0) 
    {
        if (strncmp(payload, "0", 1) == 0)
        {
            digitalWrite(pinYellow, LOW);
            Serial.println("led giallo spento");
        }
        else if (strncmp(payload, "1", 1) == 0)
        {
            digitalWrite(pinYellow, HIGH);
            Serial.println("led giallo acceso");
        }
    }

    // comando del led rosso
    // è arrivato un messaggio da redTopic
    else if (strcmp(topic, subscribedTopics.get("redTopic").c_str()) == 0) 
    {
        if (strncmp(payload, "0", 1) == 0)
        {
            digitalWrite(pinRed, LOW);
            Serial.println("led rosso spento");
        }
        else if (strncmp(payload, "1", 1) == 0)
        {
            digitalWrite(pinRed, HIGH);
            Serial.println("led rosso acceso");
        }
    }

    // comando del led blu
    // è arrivato un messaggio da blueTopic
    else if (strcmp(topic, subscribedTopics.get("blueTopic").c_str()) == 0) 
    {
        if (strncmp(payload, "0", 1) == 0)
        {
            digitalWrite(pinBlue, LOW);
            Serial.println("led blu spento");
        }
        else if (strncmp(payload, "1", 1) == 0)
        {
            digitalWrite(pinBlue, HIGH);
            Serial.println("led blu acceso");
        }
    }    
}