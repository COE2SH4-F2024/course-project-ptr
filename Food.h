#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

class Food
{
    private:
        objPos foodPos;
        GameMechs* mainGameMechsRef;
    
    public:
        Food(GameMechs* thisGMRef);
        ~Food();

        void generateFood(objPosArrayList*);
        objPos getFoodPos() const;
};

#endif