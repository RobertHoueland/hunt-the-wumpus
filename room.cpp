#include "room.h"

#include <iostream>
#include <vector>

#include "bats.h"
#include "event.h"
#include "gold.h"
#include "pit.h"
#include "wumpus.h"

Room::Room() {
    event_num = 0;
    player = false;
    event = NULL;
}

Room::~Room() {
    if (event == NULL) return;
    delete event;
    event = NULL;
}

int Room::get_event_num() {
    return event_num;
}

void Room::set_event_num(int num) {
    event_num = num;
}

int Room::get_player() {
    return player;
}

void Room::set_player(bool p) {
    player = p;
}

void Room::set_event(int choice) {
    if (choice == 2)
        event = new Wumpus;
    else if (choice == 3)
        event = new Gold;
    else if (choice == 4)
        event = new Pit;
    else if (choice == 5)
        event = new Bats;
}

string Room::get_event_percept() {
    string percept = event->get_percept();
    return percept;
}

void Room::delete_event() {
    if (event == NULL) return;
    delete event;
    event = NULL;
}

void Room::clear() {
    if (event != NULL) {
        delete event;
        event = NULL;
    }
}