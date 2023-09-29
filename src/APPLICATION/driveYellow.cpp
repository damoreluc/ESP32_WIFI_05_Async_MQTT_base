#include <APPLICATION/application.h>
#include <HWCONFIG/hwConfig.h>

// Control on/off yellow LED from payload
void driveOnOffYellow(char *data)
{
    if (strncmp(data, "0", 1) == 0)
    {
        digitalWrite(pinYellow, LOW);
        Serial.println("Yellow LED off");
    }
    else if (strncmp(data, "1", 1) == 0)
    {
        digitalWrite(pinYellow, HIGH);
        Serial.println("Yellow LED off");
    }
}