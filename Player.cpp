#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos.setObjPos(0,0, '*');
    // more actions to be included
}

Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    return playerPos;
    // return the reference to the playerPos arrray list
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
}

Player::Dir Player::getDir()
{
    return myDir;
}

void Player::setDir(Dir direction)
{
    myDir = direction;
}
// More methods to be added