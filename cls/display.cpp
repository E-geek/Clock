#ifndef DISPLAY_CLASS__
#define DISPLAY_CLASS__

#define DISPLAY_EMPTY 0xff
#define DISPLAY_DOT 127
#define DISPLAY_SEGMENT_DOTTED 128
#define DISPLAY_BLINK_TIME 280
#define dot(input) (input|DISPLAY_SEGMENT_DOTTED)
#define undot(input) (input|127)

class Display {
  byte _latch;
  byte _sqware;
  byte _data;
  byte _font[18] = {
    0x88, // 0
    0xbb, // 1
    0x94, // 2
    0x91, // 3
    0xa3, // 4|ч
    0xc1, // 5
    0xc0, // 6
    0x9b, // 7
    0x80, // 8|в
    0x81, // 9
    0x7f, // .      // 10
    0xff,  // null  // 11
    B11000000, // Б // 12
    B10100010, // Н // 13
    B10001010, // П // 14
    B10000110, // Р // 15
    B11001100, // С // 16
    B11100100  // Т // 17
  };
  byte _weekDay0[7] = {14, 8,16, 4,14,16, 8};
  byte _weekDay1[7] = {13,17,15,17,17,12,16};
  unsigned long int _lastBlinkSwap;
  bool _blinkHideOn;

  byte char2sym(byte ch) {
    return (ch & DISPLAY_SEGMENT_DOTTED) ? (_font[undot(ch)] & DISPLAY_DOT) : _font[ch];
  }

public:
  byte currentState[4];
  byte blinkMask = 0;

  Display(byte latch, byte sqware, byte data) {
    _latch = latch;
    _sqware = sqware;
    _data = data;
    _lastBlinkSwap = 0;
    _blinkHideOn = false;
    pinMode(latch, OUTPUT);
    pinMode(sqware, OUTPUT);
    pinMode(data, OUTPUT);
  }

  void show(byte *state) {
    digitalWrite(_latch, LOW);
    for (byte i = 0; i < 4; i++) {
      shiftOut(_data, _sqware, MSBFIRST, state[i]);
    }
    digitalWrite(_latch, HIGH);
  }

  void show() {
    show(currentState);
  }

  void print(byte d0, byte d1, byte d2, byte d3) {
    currentState[0] = char2sym(d0);
    currentState[1] = char2sym(d1);
    currentState[2] = char2sym(d2);
    currentState[3] = char2sym(d3);
    show();
  }

  void blink() {
    unsigned long ms = millis();
    if (_lastBlinkSwap > ms) {
      _lastBlinkSwap = ms;
    }
    if (blinkMask == 0 || (ms - DISPLAY_BLINK_TIME < _lastBlinkSwap)) {
      return;
    }
    _blinkHideOn = !_blinkHideOn;
    if (_blinkHideOn) {
      byte tmp[4] = {
        (blinkMask & B1000) ? DISPLAY_EMPTY : currentState[0],
        (blinkMask & B0100) ? DISPLAY_EMPTY : currentState[1],
        (blinkMask & B0010) ? DISPLAY_EMPTY : currentState[2],
        (blinkMask & B0001) ? DISPLAY_EMPTY : currentState[3]
      };
      show(tmp);
    } else {
      show();
    }
    _lastBlinkSwap = ms;
  }

  byte weekDay2Char(byte d, byte index) {
    if (!index) { // 0
      return _weekDay0[d];
    } else { // 1
      return _weekDay1[d];
    }
  }
  
  byte leftDec(byte dec) {
    return dec / 10;
  }

  byte rightDec(byte dec) {
    return dec % 10;
  }
};

#endif
