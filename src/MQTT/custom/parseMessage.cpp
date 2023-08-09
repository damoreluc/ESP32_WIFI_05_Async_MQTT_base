#include <MQTT/mqtt_functions.h>
#include <MQTT/custom/custom.h>
#include <MQTT/custom/mqtt_topics.h>
#include <HWCONFIG/hwConfig.h>
#include <APPLICATION/application.h>

// operazioni da eseguire quando viene ricevuto un messaggio
// viene richiamata da mqtt_onMqttMessage()
void parseMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
    // bonifica del payload
    // estrae solo i primi len caratteri del payload
    char data[len + 1];
    strncpy(data, payload, len);

    // print some information about the received message
    printRcvMsg(topic, payload, properties, len, index, total);

    // da personalizzare

    // comando del led giallo
    // è arrivato un messaggio da greenOnOffTopic
    if (strcmp(topic, subscribedTopics.get("greenOnOffTopic").c_str()) == 0)
    {
        // comanda on/off led verde a partire dal payload
        driveOnOffGreen(data);
    }

    // comando del led rosso
    // è arrivato un messaggio da redOnOffTopic
    else if (strcmp(topic, subscribedTopics.get("redOnOffTopic").c_str()) == 0)
    {
        // comanda on/off led rosso a partire dal payload
        driveOnOffRed(data);
    }

    // comando on/off del led blu
    // è arrivato un messaggio da blueOnOffTopic
    else if (strcmp(topic, subscribedTopics.get("blueOnOffTopic").c_str()) == 0)
    {
        if (strncmp(data, "0", 1) == 0)
        {
            digitalWrite(pinBlue, LOW);
            Serial.println("led blu spento");
        }
        else if (strncmp(data, "1", 1) == 0)
        {
            digitalWrite(pinBlue, HIGH);
            Serial.println("led blu acceso");
        }
    }

    // comando pwm del led RGB
    // è arrivato un messaggio da rgbPwmTopic
    else if (strcmp(topic, subscribedTopics.get("rgbPwmTopic").c_str()) == 0)
    {
        // aggiorna il pwm sul led RGB a partire dal payload
        drivePWMRGB(data);
    }
}