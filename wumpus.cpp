#include "wumpus.h"
#include <iostream>
#include <string>

using namespace std;

Wumpus::Wumpus(){
    percept = "You smell a terrible stench.";
}

/* Getter for percept */
string Wumpus::get_percept(){
    return percept;
}