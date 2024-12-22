#include "Backpack.h"

Backpack::Backpack()
{
    //ctor
    characterlvl = new int [3];
    characternum = new int [3];
    characterlvl[0] = 1;
    characterlvl[1] = 0;
    characterlvl[2] = 0;
    characternum[0] = 1;
    characternum[1] = 0;
    characternum[2] = 0;
    selected = 0;
}

Backpack::~Backpack()
{
    //dtor
    delete [] characterlvl;
    delete [] characternum;
}

void Backpack::addnum(int id, int num)
{
    characternum[id] += num;
    switch (id)
    {
    case (0):
<<<<<<< HEAD
        if (characternum[id] >= 3+characterlvl[id] && (characterlvl[id] < 6))
=======
        if (characternum[id] > (3+characterlvl[id]) && (characterlvl[id] < 6))
>>>>>>> b088a304bdc05e0055709d82dbfd48af6eb675c2
        {
            characternum[id] -= (3+characterlvl[id]);
            characterlvl[id]++;
            //std::cout<<"0 level up"<<std::endl;
        }
        break;
    case (1):
<<<<<<< HEAD
        if (characternum[id] >= 2+characterlvl[id] && (characterlvl[id] < 6))
=======
        if (characternum[id] > 2+characterlvl[id] && (characterlvl[id] < 6))
>>>>>>> b088a304bdc05e0055709d82dbfd48af6eb675c2
        {
            characternum[id] -= (2+characterlvl[id]);
            characterlvl[id]++;
            //std::cout<<"1 level up"<<std::endl;
        }
        break;
    case (2):
        if (characternum[id] > 1+characterlvl[id] && (characterlvl[id] < 6))
        {
            characternum[id] -= (1+characterlvl[id]);
            characterlvl[id]++;
            //std::cout<<"2 level up"<<std::endl;
        }
        break;
    }
}

int Backpack::getlvl(int id)
{
    return characterlvl[id];
}

void Backpack::changeselect(int id)
{
    selected = id;
}

int Backpack::getselected()
{
    return selected;
}
