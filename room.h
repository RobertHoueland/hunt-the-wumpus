#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include "event.h"

using namespace std;

class Room{
    private:
        int event_num;
        bool player;
        Event* event;
    public:
        Room();
        ~Room();

        int get_event_num();
		void set_event_num(int num);
        int get_player();
		void set_player(bool);
        void set_event(int);
        string get_event_percept();
        void delete_event();
        void clear();
};

#endif