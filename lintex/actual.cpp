byte oldSecond = 61;

#define RHB B00001111

void actualAlarmTime(bool isFirst) {
  uint8_t min, hor;
  Wire.beginTransmission(DS3231_ADDRESS); // 104 is DS3231 device address
  // get seconds only for debug
  Wire.write(isFirst ? 0x08 : 0x0B); // start at register 0
  Wire.endTransmission();
  Wire.requestFrom(DS3231_ADDRESS, 2);
  min = Wire.read();
  hor = Wire.read();
  print(
    hor >> 4,
    hor & RHB,
    min >> 4,
    min & RHB  
  );
  clog("Alarm %1i: %02x:%02x", (byte) isFirst, hor, min);
}

void actualClockTime() {
  uint8_t sec, min, hor;
  sec = (millis()/1000)%10;
  // exit if can't update;
  if (sec == oldSecond) {
    return;
  }
  oldSecond = sec;
  Wire.beginTransmission(DS3231_ADDRESS); // 104 is DS3231 device address
  // get seconds only for debug
  Wire.write(0x00); // start at register 0
  Wire.endTransmission();
  Wire.requestFrom(DS3231_ADDRESS, 3);
  sec = Wire.read();
  min = Wire.read();
  hor = Wire.read();
  print(
    hor >> 4,
    hor & RHB,
    min >> 4,
    min & RHB
  );
  clog("Time: %02x:%02x:%02x", hor, min, sec);
  /*
  DateTime now = RTC.now();
  digitalWrite(LATCH_PIN, LOW);
  val = (byte) now.hour();
  last = val % 10;
  top = (val - last) / 10;
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, g_digits[top]);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, g_digits[last]);
  val = (byte) now.minute();
  last = val % 10;
  top = (val - last) / 10;
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, g_digits[top]);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, g_digits[last]);
  digitalWrite(LATCH_PIN, HIGH);
  clog("%i.%02i.%02i %02i:%02i:%02i", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second()); */
}
