#include "bats.h"

#include <iostream>
#include <string>

using namespace std;

Bats::Bats() {
    percept = "You hear wings flapping.";
}

string Bats::get_percept() {
    return percept;
}