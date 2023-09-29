#include <APPLICATION/application.h>
#include <HWCONFIG/hwConfig.h>

// Control on/off blue LED from payload
void driveOnOffBlue(char *data)
{
    if (strncmp(data, "0", 1) == 0)
    {
        digitalWrite(pinBlue, LOW);
        Serial.println("Blue LED off");
    }
    else if (strncmp(data, "1", 1) == 0)
    {
        digitalWrite(pinBlue, HIGH);
        Serial.println("Blue LED on");
    }
}