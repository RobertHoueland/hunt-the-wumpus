#ifndef BATS_H
#define BATS_H

#include "event.h"
#include <string>

using namespace std;

/* Derived from event */
class Bats : public Event{
    private:
        string percept;
    public:
        Bats();
        
        string get_percept();  
};

#endif