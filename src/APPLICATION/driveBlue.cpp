#include <APPLICATION/application.h>

// aggiorna il pwm sul led blu a partire dal payload
void driveBlue(char *data)
{
    uint16_t dutyCycle = 0;
    dutyCycle = atoi(data);
    Serial.printf("Duty cycle: %d\n", dutyCycle);
    setDutyCycle(0, dutyCycle);
}