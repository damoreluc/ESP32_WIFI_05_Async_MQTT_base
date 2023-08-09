#include <APPLICATION/application.h>

// impostazione dei parametri PWM
const int freq = 5000;
const int resolution = 8;
const int maxValue = (1<<resolution) - 1;

// configurazione generatore pwm
void configPWM(uint8_t canale, uint8_t pin) {
  // configurazione del canale PWM
  ledcSetup(canale, freq, resolution);
  
  // connessione del canale PWM al pin del LED
  ledcAttachPin(pin, canale);
}