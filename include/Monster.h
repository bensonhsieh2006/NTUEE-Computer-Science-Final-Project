#ifndef MONSTER_H
#define MONSTER_H

#include "BaseMovingObject.h"


class Monster : public BaseMovingObject
{
    public:
        Monster(int i);
        virtual ~Monster();
        bool loadPic(SDL_Renderer* &);

    protected:

    private:
        int monid;
        int hp;
};

#endif // MONSTER_H
