#ifndef LEDDRIVER_H
#define LEDDRIVER_H

uint8_t LedDriver_Init(uint16_t *address);
void LedDriver_TurnOn(uint16_t ledNumber);
void LedDriver_TurnOff(uint16_t ledNumber);
void LedDriver_TurnAllOn(void);


#endif // LEDDRIVER_H
