#ifndef STATE_CLASS__
#define STATE_CLASS__

#define MINUTES_PER_DAY 1440

class State {
  byte _oldSecond;
public:
  byte lvl0;
  byte lvl1;
  Alarm *alarm0; // 18 byte + 10 zapas EEPROM
  Alarm *alarm1; // 18 byte + 10 zapas EEPROM
  LightMode *lightModes[24]; // 3 * 24 = 72 byte + 1b per mode zapas EEPROM

  State() {
    alarm0 = new Alarm(0, 0x08);
    alarm1 = new Alarm(28, 0x0B); // maybe lost data
    for (byte i = 0; i < 24; i++) {
      lightModes[i] = new LightMode(56 + i * 4);
    }
    _oldSecond = 61;
    lvl0 = 0;
    lvl1 = 0;
  }
};

#endif
