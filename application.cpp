/******************************************************
** Program: application.cpp
** Author: Robert Houeland
** Description: Plays a game of hunt the wumpus
** Input: Two command line arguments, size of cave grid, and debug mode
** Output: Game
******************************************************/

#include "application.h"

#include <stdio.h>   //getchar()
#include <stdlib.h>  //atoi

#include <cstdlib>  //rand() and srand()
#include <ctime>    //time()
#include <iostream>
#include <string>
#include <vector>

#include "play.h"
#include "room.h"

using namespace std;

int main(int argc, char *argv[]) {
    // Check for correct number of command line arguments
    if (argc < 2 || argc > 3) {
        error();
        return 1;
    }
    int size;
    string debug;
    // If only size is provided, debug mode is default false
    if (argc == 2) {
        size = atoi(argv[1]);
        debug = "false";
    } else {
        size = atoi(argv[1]);
        debug = argv[2];
    }
    // Check if command line arguments are valid
    for (int i = 0; i < debug.length(); i++) {
        debug[i] = tolower(debug[i]);
    }
    if (size < 4 || (debug != "false" && debug != "true")) {
        error();
        return 1;
    }
    srand(time(NULL));
    int play_again = 1;
    string direction;

    // Start game
    cout << string(50, '\n');
    string cont;
    gameInstructions(debug);
    getline(cin, cont);
    cout << string(50, '\n');

    Play play(size);
    while (play_again == 1 || play_again == 2) {
        if (play_again == 1) {
            play.set_cave();
            play.set_start_values();
        }
        while (play.get_is_alive() == true && play.get_win() == false) {
            if (play.alive() == false) {
                play.print_cave(debug);
                break;
            }

            play.nearby_event();
            play.print_cave(debug);
            controls();

            /* Gather input without pressing enter
             * Terminal goes in raw mode to gather input */
            system("stty raw");
            direction = getchar();
            for (int i = 0; i < direction.length(); i++) {
                direction[i] = tolower(direction[i]);
            }
            system("stty cooked");
            cout << string(50, '\n');

            // Move direction
            if (direction == "w")
                play.move_player("W");
            else if (direction == "s")
                play.move_player("S");
            else if (direction == "a")
                play.move_player("A");
            else if (direction == "d")
                play.move_player("D");
            // Shoot
            else if (direction == " ") {
                cout << string(50, '\n');
                cout << "Shooting an arrow, enter direction to fire..." << endl;

                play.print_cave(debug);
                controls();
                system("stty raw");
                direction = getchar();
                for (int i = 0; i < direction.length(); i++) {
                    direction[i] = tolower(direction[i]);
                }
                system("stty cooked");
                cout << string(50, '\n');

                // Shoot direction
                if (direction == "w")
                    play.shoot_arrow("W");
                else if (direction == "s")
                    play.shoot_arrow("S");
                else if (direction == "a")
                    play.shoot_arrow("A");
                else if (direction == "d")
                    play.shoot_arrow("D");
                else if (direction == "q") {
                    break;
                } else
                    cout << "Incorrect option. Please try again." << endl;
            } else if (direction == "q") {
                break;
            } else
                cout << "Incorrect option. Please try again." << endl;
            play.run_event();
        }

        // Game over
        cout << endl << "Do you want to play again?" << endl;
        cout << "Press 1: New cave layout" << endl;
        cout << "Press 2: Same cave layout" << endl;
        cout << "Press 0: Quit" << endl;
        cin >> play_again;

        // Restart
        if (play_again == 1) {
            cout << string(50, '\n');
            cin.clear();
            cin.ignore(100, '\n');
            play.replay();
        }
        if (play_again == 2) {
            cout << string(50, '\n');
            cin.clear();
            cin.ignore(100, '\n');
            play.reset();
        }
    }

    play.quit();
    return 0;
}