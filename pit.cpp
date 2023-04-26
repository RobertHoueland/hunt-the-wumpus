#include "pit.h"

#include <string>

using namespace std;

Pit::Pit() {
    percept = "You feel a breeze.";
}

string Pit::get_percept() {
    return percept;
}