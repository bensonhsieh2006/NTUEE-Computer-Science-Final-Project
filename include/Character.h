#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL.h>
#include <SDL_bgi.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "BaseMovingObject.h"
#include <string>
#include <iostream>

class Character: public BaseMovingObject
{
    public:
        Character(int, int);//id, level
        virtual ~Character();
        bool loadPic(SDL_Renderer* &r);
        void gotAttacked(int);
        int getHp() {return hp;}
        int getMaxHp() {return maxHp;}
        void playSound();

    protected:

    private:
        int id;
        int hp;
        int maxHp;
        Mix_Chunk* sound = NULL;

};

#endif // CHARACTER_H
