#ifndef I2C_CLASS__
#define I2C_CLASS__

class I2C {
  byte _addr;
  byte _limit;

public:
  I2C(byte addr, byte limit) {
    _addr = addr;
    _limit = limit;
  }

  byte *read(byte start, byte length) {
    if (start + length > _limit) {
      length = _limit - start;
    }
    byte out[length];
    Wire.beginTransmission(_addr);
    Wire.write(start);
    Wire.endTransmission();
    Wire.requestFrom(_addr, length);
    for (byte i = 0; i < length; i++) {
      out[i] = Wire.read();
    }
    Wire.endTransmission();
    return out;
  }

  void write(byte start, byte length, byte *data) {
    if (start + length > _limit) {
      length = _limit - start;
    }
    Wire.beginTransmission(_addr);
    Wire.write(start);
    for (byte i = 0; i < length; i++) {
      Wire.write(data[i]);
    }
    Wire.endTransmission();
  }
};

#endif
// end
