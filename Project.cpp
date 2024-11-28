#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* GameMechsPtr = NULL;
Player* PlayerPtr = NULL;
Food* FoodPtr = NULL;

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
    MacUILib_printf("\e[?25l"); // hide cursor
    
    GameMechsPtr = new GameMechs();
    PlayerPtr = new Player(GameMechsPtr);
    FoodPtr = new Food(GameMechsPtr);

    FoodPtr->generateFood(PlayerPtr->getPlayerPos());
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
    if (PlayerPtr->checkFoodConsumption(FoodPtr))
    {
        PlayerPtr->increasePlayerLength();
    }
    
    // FoodPtr->generateFood(PlayerPtr->getPlayerPos());
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    for(int y = 0; y < GameMechsPtr->getBoardSizeY() ; y++)
    {
        if(y != 0){ MacUILib_printf("\n"); }
        for(int x = 0; x < GameMechsPtr->getBoardSizeX() ; x++)
        {
            // game board border
            if(y == 0 || x == 0 || x == (GameMechsPtr->getBoardSizeX()) - 1 || y == (GameMechsPtr->getBoardSizeY()) - 1)
            {
                MacUILib_printf("#");
            }

            // food
            else if (FoodPtr->getFoodPos().isPosEqual(x, y))
            {
                MacUILib_printf("%c", (FoodPtr->getFoodPos()).symbol);
            }

            else
            {
                MacUILib_printf(" ");
            }

            // player
            for (int i = 0; i < PlayerPtr->getPlayerPos()->getSize(); i++)
            {
                if(PlayerPtr->getPlayerPos()->getElement(i).isPosEqual(x, y))
                {
                    MacUILib_printf("%c%c", '\b', PlayerPtr->getPlayerHeadPos().getSymbol());
                }
            }
        }
    }

    
    MacUILib_printf("\nPress ESC to quit");
    MacUILib_printf("\nPlayer at X = %d, Y = %d", PlayerPtr->getPlayerHeadPos().pos->x, PlayerPtr->getPlayerHeadPos().pos->y);   
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();
    MacUILib_printf("\e[?25h"); // show cursor  
    MacUILib_uninit();

    delete GameMechsPtr;
    delete PlayerPtr;
    delete FoodPtr;
}
