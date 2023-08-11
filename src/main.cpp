/*
 * WiFi Esempio 05: <br>controllo led RGB da client MQTT con connessione a rete WiFi
 * 
 * Il progetto realizza il controllo del colore di un led RGB tramite il client MQTT. 
 * Va considerato come riferimento per progetti più articolati basati sul protocollo MQTT su ESP32.
 * 
 * Impiega la libreria `AsyncMqttClient` (link: https://github.com/OttoWinter/async-mqtt-client)
 * (vedi anche https://github.com/khoih-prog/AsyncMQTT_ESP32 con documentazione più completa)
 * 
 * L'esempio accetta due subscribed topics:
 *   ESP32_base/rgb/pwm  per il controllo del led RGB
 *   ESP32_base/input    per la stampa di un messaggio di testo sulla console seriale
 * 
 * e pubblica sul topic:
 *   ESP32_base/output`
 * un testo che rappresenta lo stato attuale di un pulsante.
 * 
 * Il controllo del led RGB richiede che venga specificato un valore numerico a 24 bit:
 *  gli 8 bit più significativi rappresentano l'intensità del rosso (da 0 a 255)
 *  gli 8 bit intermedi stabiliscono l'intensità del verde
 *  gli 8 bit meno significativi definiscono l'intensità del blu
 * 
 * Il dato arriverà nel payload come sequenza di 6 caratteri che rappresentano cifre esadecimali. 
 * Ad esempio:
 *  FF0000 indica il colore rosso
 *  FFFF00 indica il colore giallo
 * 
 * Una volta ricavato il valore di ciascun colore primario (R, G, B) lo si utilizza per modificare
 * il duty cycle di tre generatori PWM che comandano gli anodi del led RGB.
 * 
 * CONFIGURAZIONE WIFI ------------------------------------------------------------------------------
 * La scheda ESP32 è configurata come STATION in una rete WiFi: 
 * modificare il file WIFI/credentials.h con i propri SSID e Password
 * Per il controllo dello stato della connessione vengono adoperati gli eventi dell'oggetto Wifi
 * Vengono gestite le situazioni di perdita di connessione mediante riconnessione automatica.
 * Il pin 23 viene impiegato come uscita digitale per indicare la connessione all'access point wiFi.
 * 
 * SINCONIZZAZIONE DATA/ORA CON NTP SERVER ----------------------------------------------------------
 * Viene utilizzato un server NTP per la gestione di data e ora:
 * modificare il file LOCALTIME/localTime.cpp con i propri parametri NTP 
 * 
 * CONFIGURAZIONE DEL BROKER MQTT DA IMPIEGARE ------------------------------------------------------
 * Sono predefiniti tre broker MQTT tramite i file di configurazione:
 *   MQTT/broker/mosquitto.h
 *   MQTT/broker/raspi4.h
 *   MQTT/broker/shiftr_io.h
 * 
 * ed è possibile aggiungerne altri rispettando il formato del file ed il nome delle variabili:
 * 
 *   #ifndef __NOMEBROKER_H
 *   #define __NOMEBROKER_H
 *     // parametri di accesso per il broker NOMEBROKER MQTT
 *     const char *mqttServer = "IP_o_url_del_broker_MQTT";
 *     const int mqttPort = 1883;
 *     const char *mqttUser = "eventuale_username_di_accesso_al_broker";
 *     const char *mqttPassword = "eventuale_password_di_accesso_al_broker";
 *   #endif
 * 
 * Nel file main.cpp includere il solo file prescelto di accesso al broker, ad esempio:
 *    // your MQTT Broker:
 *    // uncomment one of following #include to set the MQTT broker.
 *    #include <MQTT/broker/shiftr_io.h>
 *    // #include <MQTT/broker/raspi4.h>
 *    // #include <MQTT/broker/mosquitto.h>
 * 
 * IMPORTANTE: NON includere più di un file di definizione del broker
 * 
 * FUNZIONE SETUP() ---------------------------------------------------------------------------
 * Nella funzione setup() è importante rispettare la sequenza di operazioni:
 * 1. configurare tutti i dispositivi hardware
 * 2. assegnare i valori predefiniti a variabili/oggetti della applicazione
 * 3. creare eventuali task RTOS
 * 4. configurare il client MQTT con configMqttClient(mqttServer, mqttPort, mqttUser, mqttPassword);
 * 5. avviare il sotto sistema WiFi con initWiFi_STA();
 * 
 */

// include delle librerie minime necessarie
#include <Arduino.h>
#include <HWCONFIG/hwConfig.h>
#include <WiFi.h>
#include <WIFI/wifi_functions.h>
#include <MQTT/mqtt_functions.h>
#include <MQTT/custom/custom.h>

// altre librerie richieste dalla applicazione specifica
#include <Bounce2.h>
#include <APPLICATION/application.h>

// your MQTT Broker:
// uncomment one of following #include to set the MQTT broker.
#include <MQTT/broker/shiftr_io.h>
// #include <MQTT/broker/raspi4.h>
// #include <MQTT/broker/mosquitto.h>

// semplice ingresso digitale
Bounce button = Bounce();

void setup()
{
  Serial.begin(115200);
  Serial.println("WiFi Esempio 05: connessione ad un broker MQTT, comando di tre led e monitoraggio di un pulsante");

  // configura tre led di prova comandati tramite messaggi MQTT
  // l'interpretazione dei messaggi e l'esecuzione dei comandi
  // viene svolta nel file MQTT/custom/parseMessage.cpp  (da personalizzare)
  pinMode(pinGreen, OUTPUT);
  pinMode(pinRed, OUTPUT);
  pinMode(pinBlue, OUTPUT);

  // configurazione pwm per il led RGB
  configPWM(channelGreen, pinGreen);
  configPWM(channelRed, pinRed);  
  configPWM(channelBlue, pinBlue);
  setDutyCycle(channelGreen, 0);
  setDutyCycle(channelRed, 0); 
  setDutyCycle(channelBlue, 0); 

  // configura un ingresso digitale come pulsante gestito da Bounce2.h
  button.attach(pinButton, INPUT_PULLUP);


  // impiega il metodo macAddress() dell'oggetto WiFi
  Serial.println();
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());

  // configurazione del client mqtt
  configMqttClient(mqttServer, mqttPort, mqttUser, mqttPassword);

  // avvia la connessione ad un access point e registra gli handler degli eventi WiFi;
  // con l'evento GotIP vengono avviate le connessioni:
  // al server NTP
  // e al broker MQTT
  initWiFi_STA();
}

void loop()
{
  // Update the Bounce instance (YOU MUST DO THIS EVERY LOOP)
  button.update();

  if (button.fell())
  {
    const char msgButton[] = "Pulsante premuto";
    Serial.println(msgButton);

    // pubblica sul topic outTopic
    if(mqttClient.connected()) {
      
      uint16_t res = 0;
      res = mqttClient.publish(publishedTopics.get("outTopic").c_str(),0,false, msgButton, strlen(msgButton),false, 0);
    }
  } else if (button.rose())
  {
    const char msgButton[] = "Pulsante rilasciato";
    Serial.println(msgButton);

    // pubblica sul topic outTopic
    if(mqttClient.connected()) {
      
      uint16_t res = 0;
      res = mqttClient.publish(publishedTopics.get("outTopic").c_str(),0,false, msgButton, strlen(msgButton),false, 0);
    }
  }

  vTaskDelay(pdMS_TO_TICKS(100));
}