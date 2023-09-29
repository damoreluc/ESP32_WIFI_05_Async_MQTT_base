#include <APPLICATION/application.h>
#include <HWCONFIG/hwConfig.h>

// Control on/off red LED from payload
void driveOnOffRed(char *data)
{
    if (strncmp(data, "0", 1) == 0)
    {
        digitalWrite(pinRed, LOW);
        Serial.println("Red LED off");
    }
    else if (strncmp(data, "1", 1) == 0)
    {
        digitalWrite(pinRed, HIGH);
        Serial.println("Red LED on");
    }
}