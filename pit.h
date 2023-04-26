#ifndef PIT_H
#define PIT_H

#include <string>

#include "event.h"

using namespace std;

/* Derived from event */
class Pit : public Event {
   private:
    string percept;

   public:
    Pit();

    string get_percept();
};

#endif