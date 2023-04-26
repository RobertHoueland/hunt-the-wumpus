#include "play.h"

#include <cstdlib>  //rand() and srand()
#include <iostream>
#include <string>
#include <vector>

#include "event.h"
#include "room.h"
#include "wumpus.h"

using namespace std;

Play::Play() {}

// Default constructor with size to initialize variables
Play::Play(int size) {
    cavesize = size;
    playerx = 0, playery = 0;
    startx = 0, starty = 0;
    arrowx = 0, arrowy = 0;
    arrows = 3;
    wumpusx = 0, wumpusy = 0;
    start_wumpusx = 0, start_wumpusy = 0;
    wumpus_killed = false;
    gold_retrieved = false;
    is_alive = true;
    win = false;

    // Create cave
    for (int i = 0; i < cavesize; i++)
        this->cave.push_back(vector<Room>(cavesize));
}

bool Play::get_is_alive() {
    return is_alive;
}

bool Play::get_win() {
    return win;
}

/*******************************************************************
 ** Function: nearby_event
 ** Description: Prints if event is nearby
 ** Parameters: None
 ** Pre-Conditions: Near event
 ** Post-Conditions: Event is printed
 *******************************************************************/
void Play::nearby_event() {
    // Checks each direction for nearby event, and prints percept if so
    if (playery + 1 < cavesize &&
        cave[playery + 1][playerx].get_event_num() > 1) {
        if (cave[playery + 1][playerx].get_event_num() != 3 ||
            gold_retrieved == false)
            cout << cave[playery + 1][playerx].get_event_percept() << endl;
    }
    if (playerx + 1 < cavesize &&
        cave[playery][playerx + 1].get_event_num() > 1) {
        if (cave[playery][playerx + 1].get_event_num() != 3 ||
            gold_retrieved == false)
            cout << cave[playery][playerx + 1].get_event_percept() << endl;
    }
    if (playerx - 1 >= 0 && cave[playery][playerx - 1].get_event_num() > 1) {
        if (cave[playery][playerx - 1].get_event_num() != 3 ||
            gold_retrieved == false)
            cout << cave[playery][playerx - 1].get_event_percept() << endl;
    }
    if (playery - 1 >= 0 && cave[playery - 1][playerx].get_event_num() > 1) {
        if (cave[playery - 1][playerx].get_event_num() != 3 ||
            gold_retrieved == false)
            cout << cave[playery - 1][playerx].get_event_percept() << endl;
    }
}

/*******************************************************************
 ** Function: print_cave
 ** Description: Prints cave
 ** Parameters: None
 ** Pre-Conditions: Cave is ready to print
 ** Post-Conditions: User sees cave
 *******************************************************************/
void Play::print_cave(string debug) {
    for (int i = 0; i < cavesize; i++) {
        for (int j = 0; j < cavesize; j++) cout << "+---";
        cout << "+" << endl;
        for (int j = 0; j < cavesize; j++) {
            cout << "| ";
            if (cave[i][j].get_player() == 1) cout << "* ";

            // Prints events if in debug mod
            if (i == starty && j == startx && debug == "true" &&
                cave[i][j].get_player() == 0)
                cout << "X ";
            else if (cave[i][j].get_event_num() == 2 && debug == "true" &&
                     wumpus_killed == false && cave[i][j].get_player() == 0)
                cout << "W ";
            else if (cave[i][j].get_event_num() == 3 && debug == "true" &&
                     gold_retrieved == false && cave[i][j].get_player() == 0)
                cout << "G ";
            else if (cave[i][j].get_event_num() == 4 && debug == "true" &&
                     cave[i][j].get_player() == 0)
                cout << "P ";
            else if (cave[i][j].get_event_num() == 5 && debug == "true" &&
                     cave[i][j].get_player() == 0)
                cout << "B ";
            else if (cave[i][j].get_player() == 0 &&
                     (cave[i][j].get_event_num() < 2 ||
                      cave[i][j].get_event_num() > 5) &&
                     debug == "true")
                cout << "  ";
            else if (cave[i][j].get_player() == 0 && debug == "false")
                cout << "  ";
            else if (cave[i][j].get_player() == 0 && debug == "true" &&
                     gold_retrieved == true)
                cout << "  ";
        }

        cout << "|";
        cout << endl;
    }

    for (int i = 0; i < cavesize; i++) cout << "+---";
    cout << "+" << endl;
}

/*******************************************************************
 ** Function: set_cave
 ** Description: Sets cave with events randomly
 ** Parameters: None
 ** Pre-Conditions: Cave has been created
 ** Post-Conditions: Sets cave events
 *******************************************************************/
void Play::set_cave() {
    // Random x and y
    int randx1, randy1;
    int randx4, randy4;
    int randx5, randy5;
    bool placed1 = false, placed2 = false, placed3 = false;

    // Sets starting positions at 0 so you don't start on an event
    for (int i = 0; i < cavesize; i++) {
        for (int j = 0; j < cavesize; j++) cave[i][j].set_event_num(0);
    }

    // Sets escape rope starting position
    while (placed1 == false) {
        randx1 = rand() % cavesize;
        randy1 = rand() % cavesize;

        if (cave[randy1][randx1].get_event_num() == 0) {
            cave[randy1][randx1].set_event_num(1);
            placed1 = true;
        }
    }

    // Sets Wumpus starting position
    while (placed2 == false) {
        randx4 = rand() % cavesize;
        randy4 = rand() % cavesize;

        if (randx4 == randx1 && randy4 == randy1)
            placed2 = false;
        else if (cave[randy4][randx4].get_event_num() == 0) {
            cave[randy4][randx4].set_event_num(2);
            placed2 = true;
        }
    }
    // Sets gold starting position
    while (placed3 == false) {
        randx5 = rand() % cavesize;
        randy5 = rand() % cavesize;

        if ((randx5 == randx1 && randy5 == randy1) ||
            (randx5 == randx4 && randy5 == randy4))
            placed3 = false;
        else if (cave[randy5][randx5].get_event_num() == 0) {
            cave[randy5][randx5].set_event_num(3);
            placed3 = true;
        }
    }

    int randx2, randy2;
    // Sets two bottomless pits
    for (int i = 0; i < 2; i++) {
        bool placed = false;
        while (placed == false) {
            randx2 = rand() % cavesize;
            randy2 = rand() % cavesize;

            if ((randx2 == randx1 && randy2 == randy1) ||
                (randx2 == randx4 && randy2 == randy4) ||
                (randx2 == randx5 && randy2 == randy5))
                placed = false;
            else if (cave[randy2][randx2].get_event_num() == 0) {
                cave[randy2][randx2].set_event_num(4);
                placed = true;
            }
        }
    }

    int randx3, randy3;
    // Sets two bats
    for (int i = 0; i < 2; i++) {
        bool placed = false;
        while (placed == false) {
            randx3 = rand() % cavesize;
            randy3 = rand() % cavesize;

            if ((randx3 == randx2 && randy3 == randy2) ||
                (randx3 == randx1 && randy3 == randy1) ||
                (randx3 == randx4 && randy3 == randy4) ||
                (randx3 == randx5 && randy3 == randy5))
                placed = false;
            else if (cave[randy3][randx3].get_event_num() == 0) {
                cave[randy3][randx3].set_event_num(5);
                placed = true;
            }
        }
    }
}

/*******************************************************************
 ** Function: set_start_values
 ** Description: Sets cave with start values
 ** Parameters: None
 ** Pre-Conditions: Cave has been created and has events
 ** Post-Conditions: Sets locations of start values
 *******************************************************************/
void Play::set_start_values() {
    for (int i = 0; i < cavesize; i++) {
        for (int j = 0; j < cavesize; j++) {
            // Escape rope
            if (cave[i][j].get_event_num() == 1) {
                startx = i;
                starty = j;
                playerx = i;
                playery = j;
                cave[playery][playerx].set_player(true);
            }
            // Wumpus
            else if (cave[i][j].get_event_num() == 2) {
                cave[i][j].set_event(2);
                wumpusy = i;
                wumpusx = j;
                start_wumpusy = i;
                start_wumpusx = j;
            }
            // Gold
            else if (cave[i][j].get_event_num() == 3)
                cave[i][j].set_event(3);
            // Bottomless pit
            else if (cave[i][j].get_event_num() == 4)
                cave[i][j].set_event(4);
            // Bat
            else if (cave[i][j].get_event_num() == 5)
                cave[i][j].set_event(5);
            // Empty room
            else
                cave[i][j].set_event(0);
        }
    }
}

/*******************************************************************
 ** Function: move_player
 ** Description: Moves player up down left or right
 ** Parameters: String direction
 ** Pre-Conditions: Choice for which way to move
 ** Post-Conditions: Move user
 *******************************************************************/
void Play::move_player(string direction) {
    // North
    if (direction == "W" && (playery - 1) >= 0) {
        cave[playery][playerx].set_player(false);
        playery = playery - 1;
        cave[playery][playerx].set_player(true);
    }
    // South
    else if (direction == "S" && (playery + 1) < cavesize) {
        cave[playery][playerx].set_player(false);
        playery = playery + 1;
        cave[playery][playerx].set_player(true);
    }
    // West
    else if (direction == "A" && (playerx - 1) >= 0) {
        cave[playery][playerx].set_player(false);
        playerx = playerx - 1;
        cave[playery][playerx].set_player(true);
    }
    // East
    else if (direction == "D" && (playerx + 1) < cavesize) {
        cave[playery][playerx].set_player(false);
        playerx = playerx + 1;
        cave[playery][playerx].set_player(true);
    } else
        cout << "Error. Cannot move here. Please retry." << endl;
}

/*******************************************************************
 ** Function: shoot_arrow
 ** Description: Shoot arrow in direction
 ** Parameters: String direction
 ** Pre-Conditions: Player can shoot
 ** Post-Conditions: Shoots arrow 3 rooms away
 *******************************************************************/
void Play::shoot_arrow(string direction) {
    if (arrows < 1) {
        cout << "You have no arrows remaining." << endl;
        return;
    }

    arrows--;
    arrowx = playerx;
    arrowy = playery;

    for (int i = 0; i < 3; i++) {
        // North
        if (direction == "W" && (arrowy - 1) >= 0 && wumpus_killed == false) {
            cout << "Arrow fired North through a room." << endl;
            arrowy = arrowy - 1;
        }
        // South
        else if (direction == "S" && (arrowy + 1) < cavesize &&
                 wumpus_killed == false) {
            cout << "Arrow fired South through a room." << endl;
            arrowy = arrowy + 1;
        }
        // West
        else if (direction == "A" && (arrowx - 1) >= 0 &&
                 wumpus_killed == false) {
            cout << "Arrow fired West through a room." << endl;
            arrowx = arrowx - 1;
        }
        // East
        else if (direction == "D" && (arrowx + 1) < cavesize &&
                 wumpus_killed == false) {
            cout << "Arrow fired East through a room." << endl;
            arrowx = arrowx + 1;
        } else {
            cout << "Arrow has hit a wall." << endl;
            break;
        }
        if (arrowy == wumpusy && arrowx == wumpusx) {
            cout << "You have shot and killed the Wumpus!" << endl;
            if (gold_retrieved == true) {
                cout << "Return to your starting room and use the escape ";
                cout << "rope to win!" << endl;
            }
            if (gold_retrieved == false)
                cout << "Find and collect the gold now!" << endl;
            cave[wumpusy][wumpusx].set_event_num(0);
            wumpus_killed = true;
            return;
        }
    }

    cout << "Your arrow shot and hit nothing." << endl;
    cout << "Arrows remaining: " << arrows << endl;
    if (wumpus_killed == false) {
        // Move Wumpus on arrow fire 75% of the time
        int move = rand() % 4;
        if (move < 3) {
            cout << "The Wumpus was awoken by your arrow and moved rooms!";
            cout << endl;
            bool wumpus_set;
            cave[wumpusy][wumpusx].set_event_num(0);
            while (wumpus_set == false) {
                wumpusx = rand() % cavesize;
                wumpusy = rand() % cavesize;
                if (cave[wumpusy][wumpusx].get_event_num() == 0) {
                    cave[wumpusy][wumpusx].set_event(2);
                    cave[wumpusy][wumpusx].set_event_num(2);
                    wumpus_set = true;
                }
            }
        }
    }
}

/*******************************************************************
 ** Function: run_event
 ** Description: Runs event
 ** Parameters: None
 ** Pre-Conditions: Runs when user enters room with event
 ** Post-Conditions: Shows user what happened
 *******************************************************************/
void Play::run_event() {
    if (cave[playerx][playery].get_event_num() == 1) {
        cout << "You have returned to the escape rope." << endl;
        if (gold_retrieved == true && wumpus_killed == true) {
            cout << "You have won the game!" << endl;
            win = true;
        }
    } else if (cave[playery][playerx].get_event_num() == 2) {
        cout << "Oh no, you encountered the Wumpus! He has eaten you!" << endl;
        is_alive = false;
        return;
    } else if (cave[playery][playerx].get_event_num() == 3) {
        gold_retrieved = true;
        return;
    } else if (cave[playery][playerx].get_event_num() == 4) {
        cout << "You have fallen into a bottomless pit and died!" << endl;
        is_alive = false;
        return;
    } else if (cave[playery][playerx].get_event_num() == 5) {
        cave[playery][playerx].set_player(false);
        cout << "Super bats have carried you away to a random room!" << endl;
        int pos1 = rand() % cavesize;
        int pos2 = rand() % cavesize;
        playerx = pos1;
        playery = pos2;
        cave[playery][playerx].set_player(true);
        return;
    }
}

/*******************************************************************
 ** Function: alive
 ** Description: Finds if player is alive
 ** Parameters: None
 ** Pre-Conditions: Runs throughout program
 ** Post-Conditions: Checks if user is dead
 *******************************************************************/
bool Play::alive() {
    if (arrows <= 0) cout << "You've run out of arrows!" << endl;
    if (cave[playerx][playery].get_event_num() == 1) {
        if (gold_retrieved == true && wumpus_killed == true) {
            win = true;
            cout << "You have won the game!" << endl;
            return false;
        }
    } else if (cave[playery][playerx].get_event_num() == 2) {
        cout << "You have found the Wumpus! He has eaten you!" << endl;
        is_alive = false;
        return false;
    } else if (cave[playery][playerx].get_event_num() == 3 &&
               wumpus_killed == false) {
        cout << "You have found the gold! Find and kill the Wumpus now!"
             << endl;
        gold_retrieved = true;
        return true;
    } else if (cave[playery][playerx].get_event_num() == 3 &&
               wumpus_killed == true) {
        cout << "You have found the gold! Return to your starting room and ";
        cout << "use the escape rope to win!" << endl;
        gold_retrieved = true;
        return true;
    } else if (cave[playery][playerx].get_event_num() == 4) {
        cout << "You have fallen into a bottomless pit and died!" << endl;
        is_alive = false;
        return false;
    }
    return true;
}

/*******************************************************************
 ** Function: reset
 ** Description: Resets game with same cave layout
 ** Parameters: None
 ** Pre-Conditions: Game has ended, user wants to restart
 ** Post-Conditions: Keeps layout the same
 *******************************************************************/
void Play::reset() {
    // Restart game and variables with same cave layout
    cave[playery][playerx].set_player(false);
    playerx = startx;
    playery = starty;
    cave[playery][playerx].set_player(true);
    if (wumpus_killed == false) {
        cave[wumpusy][wumpusx].delete_event();
        cave[wumpusy][wumpusx].set_event_num(0);
    }
    wumpusx = start_wumpusx;
    wumpusy = start_wumpusy;
    cave[wumpusy][wumpusx].set_event(2);
    cave[wumpusy][wumpusx].set_event_num(2);
    gold_retrieved = false;
    is_alive = true;
    win = false;
    wumpus_killed = false;
    arrows = 3;
    cave.clear();
}

/*******************************************************************
 ** Function: replay
 ** Description: Resets game with new cave layout
 ** Parameters: None
 ** Pre-Conditions: Game has ended, user wants to restart
 ** Post-Conditions: Gives new layout
 *******************************************************************/
void Play::replay() {
    // Restart game and variables with new cave layout
    cave.clear();
    cave[playery][playerx].set_player(false);
    gold_retrieved = false;
    is_alive = true;
    win = false;
    wumpus_killed = false;
    arrows = 3;
}

/*******************************************************************
 ** Function: quit
 ** Description: Frees dynamic memory
 ** Parameters: None
 ** Pre-Conditions: Game has ended, program ending
 ** Post-Conditions: Memory is deleted
 *******************************************************************/
void Play::quit() {
    for (int i = 0; i < cavesize; i++) {
        for (int j = 0; j < cavesize; j++) cave[i][j].delete_event();
    }
}