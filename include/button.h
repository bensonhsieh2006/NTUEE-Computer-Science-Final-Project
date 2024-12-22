#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include <SDL_bgi.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include "Backpack.h"

class button
{
    public:
        button(int, int, int, int, int);
        virtual ~button();
        bool handle(int &, Backpack* &);
        void setDetectArea(int, int, int, int);

    protected:

    private:
        SDL_Point position;
        int width;
        int height;
        int destNum;
        Mix_Chunk* sound = NULL;
};

#endif // BUTTON_H
