#ifndef MONSTER_H
#define MONSTER_H

#include "BaseMovingObject.h"
#include <random>
#include <ctime>

class Monster : public BaseMovingObject
{
    public:
        Monster(int i);
        virtual ~Monster();
        bool loadPic(SDL_Renderer* &);
        void update_pos(int &);
        void gotAttacked(int);
        int getHp() {return hp;}
        int getMaxHp() {return maxHp;}

    protected:

    private:
        int monid;
        int hp;
        int maxHp;
};

#endif // MONSTER_H
