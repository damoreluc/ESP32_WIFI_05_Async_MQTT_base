#include <APPLICATION/application.h>

// aggiorna il duty cycle su un canale
void setDutyCycle(uint8_t canale, uint16_t dutyCycle) {
// modifica del valore del duty cycle
    ledcWrite(canale, dutyCycle);    
}
