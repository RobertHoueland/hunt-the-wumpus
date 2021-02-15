#include "pit.h"
#include <string>

using namespace std;

Pit::Pit(){
    percept = "You feel a breeze.";
}

/* Getter for percept */
string Pit::get_percept(){
    return percept;
}