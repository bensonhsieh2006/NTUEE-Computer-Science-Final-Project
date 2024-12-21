#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SDL.h>
#include <SDL_bgi.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Character.h"
#include "Monster.h"
class GamePlay
{
    public:
        GamePlay(int cid, int stg);
        virtual ~GamePlay();
        void handle_keyboard(SDL_Event &);
        void handle_collision();
        bool load(SDL_Renderer* &);
        void render(SDL_Renderer* &);

    protected:
        Character* C = NULL;
        Monster* M = NULL;

    private:
        int characterID;
        int level;
};

#endif // GAMEPLAY_H
