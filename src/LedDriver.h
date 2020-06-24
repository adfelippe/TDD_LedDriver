#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#include <stdint.h>
#include <stdbool.h>

uint8_t LedDriver_Init(uint16_t *address);
void LedDriver_TurnOn(uint16_t ledNumber);
void LedDriver_TurnOff(uint16_t ledNumber);
void LedDriver_Toggle(uint16_t ledNumber);
void LedDriver_TurnAllOn(void);
void LedDriver_TurnAllOff(void);
bool LedDriver_IsLedOn(uint16_t ledNumber);
bool LedDriver_IsLedOff(uint16_t ledNumber);


#endif // LEDDRIVER_H
