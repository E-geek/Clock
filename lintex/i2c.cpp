
uint8_t read_i2c_register(uint8_t addr, uint8_t reg) {
  Wire.beginTransmission(addr);
  Wire.write((byte)reg);
  Wire.endTransmission();
  Wire.requestFrom(addr, (byte)1);
  return Wire.read();
}

uint8_t read_i2c_register(uint8_t reg) {
  return read_i2c_register(DS3231_ADDRESS, reg);
}

void write_i2c_register(uint8_t addr, uint8_t reg, uint8_t val) {
  Wire.beginTransmission(addr);
  Wire.write((byte)reg);
  Wire.write((byte)val);
  Wire.endTransmission();
}

void write_i2c_register(uint8_t reg, uint8_t val) {
  return write_i2c_register(DS3231_ADDRESS, reg, val);
}