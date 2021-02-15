#ifndef CATALOG_H
#define CATALOG_H

#include <iostream>
#include "room.h"

using namespace std;

/*******************************************************************
   ** Function: error
   ** Description: For when command line arguments are incorrect
   ** Parameters: None
   ** Pre-Conditions: Runs with incorrect arguments to give error
   ** Post-Conditions: Outputs instructions for arguments
   *******************************************************************/
void error(){
    cout << "Invalid arguments." << endl;
    cout << "Please use size of grid cave as number for first argument.";
    cout << " (example: 5 = 5x5 grid, 4 is smallest)" << endl; 
    cout << "Second argument is debug/cheat mode, true or false." << endl;
}

/*******************************************************************
   ** Function: debug_instructions
   ** Description: Gives instructions for player if they are in cheat mode
   ** Parameters: String debug
   ** Pre-Conditions: Runs when game has started
   ** Post-Conditions: Shows player how to use debug mode
   *******************************************************************/
void debug_instructions(){
    cout << "Debug mode activated:" << endl;
    cout << "Escape rope: X" << endl;
    cout << "Wumpus: W" << endl;
    cout << "Gold: G" << endl;
    cout << "Bottomless pits: P" << endl;
    cout << "Super bats: B" << endl;
}

/*******************************************************************
   ** Function: gameInstructions
   ** Description: Gives instructions for player
   ** Parameters: None
   ** Pre-Conditions: Runs when game has started
   ** Post-Conditions: Shows player how to play
   *******************************************************************/
void gameInstructions(string debug){
    cout << "Welcome to Hunt the Wumpus! " << endl << endl;
    cout << "Your goal is to find the Wumpus creature's gold and kill it to ";
    cout << "escape." << endl;
    cout << "Each turn you can move in the cave or shoot one of your three ";
    cout << "arrows." << endl;
    cout << "There are two rooms filled with super bats that will fly you to ";
    cout << "a random room if you enter." << endl;
    cout << "There are two bottomless pits so don't fall in." << endl;
    cout << "One room has the Wumpus, who might move if he hears you." << endl;
    cout << "One room has the gold, that you can pickup, and if you ";
    cout << "return to your starting position and use the escape rope you win.";
    cout << endl;
    cout << "You will have feelings when you are adjacent to a special room.";
    cout << endl;
    cout << "You can move or fire an arrow North, South, East, or West." << endl;
    cout << "Your arrows will go three rooms unless they hit Wumpus or a wall.";
    cout << endl;
    cout << "To win, you need to shoot the Wumpus and escape with it's gold ";
    cout << "to win." << endl; 
    cout << "Watch out though, if you enter it's room, the Wumpus will eat you.";
    cout << endl << endl;
    if (debug == "true")
        debug_instructions();
    cout << endl << "Ready to play?" << endl; 
    cout << "Your player will be represented with a \"*\". Press enter to play: ";
    cout << endl;
}

void controls(){
	cout << "To move: press W to move North, A to move South, S to ";
    cout << "move West, ";
    cout << "D to move East." << endl;
    cout << "To shoot: enter a space and a direction." << endl;
}

#endif