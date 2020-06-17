#include <stdint.h>
#include "LedDriver.h"
#include "RuntimeErrorStub.h"


enum {ALL_LEDS_OFF = 0x0, ALL_LEDS_ON = 0xFFFF};

static uint16_t *ledsAddress;
static uint16_t ledsImage;

// Private prototypes
static uint16_t convertLedNumberToBit(uint16_t ledNumber);
static void updateLedHardware(void);

uint8_t LedDriver_Init(uint16_t *address)
{
    ledsAddress = address;
    ledsImage = ALL_LEDS_OFF;
    updateLedHardware();
}

void LedDriver_TurnOn(uint16_t ledNumber)
{
    if (ledNumber <= 0 || ledNumber > 16) {
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", -1);
        return;
    }
    ledsImage |= convertLedNumberToBit(ledNumber);
    updateLedHardware();
}

void LedDriver_TurnOff(uint16_t ledNumber)
{
    if (ledNumber <= 0 || ledNumber > 16) {
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", -1);
        return;
    }
    ledsImage &= ~(convertLedNumberToBit(ledNumber));
    updateLedHardware();
}

void LedDriver_TurnAllOn(void)
{
    ledsImage = ALL_LEDS_ON;
    updateLedHardware();
}

static uint16_t convertLedNumberToBit(uint16_t ledNumber)
{
    return 1 << (ledNumber - 1);
}

static void updateLedHardware(void)
{
    *ledsAddress = ledsImage;
}
