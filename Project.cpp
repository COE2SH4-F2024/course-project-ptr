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
    
    // initialize main game components
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

    // update player based on input
    PlayerPtr->updatePlayerDir();
    PlayerPtr->movePlayer();

    // check food consumption and specialty food 
    objPos food;
    if (PlayerPtr->checkFoodConsumption(FoodPtr, &food))
    {
        PlayerPtr->increasePlayerLength();
        if (food.symbol == '$') // special food increases length and score by 2
        {
            PlayerPtr->increasePlayerLength();
            GameMechsPtr->incrementScore();
        }
        FoodPtr->generateFood(PlayerPtr->getPlayerPos());
        GameMechsPtr->incrementScore();
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    // loop through entire game board area
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

            else
            {
                MacUILib_printf(" ");
            }

            // food
            for (int i = 0; i < FoodPtr->getFoodPos()->getSize(); i++)
            {
                if(FoodPtr->getFoodPos()->getElement(i).isPosEqual(x, y))
                {
                    //overwrite charachter with \b
                    MacUILib_printf("%c%c", '\b', FoodPtr->getFoodPos()->getElement(i).getSymbol());
                }
            }

            // player
            for (int i = 0; i < PlayerPtr->getPlayerPos()->getSize(); i++)
            {
                //overwrite charachter with \b
                if(PlayerPtr->getPlayerPos()->getElement(i).isPosEqual(x, y))
                {
                    MacUILib_printf("%c%c", '\b', PlayerPtr->getPlayerHeadPos().getSymbol());
                }
            }
        }
    }
    
    MacUILib_printf("\nPress ESC to quit");
    MacUILib_printf("\nScore = %d", GameMechsPtr->getScore());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();

    if((GameMechsPtr->getLoseFlagStatus()))
    {
        MacUILib_printf("\nGAME LOST");
    }

    MacUILib_printf("\e[?25h"); // show cursor  
    MacUILib_uninit();

    delete GameMechsPtr;
    delete PlayerPtr;
    delete FoodPtr;
}
