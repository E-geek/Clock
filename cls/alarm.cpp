#ifndef ALARM_CLASS__
#define ALARM_CLASS__

#include "./run-setting.cpp"

#define RHB B00001111

class Alarm {
  byte _reg;
  byte _RTCStart;

public:
  byte hour;
  byte minute;
  byte state;
  byte digit[4];
  RunSetting *runSettings[8];

  Alarm(byte reg, byte RTCStart) {
    _reg = reg;
    _RTCStart = RTCStart;
    state = EEPROM.read(reg);
    for (byte i = 1; i < 9; i++) {
      runSettings[i - 1] = new RunSetting(reg + i * 2);
    }
    byte *data;
    data = i2c->read(RTCStart, 2);
    digit[0] = data[1] >> 4;
    digit[1] = data[1] & RHB;
    digit[2] = data[0] >> 4;
    digit[3] = data[0] & RHB;
    hour = digit[0] * 10 + digit[1];
    minute = digit[2] * 10 + digit[3];
  }
};

#endif
