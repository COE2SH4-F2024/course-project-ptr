#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

#define FOOD_BUCKET_SIZE 5
#define SPECIAL_FOOD_CHANCE 7 // 1 in x chance of generating special food

class Food
{
    private:
        objPos foodPos;
        GameMechs* mainGameMechsRef;
        objPosArrayList* foodBucket;
    
    public:
        Food(GameMechs* thisGMRef);
        ~Food();

        void generateFood(objPosArrayList*);
        objPosArrayList* getFoodPos() const;
};

#endif