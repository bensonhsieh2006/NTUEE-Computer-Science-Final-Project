#ifndef CHARACTERPOLL_H
#define CHARACTERPOLL_H

#include <iostream>
#include <SDL.h>
#include <SDL_bgi.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <string>
#include <stdio.h>
#include <cmath>

#include <stdlib.h>
#include <ctime>

class CharacterPoll
{
    public:
        CharacterPoll(int);
        virtual ~CharacterPoll();
        void getone();
        int onegot;

    protected:

    private:
        int guarantee;
};

#endif // CHARACTERPOLL_H
