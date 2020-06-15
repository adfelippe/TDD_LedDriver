#include "build/temp/_test_LedDriver.c"
#include "src/LedDriver.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"




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

 UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

((void *)0)

), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_HEX16);

}



void test_LedDriver_TurnOnLedOne(void)

{

    LedDriver_TurnOn(1);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((1)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(26), UNITY_DISPLAY_STYLE_HEX16);

}



void test_LedDriver_TurnOffLedOne(void)

{

    LedDriver_TurnOff(1);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_HEX16);

}



void test_LedDriver_TurnOnMultipleLeds(void)

{

    LedDriver_TurnOn(9);

    LedDriver_TurnOn(8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x180)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_HEX16);

}



void test_LedDriver_TurnAllOn(void)

{

    LedDriver_TurnAllOn();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xFFFF)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(45), UNITY_DISPLAY_STYLE_HEX16);

}



void test_LedDriver_LedTurnOffAnyLed(void)

{

    LedDriver_TurnAllOn();

    LedDriver_TurnOff(8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xFF7F)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(52), UNITY_DISPLAY_STYLE_HEX16);

}



void test_LedDriver_LedMemoryIsNotReadable(void)

{

    virtualLeds = 0xFFFF;

    LedDriver_TurnOn(8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x80)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

   ((void *)0)

   ), (UNITY_UINT)(59), UNITY_DISPLAY_STYLE_HEX16);

}
