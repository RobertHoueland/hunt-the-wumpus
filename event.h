#ifndef EVENT_H
#define EVENT_H

#include <string>

using namespace std;

/* Abstract class, pure virtual function */
class Event{
    private:
        string percept;
    public:
        Event();
        virtual ~Event();

        virtual string get_percept() = 0; 
};

#endif