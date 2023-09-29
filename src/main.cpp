/*
# WiFi Example 05: MQTT client template with WiFi network connection

The project is a basic model for building an MQTT client. It should be considered as a reference for more complex projects based on the MQTT protocol on ESP32.

It uses the library `AsyncMqttClient` (link: https://github.com/OttoWinter/async-mqtt-client)

(see also https://github.com/khoih-prog/AsyncMQTT_ESP32 with more complete documentation)

The sample accepts four subscribed topics:

* `ESP32_base/yellowTopic`  to turn on/off a yellow led
* `ESP32_base/redTopic`  to turn on/off a red led
* `ESP32_base/blueTopic`  to turn on/off a blue led 
* `ESP32_base/input`    to print a text message on the serial console

and publish on the topic:

* `ESP32_base/output`

a message that represents the current state of a button.


## Folder `\APPLICATION` ---------------------------------------------------------------------------

The `\APPLICATION` folder is designed to better organize your project code.
Enter here the auxiliary functions specific to the application under development, 
for example the callbacks to turn on and off the LEDs depending on the content of the payload.

## WIFI CONFIGURATION ------------------------------------------------------------------------------
The ESP32 board is configured as a __STATION__ on a WiFi network; 
edit the 'WIFI/credentials.h' file with your own 'SSID' and 'Password'

The WiFi object's events are used to check the connection status.
Connection loss situations are handled by automatic reconnection.

Pin '23' is used as a digital output to indicate connection to the WiFi access point. 
To configure another LED position, change the parameter 'pinWiFiConnected' in the file
'HWCONFIG\hwConfig.h'
 
## DATE/TIME SYNCHRONIZATION WITH NTP SERVER -------------------------------------------------------
A __NTP__ server is used to manage the date and time:
edit the file 'LOCALTIME/LOCALTime.cpp' with your own NTP parameters.
For date and time printing use the 'printLocalTime()' function.

## CONFIGURING THE MQTT BROKER TO USE --------------------------------------------------------------
Three MQTT brokers are predefined via their configuration files:
* `MQTT/broker/mosquitto.h`
* `MQTT/broker/raspi4.h`
* `MQTT/broker/shiftr_io.h`

and you can add others respecting the file format and the name of the variables: 

#ifndef __BROKERNAME_H
#define __BROKERNAME_H
  // Access parameters for the broker NOMEBROKER MQTT
  const char *mqttServer = "MQTT_broker_IP_Address_or_url";
  const int mqttPort = 1883;
  const char *mqttUser = "username_to_access_the_broker";
  const char *mqttPassword = "password_to_access_the_broker";
#endif


In the 'main.cpp' file, include __only__ the chosen broker login file, for example:

 // your MQTT Broker:
 // uncomment one of following #include to set the MQTT broker.
 #include <MQTT/broker/shiftr_io.h>
 // #include <MQTT/broker/raspi4.h>
 // #include <MQTT/broker/mosquitto.h>

__IMPORTANT__: __Do NOT__ include more than one broker definition file

##  SUBSCRIBED AND PUBLISHING TOPICS DEFINITION ------------------------------------------

Depending on the application to be created, you must define the _topics_ to which the 
client must subscribe to receive data or commands remotely.

The MQTT client must have a __unique__ name on the broker. 
The unique name is declared in file 'MQTT\custom\mqtt_topics.h', which you can customize:

 // MQTT client ID
 #define thisClient "ESP32_base"
 
The topics on which the client publishes data to the broker must then be defined.

Two dictionaries are used for this purpose:
* for _subscribed topics_ ("inputs" for the client):  `subscribedTopics`
* for _publishing topics_ ("outputs" for the client):  `publishedTopics`

Both dictionaries have the structure: `<key>, <value>` both entries are of type 'String'.

* `<key>` indicates a simple name to be assigned to the topic
* The `<value>` contains the _logical path_ of the topic.

Customization must be done in the file 'MQTT\custom\mqtt_topics.cpp'

For incoming topics (_Subscribed topics_) change the function:
   void compileSubTopics(Dictionary<String, String> &subTopics)

For outgoing topics (_Published topics_) change the function:
   void compilePubTopics(Dictionary<String, String> &pubTopics)

__Proceed in order:__

1. define what information the ESP32 board should receive from the broker and associate 
subscribed topics, defining a unique name (key) for each topic and its path on the broker.

For example: you want to remotely turn on/off a yellow LED connected to the ESP32;
    * define the _subscribed topic_ as (key) `"yellowOnOffTopic"`
    * with logical path  `"ESP32_base/yellowTopic"` 
    * From this topic will come the string `"0"` to turn off the LED, 
      or the string `"1"` to turn it on.
 
2. similarly, define what information the ESP32 will publish to the broker 
and associate publisher topics, defining a unique name for each topic and its path 
on the broker.

For example: You want to remotely notify that a button has been pressed or released;
    * define the _published topic_ as (key) `"outTopic"`
    * with logical path  `"ESP32_base/output"`
    * on this topic the ESP32 will send a message about the status of the button

3. For subscribed topics, in the `compileSubTopics()` function add the topic 
to the subscribed topics dictionary using the command:
      // Yellow LED control subscribed topic  
      subTopics.set("yellowTopic", thisClient "/yellowTopic");

4. Repeat step 3. for each _subscribed topic_ required by the application

5. for _publishing topic_, in the function `compilePubTopics()` add the topic 
to the dictionary of published topics using the command:
      // Message Publishing Topic
      pubTopics.set("outTopic", thisClient "/output");

 6. Repeat step 5. for each _published topic_ required by the application.

When the MQTT client starts, subscribed topics will be automatically registered on the broker.
 
## PARSING OF SUBSCRIBED TOPICS ---------------------------------------------------------------
The MQTT client handles traffic with the broker in _asynchronous mode_, so it is not necessary
for the application programmer to worry about the phases of receiving or transmitting data 
on the topics.

Instead, it is the __programmer's responsibility__ to decide what to do when a message 
is received on a subscribed topic.

In the `MQTT\custom\parseMessage.cpp`  file
the function `parseMessage()`  must be customized.

Referring to the case of the yellow LED shown above, in the `parseMessage()` function: 
1. you will check if it is the __topic__ described by the key `"yellowOnOffTopic"`. 
   If so, then you pass the content of the payload to the auxiliary function
   __programmed by the developer__ that will manage the information:

// What to do when a message is received
// it is called by mqtt_onMqttMessage() function
void parseMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
    // Payload cleanup
    // extracts only the first `len` characters of the payload
    char data[len + 1];
    strncpy(data, payload, len);

    // print some information about the received message
    printRcvMsg(topic, payload, properties, len, index, total);

    // to be customized

    // Yellow LED control
    // a message has arrived from yellowOnOffTopic
    if (strcmp(topic, subscribedTopics.get("yellowOnOffTopic").c_str()) == 0)
    {
        // Controls on/off yellow LED from payload
        driveOnOffYellow(data);
    }
}

2. in the auxiliary function, if the __payload__ is the string `"0"` then the yellow led
   is driven off; otherwise, if the __payload__ is the string `"1"` then the yellow led 
   is driven on.

The corresponding code structure is:

#include <APPLICATION/application.h>
#include <HWCONFIG/hwConfig.h>

// Controls on/off yellow LED from payload
void driveOnOffYellow(char *data)
{
    if (strncmp(data, "0", 1) == 0)
    {
        digitalWrite(pinYellow, LOW);
        Serial.println("Yellow LED turned off");
    }
    else if (strncmp(data, "1", 1) == 0)
    {
        digitalWrite(pinYellow, HIGH);
        Serial.println("Yellow LED turned on");
    }
}

__NOTE__: In payload string comparison operations (treated as _char array_) it is recommended
 to use the `strncmp()` comparison function specifying exactly the number of characters to be
 compared.


## PUBLICATION OF DATA ON PUBLISHING TOPICS ---------------------------------------------
Even the publication of a data from ESP32 to the broker is managed asynchronously by the layers
of the MQTT library.

In the application, it is sufficient for the programmer to use the `mqttClient.publish()` 
method whenever he wants to publish information about a particular topic.
The `mqttClient.publish()` method requires the following parameters:

* the topic on which to publish, for example `"ESP32_base/output"`
* the required QOS level (for example, 0)
* whether the message is a retain message or not
* the payload to be transmitted (for example, a char array containing text)
* the size _in byte_ of the payload

and returns the _packet ID_ (other than 0) of the message if it was able to put the payload
in the queue of messages to be published to the broker, otherwise it returns error code 0.

For example, to publish the status of the button, the programmer can write:

  if (button.fell())
  {
    const char msgButton[] = "Button pressed";
    Serial.println(msgButton);

    // publish on topic outTopic
    if(mqttClient.connected()) {
      uint16_t res = 0;
      res = mqttClient.publish(publishedTopics.get("outTopic").c_str(),0,false, msgButton, strlen(msgButton));
    }
  }


Note that the payload (the information sent on the channel defined by the topic) will be treated
by low-level layers as __array of byte__. 
Therefore, the payload can also be an `int`, a `float` or a user-defined data type, as long as 
its size in bytes can be determined and the data type is _recognizable_ and _manageable_ 
by those who will receive the information on the other side of the broker.


## THE SETUP() FUNCTION ---------------------------------------------------------------------------

In the `setup()` function it is important to respect the sequence of operations:

1. configure all hardware devices
2. assign default values to application variables/objects
3. create any RTOS tasks
4. configure the MQTT client with `configMqttClient(mqttServer, mqttPort, mqttUser, mqttPassword);`
5. start the WiFi subsystem with `initWiFi_STA();`

*/

// Minimum libraries required
#include <Arduino.h>
#include <HWCONFIG/hwConfig.h>
#include <WiFi.h>
#include <WIFI/wifi_functions.h>
#include <MQTT/mqtt_functions.h>
#include <MQTT/custom/custom.h>

// Other libraries required by the specific application
#include <Bounce2.h>

// your MQTT Broker:
// uncomment one of following #include to set the MQTT broker.
#include <MQTT/broker/shiftr_io.h>
// #include <MQTT/broker/raspi4.h>
// #include <MQTT/broker/mosquitto.h>

// simple digital input
Bounce button = Bounce();

void setup()
{
  Serial.begin(115200);
  Serial.println("WiFi Example 05: connection to an MQTT broker, control of three LEDs and monitoring of a button");

  // configures three test LEDs controlled via MQTT messages
  // interpreting messages and executing commands is carried out 
  // in the file MQTT/custom/parseMessage.cpp  (to be customized)
  pinMode(pinYellow, OUTPUT);
  pinMode(pinRed, OUTPUT);
  pinMode(pinBlue, OUTPUT);

  // Configure a digital input as a button managed by Bounce2.h
  button.attach(pinButton, INPUT_PULLUP);

  // uses the macAddress() method of the WiFi object
  Serial.println();
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());

  // Configuring the MQTT Client
  configMqttClient(mqttServer, mqttPort, mqttUser, mqttPassword);

  // initiates the connection to an access point and records the handlers of WiFi events;
  // The GotIP event initiates connections:
  // * to NTP server
  // * to MQTT broker
  initWiFi_STA();
}

void loop()
{
  // Update the Bounce instance (YOU MUST DO THIS EVERY LOOP)
  button.update();

  if (button.fell())
  {
    const char msgButton[] = "Button pressed";
    Serial.println(msgButton);

    // publish on topic outTopic
    if(mqttClient.connected()) {
      
      uint16_t res = 0;
      res = mqttClient.publish(publishedTopics.get("outTopic").c_str(),0,false, msgButton, strlen(msgButton),false, 0);
    }
  } else if (button.rose())
  {
    const char msgButton[] = "Button released";
    Serial.println(msgButton);

    // publish on topic outTopic
    if(mqttClient.connected()) {
      
      uint16_t res = 0;
      res = mqttClient.publish(publishedTopics.get("outTopic").c_str(),0,false, msgButton, strlen(msgButton),false, 0);
    }
  }

  vTaskDelay(pdMS_TO_TICKS(100));
}