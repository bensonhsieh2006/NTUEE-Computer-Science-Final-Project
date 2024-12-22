#include "CharacterPoll.h"

CharacterPoll::CharacterPoll(int n): guarantee(n)
{
    //ctor
    srand(time(NULL));
    elevengot = new int [3];
}

CharacterPoll::~CharacterPoll()
{
    //dtor
    delete [] elevengot;
}

void CharacterPoll::getone()
{
    int seed = rand();
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

void CharacterPoll::get11()
{
    int seed;
    for (int i=0;i<3;i++) elevengot[i] = 0;
    for (int i=0;i<11;i++)
    {
        seed = rand();
        if (seed < 983)
        {
            elevengot[2]++;
        }
        else if (seed >= 4916)
        {
            elevengot[0]++;
        }
        else
            elevengot[1]++;
    }
}
