#ifndef LIGHT_MODE_CLASS__
#define LIGHT_MODE_CLASS__

#include <math.h>

class LightMode {
  byte _reg;

public:
  byte time;
  byte level;
  byte warmness;

  LightMode(byte reg) {
    _reg = reg;
    time = EEPROM.read(reg);
    level = EEPROM.read(reg+1);
    warmness = EEPROM.read(reg+2);
  }

  void save() {
    EEPROM.update(_reg, time);
    EEPROM.update(_reg+1, level);
    EEPROM.update(_reg+2, warmness);
  }

  /*
   * @param T current time seconds
   * @param Tmax length of sunrise in seconds
   */
  byte *getLevels(int T, int Tmax) {
    clog('start getLevels: %i', millis()%1000);
    double kT = Tmax / (sqrt(level) + sqrt(warmness * level / 510));
    double Tc0 = Tmax - kT * sqrt(level);
    double Tm = Tmax - Tc0;
    double Tw0 = Tc0 / 2;
    byte levels[3] = {0, 0, 0};
    double lrm = warmness * level / 510;
    int test = round(lrm / 255 * pow( sqrt(lrm) * (Tc0 - abs(T - round(Tc0))) / Tc0 , 2 ));
    if (test > 0) {
      levels[0] = test;
    }
    if (T > Tw0) {
      test = round(level / 255 * pow(sqrt((T - Tw0) / Tm), 2));
      levels[1] = test < 256 ? test : 255;
    }
    if (T > Tc0) {
      test = round(level / 255 * pow(sqrt((T - Tc0) / Tm), 2));
      levels[2] = test < 256 ? test : 255;
    }
    clog('end getLevels: %i', millis()%1000);
    clog("T < %i\nTmax < %i\nkT  > %s\nTc0 > %i\nlrm > %s",
      T, Tmax, String(kT).c_str(), round(Tc0 * 10), String(lrm).c_str()
    );
    clog("[%i,%i,%i]", levels[0], levels[1], levels[2]);
    return levels;
  }
};

#endif
