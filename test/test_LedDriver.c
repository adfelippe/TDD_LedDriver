#include "unity.h"
#include "LedDriver.h"
#include "RuntimeErrorStub.h"


uint16_t virtualLeds;

void setUp(void)
{
    LedDriver_Init(&virtualLeds);
}

void tearDown(void)
{
    RuntimeErrorStub_Reset();
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

void test_LedDriver_TurnOffMultipleLeds(void)
{
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(9);
    LedDriver_TurnOff(8);
    TEST_ASSERT_EQUAL_HEX16((~0x180)&0xffff, virtualLeds);
}

void test_LedDriver_TurnAllOn(void)
{
    LedDriver_TurnAllOn();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, virtualLeds);
}

void test_LedDriver_TurnAllOff(void)
{
    LedDriver_TurnAllOn();
    LedDriver_TurnAllOff();
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
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

void test_LedDriver_IsLedOn(void)
{
    TEST_ASSERT_FALSE(LedDriver_IsLedOn(11));
    LedDriver_TurnOn(11);
    TEST_ASSERT_TRUE(LedDriver_IsLedOn(11));
}

void test_LedDriver_IsLedOff(void)
{
    TEST_ASSERT_TRUE(LedDriver_IsLedOff(12));
    LedDriver_TurnOn(12);
    TEST_ASSERT_FALSE(LedDriver_IsLedOff(12));
}

void test_LedDriver_UpperAndLowerBounds(void)
{
    LedDriver_TurnOn(1);
    LedDriver_TurnOn(16);
    TEST_ASSERT_EQUAL_HEX16(0x8001, virtualLeds);
}

void test_LedDriver_OutOfBoundsChangesNothing(void)
{
    LedDriver_TurnOn(-1);
    LedDriver_TurnOn(0);
    LedDriver_TurnOn(17);
    LedDriver_TurnOn(3141);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

void test_LedDriver_OutOfBoundsDoesNoHarm(void)
{
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(-1);
    LedDriver_TurnOff(0);
    LedDriver_TurnOff(17);
    LedDriver_TurnOff(3141);
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, virtualLeds);
}

void test_LedDriver_OutOfBoundsLedOnProducesRuntimeError(void)
{
    LedDriver_TurnOn(-1);
    TEST_ASSERT_EQUAL_STRING("LED Driver: out-of-bounds LED", RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}

void test_LedDriver_OutOfBoundsLedsAreAlwaysOff(void)
{
    TEST_ASSERT_FALSE(LedDriver_IsLedOn(0));
    TEST_ASSERT_FALSE(LedDriver_IsLedOn(17));
    TEST_ASSERT_TRUE(LedDriver_IsLedOff(0));
    TEST_ASSERT_TRUE(LedDriver_IsLedOff(17));
}

#if 0
void test_LedDriver_OutOfBoundsToDo(void)
{
    TEST_IGNORE_MESSAGE("Keep refactoring as tests pass!");
}
#endif
