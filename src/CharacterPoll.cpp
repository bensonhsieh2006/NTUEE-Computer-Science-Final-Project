#include "CharacterPoll.h"

CharacterPoll::CharacterPoll(int n): guarantee(n)
{
    //ctor
    srand(time(NULL));
    std::cout<<RAND_MAX<<std::endl;
}

CharacterPoll::~CharacterPoll()
{
    //dtor
}

void CharacterPoll::getone()
{
    int seed = rand();
    std::cout<<seed<<std::endl;
    if (seed < 983)
    {
        onegot = 2;
    }
    else if (seed >= 4916)
    {
        onegot = 0;
    }
    else
        onegot = 1;
}
