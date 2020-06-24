#include "LedDriver.h"
#include "RuntimeErrorStub.h"


enum {ALL_LEDS_OFF = 0x0, ALL_LEDS_ON = 0xFFFF};
enum {FIRST_LED = 1, LAST_LED = 16};

static uint16_t *ledsAddress;
static uint16_t ledsImage;

// Private prototypes
static uint16_t convertLedNumberToBit(uint16_t ledNumber);
static void updateLedHardware(void);
static bool IsLedOutOfBounds(uint16_t ledNumber);
static void setLedImageBit(int ledNumber);
static void clearLedImageBit(int ledNumber);

uint8_t LedDriver_Init(uint16_t *address)
{
    ledsAddress = address;
    ledsImage = ALL_LEDS_OFF;
    updateLedHardware();
}

void LedDriver_TurnOn(uint16_t ledNumber)
{
    if (IsLedOutOfBounds(ledNumber)) {
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", -1);
        return;
    }

    setLedImageBit(ledNumber);
    updateLedHardware();
}

void LedDriver_TurnOff(uint16_t ledNumber)
{
    if (IsLedOutOfBounds(ledNumber)) {
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", -1);
        return;
    }

    clearLedImageBit(ledNumber);
    updateLedHardware();
}

void LedDriver_TurnAllOn(void)
{
    ledsImage = ALL_LEDS_ON;
    updateLedHardware();
}

void LedDriver_TurnAllOff(void)
{
    ledsImage = ALL_LEDS_OFF;
    updateLedHardware();
}

void LedDriver_Toggle(uint16_t ledNumber)
{
    if (LedDriver_IsLedOn(ledNumber))
        LedDriver_TurnOff(ledNumber);
    else
        LedDriver_TurnOn(ledNumber);
}

bool LedDriver_IsLedOn(uint16_t ledNumber)
{
    if (IsLedOutOfBounds(ledNumber))
        return false;
    else
        return ledsImage & (convertLedNumberToBit(ledNumber));
}

bool LedDriver_IsLedOff(uint16_t ledNumber)
{
    return !LedDriver_IsLedOn(ledNumber);
}

static uint16_t convertLedNumberToBit(uint16_t ledNumber)
{
    return 1 << (ledNumber - 1);
}

static void updateLedHardware(void)
{
    *ledsAddress = ledsImage;
}

static bool IsLedOutOfBounds(uint16_t ledNumber)
{
    return (ledNumber < FIRST_LED || ledNumber > LAST_LED);
}

static void setLedImageBit(int ledNumber)
{
    ledsImage |= convertLedNumberToBit(ledNumber);
}

static void clearLedImageBit(int ledNumber)
{
    ledsImage &= ~(convertLedNumberToBit(ledNumber));
}
