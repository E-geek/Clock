#include <EEPROM.h>

#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>

/*
********************************************************************
  Name    : shiftOutDisplay, Test code
  Author  : Benjo Charlie
  Date    : 13 Sept, 2013
  Version : 1.0
  Notes   : Shiftbit registers can be a little tricky to setup so I
          : designed this simple Hello World code for doing just that.
          : This example uses a 74HC595 Shift Bit Register in conjunction
          : with a common anode seven segment display.
          : This code sends the following values to a Shift Bit Register:
          : 1, 2, 4, 8, 16, 32, 64, 128.
          : Each of the 74HC595 outputs will "switch on" in turn.
********************************************************************

7 Segment (Common Anode) Display Map: (This can be altered to reflect your HW)

    D   E  5V   F   G
 ___|___|___|___|___|____
|                        |
|        F               |
|    E       G           |
|        D               |
|    A       C           |
|        B       H(Dot)  |
|________________________|
    |   |   |   |   |
    A   B  5V   C   H

74HC595 Map:
           _______
   OUT Q1-|1 *  16|-5V
   OUT Q2-|2    15|-OUT Q0
   OUT Q3-|3    14|-ARD PIN 11
   OUT Q4-|4    13|-GND
   OUT Q5-|5    12|-ARD PIN 8 ; 1uF TO GND
   OUT Q6-|6    11|-ARD PIN 12
   OUT Q7-|7    10|-5V
      GND-|8_____9|-

********************************************************************
*/
#define DEBUG

#include <Wire.h>

#define DS3231_ADDRESS 0x68

//Pin connected to ST_CP of 74HC595
#define LATCH_PIN 2
//Pin connected to SH_CP of 74HC595
#define CLOCK_PIN 7
//Pin connected to DS of 74HC595
#define DATA_PIN 4

#define BTN_ENTER 11
#define BTN_CHANGE 10
#define BTN_SHIFT 9
#define BTN_NEXT 8

#include "./cls/clog.cpp"
#include "./cls/event-target.cpp"
#include "./cls/button.cpp"
#include "./cls/i2c.cpp"
#include "./cls/display.cpp"
Display *display;
I2C *i2c;
#include "./cls/alarm.cpp"
#include "./cls/light-mode.cpp"
#include "./router/state.cpp"
State *state;
//# include "./router/logic.cpp"

Button *btnEnter;
Button *btnNext;
Button *btnChange;
Button *btnShift;

void setup() {
  //set pins to output so you can control the shift register]
  Wire.begin();
  i2c = new I2C(DS3231_ADDRESS, 14);
  display = new Display(LATCH_PIN, CLOCK_PIN, DATA_PIN);
  state = new State();
  Serial.begin(57600);
  clog("Base init");
  btnNext = new Button(BTN_NEXT);
  btnEnter = new Button(BTN_ENTER);
  btnChange = new Button(BTN_CHANGE);
  btnShift = new Button(BTN_SHIFT);
  // bind
  /*
  btnNext->on("press", onNext);
  btnEnter->on("press", onEnter);
  btnChange->on("down", onChangeDown)->on("press", onChangePress);
  btnShift->on("down", onShiftDown)->on("press", onShiftPress);
  */
  clog("Bind done");
}

void loop() {
  checkButtons();
}
