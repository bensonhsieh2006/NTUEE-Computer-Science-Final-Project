#ifndef MONSTER_H
#define MONSTER_H

#include "BaseMovingObject.h"
#include <random>
#include <ctime>

class Monster : public BaseMovingObject
{
    public:
        Monster(int i);
        Monster* operator- (const int &);
        virtual ~Monster();
        bool loadPic(SDL_Renderer* &);
        void update_pos();
        int getHp() {return hp;}
        int getMaxHp() const {return maxHp;}

    protected:

    private:
        static int count_mon_move;

        const int monid;
        int maxHp;
        int hp;
};

#endif // MONSTER_H
