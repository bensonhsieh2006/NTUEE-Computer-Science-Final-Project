#ifndef BULLET_H
#define BULLET_H

#include <BaseMovingObject.h>

class Bullet : public BaseMovingObject
{
    public:
        Bullet(int bid, int _posx, int _posy, int _shoot_dir);
        virtual ~Bullet();
        bool loadPic(SDL_Renderer* &);
        int getDamage(){return damage;}

    protected:
        int damage;
        int id;
        int shoot_dir;

    private:
};

#endif // BULLET_H
