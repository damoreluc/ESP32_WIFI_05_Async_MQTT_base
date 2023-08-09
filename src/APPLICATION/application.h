#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <Arduino.h>

// configurazione generatore pwm
void configPWM(uint8_t canale, uint8_t pin);

// aggiorna il duty cycle su un canale
void setDutyCycle(uint8_t canale, uint16_t dutyCycle);

// aggiorna il pwm sul led RGB a partire dal payload
void drivePWMRGB(char* data);

// comanda on/off led rosso a partire dal payload
void driveOnOffRed(char* data);
// comanda on/off led verde a partire dal payload
void driveOnOffGreen(char* data);
// comanda on/off led giallo a partire dal payload
void driveOnOffYellow(char* data);

#endif