#include "gold.h"

#include <string>

using namespace std;

Gold::Gold() {
    percept = "You see a glimmer nearby.";
}

string Gold::get_percept() {
    return percept;
}