#include "build/temp/_test_LedDriver.c"
#include "RuntimeErrorStub.h"
#include "LedDriver.h"
#include "unity.h"




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

 UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

((void *)0)

), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_HEX16);

}



void test_LedDriver_TurnOnLedOne(void)

{

    LedDriver_TurnOn(1);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((1)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(28), UNITY_DISPLAY_STYLE_HEX16);

}



void test_LedDriver_TurnOffLedOne(void)

{

    LedDriver_TurnOff(1);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_HEX16);

}



void test_LedDriver_TurnOnMultipleLeds(void)

{

    LedDriver_TurnOn(9);

    LedDriver_TurnOn(8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x180)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(41), UNITY_DISPLAY_STYLE_HEX16);

}



void test_LedDriver_TurnOffMultipleLeds(void)

{

    LedDriver_TurnAllOn();

    LedDriver_TurnOff(9);

    LedDriver_TurnOff(8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)(((~0x180)&0xffff)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(49), UNITY_DISPLAY_STYLE_HEX16);

}



void test_LedDriver_TurnAllOn(void)

{

    LedDriver_TurnAllOn();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xFFFF)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(55), UNITY_DISPLAY_STYLE_HEX16);

}



void test_LedDriver_TurnAllOff(void)

{

    LedDriver_TurnAllOn();

    LedDriver_TurnAllOff();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(62), UNITY_DISPLAY_STYLE_HEX16);

}



void test_LedDriver_LedTurnOffAnyLed(void)

{

    LedDriver_TurnAllOn();

    LedDriver_TurnOff(8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xFF7F)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(69), UNITY_DISPLAY_STYLE_HEX16);

}



void test_LedDriver_LedMemoryIsNotReadable(void)

{

    virtualLeds = 0xFFFF;

    LedDriver_TurnOn(8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x80)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(76), UNITY_DISPLAY_STYLE_HEX16);

}



void test_LedDriver_IsLedOn(void)

{

    if (!(LedDriver_IsLedOn(11))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(81)));};

    LedDriver_TurnOn(11);

    if ((LedDriver_IsLedOn(11))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(83)));};

}



void test_LedDriver_IsLedOff(void)

{

    if ((LedDriver_IsLedOff(12))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(88)));};

    LedDriver_TurnOn(12);

    if (!(LedDriver_IsLedOff(12))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(90)));};

}



void test_LedDriver_UpperAndLowerBounds(void)

{

    LedDriver_TurnOn(1);

    LedDriver_TurnOn(16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x8001)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(97), UNITY_DISPLAY_STYLE_HEX16);

}



void test_LedDriver_OutOfBoundsChangesNothing(void)

{

    LedDriver_TurnOn(-1);

    LedDriver_TurnOn(0);

    LedDriver_TurnOn(17);

    LedDriver_TurnOn(3141);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(106), UNITY_DISPLAY_STYLE_HEX16);

}



void test_LedDriver_OutOfBoundsDoesNoHarm(void)

{

    LedDriver_TurnAllOn();

    LedDriver_TurnOff(-1);

    LedDriver_TurnOff(0);

    LedDriver_TurnOff(17);

    LedDriver_TurnOff(3141);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xFFFF)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(116), UNITY_DISPLAY_STYLE_HEX16);

}



void test_LedDriver_OutOfBoundsLedOnProducesRuntimeError(void)

{

    LedDriver_TurnOn(-1);

    UnityAssertEqualString((const char*)(("LED Driver: out-of-bounds LED")), (const char*)((RuntimeErrorStub_GetLastError())), (

   ((void *)0)

   ), (UNITY_UINT)(122));

    UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((RuntimeErrorStub_GetLastParameter())), (

   ((void *)0)

   ), (UNITY_UINT)(123), UNITY_DISPLAY_STYLE_INT);

}



void test_LedDriver_OutOfBoundsLedsAreAlwaysOff(void)

{

    if (!(LedDriver_IsLedOn(0))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(128)));};

    if (!(LedDriver_IsLedOn(17))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(129)));};

    if ((LedDriver_IsLedOff(0))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(130)));};

    if ((LedDriver_IsLedOff(17))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(131)));};

}
