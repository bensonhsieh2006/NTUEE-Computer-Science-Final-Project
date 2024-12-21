#ifndef BULLET_H
#define BULLET_H

#include <BaseMovingObject.h>


class Bullet : public BaseMovingObject
{
    public:
        Bullet(int bid);
        virtual ~Bullet();
        bool loadPic(SDL_Renderer* &);

    protected:
        int damage;
        int id;

    private:
};

#endif // BULLET_H
