#ifndef EVENT_TARGET_CLASS__
#define EVENT_TARGET_CLASS__

#include <map>
#include <string>

using namespace std;

class Event {
  public:
    string name;
    unsigned long time;
    Event(string _name) {
      time = millis();
      name = _name;
    }
}; // end class

typedef void listenerFunction(Event*);
typedef std::map<string, listenerFunction*> listeners;

class EventTarget {
    listeners _map;
  public:
    EventTarget* on(string name, listenerFunction *handler) {
      //clog("bind on %s", name.c_str());
      _map[name] = handler;
      return this;
    }
    EventTarget* fire(string name) {
      listenerFunction *handler = _map[name];
      //clog("fire called %s", name.c_str());
      if (handler == nullptr) {
	      return this;
      }
      Event *event = new Event(name);
      handler(event);
      return this;
    }
    void check() {
      return;
    }
  
}; // end class

// end EVENT_TARGET_CLASS__
#endif
