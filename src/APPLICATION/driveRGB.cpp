#include <APPLICATION/application.h>
#include <HWCONFIG/hwConfig.h>

// // aggiorna il pwm sul led RGB a partire dal payload
void drivePWMRGB(char *data)
{
    // la stringa data contiene le componenti R, G, B come valori esadecimali  rrggbb
    uint32_t number = (uint32_t)strtol(data, NULL, 16);
    uint16_t b = number & 0x0000FF;
    uint16_t g = (number >> 8) & 0x0000FF;
    uint16_t r = (number >> 16) & 0x0000FF;

    // aggiornamento dei tre duty cycles
    setDutyCycle(channelRed, r);
    setDutyCycle(channelGreen, g);
    setDutyCycle(channelBlue, b);
}