#include "Player.h"
#include "MacUILib.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos.setObjPos(1,1, '*');
    playerPosList = new objPosArrayList;
    initialBodyLength = 3;

    for (int i = 0; i < initialBodyLength; i++)
    {
        playerPosList->insertHead(objPos(i+1, 1, '*'));
    }
}

Player::~Player()
{
    delete playerPosList;
    // delete any heap members here
}

objPos Player::getPlayerHeadPos() const
{
    return playerPosList->getHeadElement();
    // return the reference to the playerPos arrray list
}

objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    switch(mainGameMechsRef->getInput())
    {
        case 'w':
            if(getDir() == DOWN)
            {
                break;
            }
            setDir(UP);
            break;
        case 'a':
            if(getDir() == RIGHT)
            {
                break;
            }
            setDir(LEFT);
            break;
        case 's':
            if(getDir() == UP)
            {
                break;
            }
            setDir(DOWN);
            break;
        case 'd':
            if(getDir() == LEFT)
            {
                break;
            }
            setDir(RIGHT);
            break;
        default:
            break;
    }

    mainGameMechsRef->clearInput();
        // PPA3 input processing logic          
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    
    switch(myDir)
    {
        case UP:
            (playerPos.pos->y)--;
            if(playerPos.pos->y <= 0){
                playerPos.pos->y = (mainGameMechsRef->getBoardSizeY() - 2);
            }
            break;
        case DOWN:
            (playerPos.pos->y)++;
            if(playerPos.pos->y == (mainGameMechsRef->getBoardSizeY() - 1)){
                playerPos.pos->y = 1;
            }
            break;
        case RIGHT:
            (playerPos.pos->x)++;
            if(playerPos.pos->x == mainGameMechsRef->getBoardSizeX() - 1){
                playerPos.pos->x = 1;
            }
            break;
        case LEFT:
            (playerPos.pos->x)--;
            if(playerPos.pos->x <= 0){
                playerPos.pos->x = (mainGameMechsRef->getBoardSizeX() - 2);
            }
            break;
        default:
            break;
    }

    playerPosList->insertHead(playerPos); // insert next position at head
    playerPosList->removeTail(); // remove last position in list
    
    for(int i = 1; i < playerPosList->getSize(); i++)
    {
        if(myDir != STOP){
            if((playerPosList->getHeadElement()).isPosEqual((playerPosList)->getElement(i)))
            {
                mainGameMechsRef->setExitTrue();
                mainGameMechsRef->setLoseFlag();
            }
        }
    }   
}

Player::Dir Player::getDir()
{
    return myDir;
}

void Player::setDir(Dir direction)
{
    myDir = direction;
}

bool Player::checkFoodConsumption(Food* foodRef)
{
    if (this->getPlayerHeadPos().isPosEqual(foodRef->getFoodPos()))
    {
        foodRef->generateFood(playerPosList);
        return true;
    }

    else
    {
        return false;
    }
}

void Player::increasePlayerLength()
{
    playerPosList->insertHead(playerPos); // insert next position at head
}
// More methods to be added