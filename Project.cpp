#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* GameMechsPtr = NULL;
Player* PlayerPtr = NULL;

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(GameMechsPtr->getExitFlagStatus() == 0)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    GameMechsPtr = new GameMechs();
    PlayerPtr = new Player(GameMechsPtr);

    exitFlag = false;
}

void GetInput(void)
{
    if(MacUILib_hasChar())
    {
        GameMechsPtr->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    if(GameMechsPtr->getInput() == '\x1B') // '\1xB is the escape character
    {
        GameMechsPtr->setExitTrue();
    }
    PlayerPtr->updatePlayerDir();
    PlayerPtr->movePlayer();
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    for(int y = 0; y<GameMechsPtr->getBoardSizeY() ; y++){
        if(y != 0){
            MacUILib_printf("\n");
        }
        for(int x = 0; x<GameMechsPtr->getBoardSizeX() ; x++){
            if(y == 0 || x == 0 || x == (GameMechsPtr->getBoardSizeX()) - 1 || y == (GameMechsPtr->getBoardSizeY()) - 1){
                MacUILib_printf("#");
            }
            else if(x == (PlayerPtr->getPlayerPos()).pos->x && y == (PlayerPtr->getPlayerPos()).pos->y){
                MacUILib_printf("%c", (PlayerPtr->getPlayerPos()).symbol);
            }
            else{
                MacUILib_printf(" ");
            }
        }
    }
    MacUILib_printf("\nPress ESC to quit");
    MacUILib_printf("\nPlayer at X = %d, Y = %d", (PlayerPtr->getPlayerPos()).pos->x, (PlayerPtr->getPlayerPos()).pos->y);   
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    MacUILib_uninit();

    delete GameMechsPtr;
    delete PlayerPtr;
}
