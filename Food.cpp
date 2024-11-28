#include "Food.h"

Food::Food(GameMechs *thisGMRef)
{
    srand(time(NULL));
    foodPos = objPos();
    mainGameMechsRef = thisGMRef;
}

Food::~Food()
{

}

void Food::generateFood(objPosArrayList* blockoff)
{
    int x, y, symbol;
    bool foodValid = true;
    do
    {
        x = (rand() % (mainGameMechsRef->getBoardSizeX() - 2)) + 1; // generate random position on gameboard
        y = (rand() % (mainGameMechsRef->getBoardSizeY() - 2)) + 1;
        symbol = (rand() % (MAXASCII-MINASCII)) + MINASCII; // generate random ascii symbol

        foodPos.setObjPos(x, y, symbol);

        for (int i = 0; i < blockoff->getSize(); i++)
        {
            foodValid &= !(foodPos.isPosEqual(blockoff->getElement(i)));
        }
    } 
    while (!foodValid); // repeat as long as generated position overlaps player
}

objPos Food::getFoodPos() const
{
    return foodPos;
}