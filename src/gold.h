#ifndef GOLD_H
#define GOLD_H

#include <string>

#include "event.h"

using namespace std;

/* Derived from event */
class Gold : public Event {
   private:
    string percept;

   public:
    Gold();

    string get_percept();
};

#endif