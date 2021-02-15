#include "room.h"
#include "event.h"
#include "wumpus.h"
#include "bats.h"
#include "pit.h"
#include "gold.h"
#include <iostream>
#include <vector>

Room::Room(){
    event_num = 0;
    player = false;
    event = NULL;
}

Room::~Room(){
	if (event == NULL)
		return;
	delete event;
	event = NULL;
}

/* Getter for event_num */
int Room::get_event_num(){
	return event_num;
}

/* Setter for event_num */
void Room::set_event_num(int num){
	event_num = num;
}

/* Getter for player */
int Room::get_player(){
	return player;
}

/* Setter for player */
void Room::set_player(bool p){
    player = p;
}

/* Setter for event */
void Room::set_event(int choice){
	if (choice == 2)
		event = new Wumpus;
	else if(choice == 3)
		event = new Gold;		
	else if(choice == 4)
		event = new Pit;	
	else if(choice == 5)
		event = new Bats;
}

/* Getter for event percept */
string Room::get_event_percept(){
    string percept = event->get_percept();
    return percept;
}

/* Deletes event */
void Room::delete_event(){
	if (event == NULL)
		return;
	delete event;
	event = NULL;
}

void Room::clear(){
	if (event != NULL){
		delete event;
		event = NULL;
	}
}