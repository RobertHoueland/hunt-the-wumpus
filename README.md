# hunt-the-wumpus

Works with polymorphism and STL template classes. The player is an adventurer trying to kill the Wumpus, find the pot of gold, and escape. The Wumpus lives in a cave grid, with rooms and tunnels connecting them in North, East, West, South directions. The adventurer starts in an empty room, which is also where the escape rope is. Each room can be empty, or can have an event: two hazards, the gold, or the Wumpus. 

**Each Turn:**

The player presses W, A, S, D to move through a room OR fires an arrow.

Firing an arrow: Press space, and the direction. Adventurer starts with three arrows, and travels up to three rooms. This can kill the Wumpus, but if the player runs out of arrows and haven't killed it, they lose. 

**Wumpus:** 

The Wumpus is asleep until awoken by an arrow going by and missing him. If the player enters the room with the Wumpus, the game will be over. When awoken, the Wumpus has a 75% chance of moving to another random room.

**Hazards:**

Bottomless Pits: Two rooms are bottomless pits, and the player will fall and die if entered.

Super Bats: Two rooms have super bats, that will carry the player to another random room if entered. 

**Gold:**

The gold is in it's own room, and the player will automatically pick it up when entering the room.

**Percepts:**

When adjacent to a room with an event, the player will see the prompts:

    Wumpus: "You smell a terrible stench."
    Super bats: "You hear wings flapping."
    Bottomless pit: "You feel a breeze."
    Gold: "You see a glimmer nearby."

There is no percept for the escape rope, the player must remember the room.

## To Run:

Compile with make

Run with ./hunt_wumpus SIZE DEBUG

     SIZE = Width and Height of square cave (ex: 5 gives 5x5 cave)
     
     DEBUG = true gives debug mode (case sensitive) where player can see rooms labeled
             false or none gives normal mode
             
             
