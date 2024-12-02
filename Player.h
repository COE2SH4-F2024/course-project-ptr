#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "Food.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

     
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        objPos getPlayerHeadPos() const; // Upgrade this in iteration 3.  
        objPosArrayList* getPlayerPos() const;     
        void updatePlayerDir();
        void movePlayer();
        bool checkFoodConsumption(Food* foodRef, objPos*);
        void increasePlayerLength();

        // More methods to be added here
        Dir getDir();
        void setDir(Dir direction);
    private:
        objPosArrayList* playerPosList;
        objPos playerPos; // Upgrade this in iteration 3.       
        enum Dir myDir;
        int initialBodyLength;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif