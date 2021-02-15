#ifndef WUMPUS_H
#define WUMPUS_H

#include "event.h"
#include <string>

using namespace std;

/* Derived from event */
class Wumpus : public Event{
    private:
        string percept;
    public:
        Wumpus();

        string get_percept(); 
};

#endif