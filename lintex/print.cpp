byte leftDec(byte dec) {
  return dec / 10;
}

byte rightDec(byte dec) {
  return dec % 10;
}

uint8_t s0,s1,s2,s3;

void output(uint8_t sd0, uint8_t sd1, uint8_t sd2, uint8_t sd3) {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, sd0);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, sd1);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, sd2);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, sd3);
  digitalWrite(LATCH_PIN, HIGH);
}

void print(int8_t d0, int8_t d1, int8_t d2, int8_t d3) {
  output(
    s0 = d0 >= 0 ? g_digits[d0] : (g_digits[-d0] & g_digits[10]),
    s1 = d1 >= 0 ? g_digits[d1] : (g_digits[-d1] & g_digits[10]),
    s2 = d2 >= 0 ? g_digits[d2] : (g_digits[-d2] & g_digits[10]),
    s3 = d3 >= 0 ? g_digits[d3] : (g_digits[-d3] & g_digits[10])
  );
}

uint8_t flash = 0;
bool flashDown = true;
unsigned long flashChangeTime = 0;
#define FLASH_DELAY 280
void flashDisplay() {
  if (millis() - FLASH_DELAY < flashChangeTime) {
    return;
  }
  flashDown = !flashDown;
  if (flashDown) {
    output(s0, s1, s2, s3);
  } else {
    output(
      flash & B1000 ? g_digits[11] : s0,
      flash & B0100 ? g_digits[11] : s1,
      flash & B0010 ? g_digits[11] : s2,
      flash & B0001 ? g_digits[11] : s3
    );
  }
  flashChangeTime = millis();
}