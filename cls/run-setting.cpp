#ifndef RUN_SETTING_CLASS__
#define RUN_SETTING_CLASS__

#define RUN_SETTING_LIGHT 1
#define RUN_SETTING_SOUND 2

class RunSetting {
  byte _reg;

public:
  byte mode; // B01 - light, B10 - sound
  byte lightIndex; // 0-24
  byte sound; // 0xff is random

  /*
   * @reg EEPROM index for read two byte
   */
  RunSetting(byte reg) {
    byte s0;
    _reg = reg;
    s0 = EEPROM.read(reg);
    sound = EEPROM.read(reg + 1);
    mode = s0 & B11;
    lightIndex = s0 >> 2;
  }

  void save() {
    EEPROM.update(_reg, (lightIndex << 2) | mode);
    EEPROM.update(_reg + 1, sound);
  }

  void off() {
    mode = 0;
  }

  void lightOn() {
    mode = mode | RUN_SETTING_LIGHT;
  }

  void lightOff() {
    mode = mode & RUN_SETTING_SOUND;
  }

  void soundOn() {
    mode = mode | RUN_SETTING_SOUND;
  }

  void soundOff() {
    mode = mode & RUN_SETTING_LIGHT;
  }
};

#endif
