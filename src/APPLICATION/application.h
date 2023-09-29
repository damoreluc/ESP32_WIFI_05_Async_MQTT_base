#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <Arduino.h>

// Control on/off red LED from payload
void driveOnOffRed(char* data);
// Control on/off yellow LED from payload
void driveOnOffYellow(char* data);
// Control on/off blue LED from payload
void driveOnOffBlue(char* data);

#endif