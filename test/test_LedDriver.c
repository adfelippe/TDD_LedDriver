#include "unity.h"
#include "LedDriver.h"


uint16_t virtualLeds;

void setUp(void)
{
    LedDriver_Init(&virtualLeds);
}

void tearDown(void)
{
}

void test_LedDriver_LedsOffAfterInitialization(void)
{
	virtualLeds = 0xFFFF;
	LedDriver_Init(&virtualLeds);
	TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

void test_LedDriver_TurnOnLedOne(void)
{
    LedDriver_TurnOn(1);
    TEST_ASSERT_EQUAL_HEX16(1, virtualLeds);
}

void test_LedDriver_TurnOffLedOne(void)
{
    LedDriver_TurnOff(1);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

void test_LedDriver_TurnOnMultipleLeds(void)
{
    LedDriver_TurnOn(9);
    LedDriver_TurnOn(8);
    TEST_ASSERT_EQUAL_HEX16(0x180, virtualLeds);
}

void test_LedDriver_TurnAllOn(void)
{
    LedDriver_TurnAllOn();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, virtualLeds);
}

void test_LedDriver_LedTurnOffAnyLed(void)
{
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(8);
    TEST_ASSERT_EQUAL_HEX16(0xFF7F, virtualLeds);
}

void test_LedDriver_LedMemoryIsNotReadable(void)
{
    virtualLeds = 0xFFFF;
    LedDriver_TurnOn(8);
    TEST_ASSERT_EQUAL_HEX16(0x80, virtualLeds);
}
