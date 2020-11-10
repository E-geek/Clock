// lvl0 0 - часы, 1 - буд1, 2 - буд2
// lvl1 0 - none, 1-... - value
int8_t lvl0, lvl1;

bool shift, change;
byte flash;

void save() {
  lvl0 = lvl1 = 0;
}

void onNext(Event*) {
  clog("next press");
  if(lvl1 > 0) {
    if(lvl0 == 0) {
      if(++lvl1 == 4) {
        save();
        return;
      }
      if(lvl1 == 2) {
        flash = B1100;
      } else if (lvl1 == 3) {
        flash = B0011;
      } else {
        uint8_t d = i2c->read(0x03, 1)[0];
        display->print(
          display->weekDay2Char(d, 0),
          display->weekDay2Char(d, 1),
          DISPLAY_EMPTY,
          DISPLAY_EMPTY
        );
        flash = B1100;
      }
      return;
    }
  }
  if(++lvl0 == 3) {
    lvl0 = 0;
    return;
  }
  //actualAlarmTime(lvl0 == 1);
};

void onEnter(Event* e) {
  clog("enter press");
  if(lvl1++ == 0) {
    onNext(e);
    return;
  }
};

void onChangeDown() {
  clog("change down");
  change = true;
}

void onChangePress() {
  clog("change press");
  change = false;
}

void onShiftDown(Event*) {
  clog("shift down");
  if ((lvl0 | lvl1) == 0) {
    if (change) {
      printRTCState();
      return;
    }
    // print day week and temp
    lvl1 = -1;
    uint8_t d = i2c->read(0x03, 1)[0];
    uint8_t t = i2c->read(0x11, 1)[0];
    display->print(
      display->weekDay2Char(d, 0),
      dot(display->weekDay2Char(d, 1)),
      display->leftDec(t),
      display->rightDec(t)
    );
    return;
  }
};

void onShiftPress(Event*) {
  clog("shift press");
  if (lvl0 == 0 && lvl1 == -1) {
    lvl1 = 0;
    return;
  }
}
