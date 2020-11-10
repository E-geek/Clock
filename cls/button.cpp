#ifndef BUTTON_CLASS__
#define BUTTON_CLASS__

#include <list>
#include <iterator>

class Button : public EventTarget {
  byte _pin;
  bool _press;
  
public:
  Button(byte);
  void check() {
    bool press = HIGH == digitalRead(_pin);
    if (press == _press) {
      return;
    }
    //clog("power %i button changed: %i != %i", _pin, press, _press);
    _press = press;
    if (press) { // if old state is off
      fire(string("down"));
    } else { // if old state is on
      fire(string("up"));
      fire(string("press"));
    }
  }
};

list <Button*> buttons;

Button::Button(byte pin) {
  pinMode(pin, INPUT);
  _pin = pin;
  _press = HIGH == digitalRead(pin);
  buttons.push_back(this);
}

void checkButtons() {
  list <Button*> :: iterator it;
  for (it = buttons.begin(); it != buttons.end(); it++) { 
    (*it)->check();
  }
}

//end BUTTON_CLASS__
#endif