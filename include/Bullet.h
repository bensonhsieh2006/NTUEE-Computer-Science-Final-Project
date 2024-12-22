#ifndef BULLET_H
#define BULLET_H

#include "BaseMovingObject.h"
#include "Backpack.h"

class Bullet : public BaseMovingObject
{
    public:
        Bullet(int bid, int _posx, int _posy, int _shoot_dir, Backpack*);
        virtual ~Bullet();
        bool loadPic(SDL_Renderer* &);
        int getDamage(){return damage;}

    protected:
        int damage;
        const int id;
        const int shoot_dir;

    private:
};

#endif // BULLET_H
