#ifndef WUMPUS_H
#define WUMPUS_H

#include <string>

#include "event.h"

using namespace std;

class Wumpus : public Event {
   private:
    string percept;

   public:
    Wumpus();

    string get_percept();
};

#endif