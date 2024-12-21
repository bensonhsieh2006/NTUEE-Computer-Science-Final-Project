#include "Character.h"

Character::Character(): BaseMovingObject(130, 200, 0)
{
    //ctor
}

Character::~Character()
{
    //dtor
}

bool Character::loadPic(std::string c, SDL_Renderer* &r){
    return 1;
}
