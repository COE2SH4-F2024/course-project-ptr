#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#define DEFAULT_BOARD_SIZE_X 30;
#define DEFAULT_BOARD_SIZE_Y 15;
#define MAXASCII 176 // -
#define MINASCII 33 // !

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;

        int boardSizeX;
        int boardSizeY;

        objPos food;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs(); // is this one needed at all? Why or why not?
        
        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const;
        void setLoseFlag();

        char getInput() const;
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX() const;
        int getBoardSizeY() const;

        int getScore() const;
        void incrementScore();
        
        // More methods should be added here
};

#endif