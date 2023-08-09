#include <APPLICATION/application.h>
#include <HWCONFIG/hwConfig.h>

// comanda on/off led verde a partire dal payload
void driveOnOffGreen(char *data)
{
    if (strncmp(data, "0", 1) == 0)
    {
        digitalWrite(pinGreen, LOW);
        Serial.println("led verde spento");
    }
    else if (strncmp(data, "1", 1) == 0)
    {
        digitalWrite(pinGreen, HIGH);
        Serial.println("led verde acceso");
    }
}