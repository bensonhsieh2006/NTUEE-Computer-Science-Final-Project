#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL.h>
#include <SDL_bgi.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "BaseMovingObject.h"
#include <string>

class Character: public BaseMovingObject
{
    public:
        Character(int);
        virtual ~Character();
        bool loadPic(SDL_Renderer* &r);

    protected:

    private:
        int id;
        int hp;

};

#endif // CHARACTER_H
