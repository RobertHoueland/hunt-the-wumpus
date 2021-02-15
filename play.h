#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
#include <string>

#include "room.h"
#include "event.h"
#include "wumpus.h"

using namespace std;

class Play{
	private:
		int cavesize;
		vector<vector<Room> > cave;
		int playerx;
        int playery;
		int startx;
        int starty;
		int arrowx;
        int arrowy; 
		int arrows;
		int wumpusx;
        int wumpusy;
		int start_wumpusx;
        int start_wumpusy;
		bool wumpus_killed;
		bool gold_retrieved;
		bool is_alive;
		bool win;
	public:
        Play();
		Play(int);

        bool get_is_alive();
		bool get_win();

		void nearby_event(); 
		void print_cave(string);
		void set_cave(); 
		void set_start_values();
		void move_player(string); 
		void shoot_arrow(string);
		void run_event(); 
		bool alive();
		void reset();
		void replay();
		void quit();
};

#endif