#include "Food.h"
#include "MacUILib.h"

Food::Food(GameMechs *thisGMRef)
{
    // seed random generator
    srand(time(NULL));
    foodPos = objPos();
    mainGameMechsRef = thisGMRef;
    foodBucket = new objPosArrayList;
    
    // fill food bucket with default objects
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
        int x, y, symbol;
        bool foodValid;
        do
        {
            foodValid = true;
            x = (rand() % (mainGameMechsRef->getBoardSizeX() - 2)) + 1; // generate random position on gameboard
            y = (rand() % (mainGameMechsRef->getBoardSizeY() - 2)) + 1;
            // 1 in special_food_chance of generating special food
            symbol = (rand() % SPECIAL_FOOD_CHANCE == 0) ? '$' : '+';

            // insert generated food into bucket
            foodBucket->insertHead(objPos(x, y, symbol));

            // check if generated food is valid
            for (int j = 0; j < blockoff->getSize(); j++)
            {
                foodValid &= !(foodBucket->getHeadElement().isPosEqual(blockoff->getElement(j)));
            }

            // remove food if invalid
            if (!foodValid)
            {
                foodBucket->removeHead();
            }
        } 
        while (!foodValid); // repeat as long as generated position overlaps player
        // remove last item if inserted food is valid
        foodBucket->removeTail();
    }
}

objPosArrayList* Food::getFoodPos() const
{
    return foodBucket;
}