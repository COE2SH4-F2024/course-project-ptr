#include "Food.h"
#include "MacUILib.h"

Food::Food(GameMechs *thisGMRef)
{
    srand(time(NULL));
    foodPos = objPos();
    mainGameMechsRef = thisGMRef;
    foodBucket = new objPosArrayList;
    
    for(int i = 0; i < FOOD_BUCKET_SIZE; i++)
    {
        foodBucket->insertTail(objPos());
    }
}

Food::~Food()
{
    delete foodBucket;
}

void Food::generateFood(objPosArrayList* blockoff)
{
    for (int i = 0; i < foodBucket->getSize(); i++)
    {
        MacUILib_printf("\ngenerating food\n");
        int x, y, symbol;
        bool foodValid;
        do
        {
            foodValid = true;
            x = (rand() % (mainGameMechsRef->getBoardSizeX() - 2)) + 1; // generate random position on gameboard
            y = (rand() % (mainGameMechsRef->getBoardSizeY() - 2)) + 1;
            //symbol = (rand() % (MAXASCII-MINASCII)) + MINASCII; // generate random ascii symbol
            symbol = (rand() % SPECIAL_FOOD_CHANCE == 0) ? '$' : '+';
            //symbol = '+';
            //MacUILib_printf("pos generated\n");
            foodBucket->insertHead(objPos(x, y, symbol));

            for (int j = 0; j < blockoff->getSize(); j++)
            {
                foodValid &= !(foodBucket->getHeadElement().isPosEqual(blockoff->getElement(j)));
            }

            if (!foodValid)
            {
                foodBucket->removeHead();
            }
            //MacUILib_printf("food valid %d\n", foodValid);
        } 
        while (!foodValid); // repeat as long as generated position overlaps player
        foodBucket->removeTail();
        MacUILib_printf("food generated");
    }
}

objPosArrayList* Food::getFoodPos() const
{
    return foodBucket;
}