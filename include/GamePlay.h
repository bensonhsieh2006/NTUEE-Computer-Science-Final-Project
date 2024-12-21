#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SDL.h>
#include <SDL_bgi.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <list>
#include <string>
#include <iostream>
#include <cmath>

#include "Character.h"
#include "Monster.h"
#include "Bullet.h"
#include "BaseMovingObject.h"

class GamePlay
{
    public:
        GamePlay(int cid, int stg);
        virtual ~GamePlay();
        void handle_keyboard(SDL_Event &, SDL_Renderer* &, int &cd_count);
        void handle_move(int &, SDL_Renderer* &);
        bool load(SDL_Renderer* &);
        void render(SDL_Renderer* &);

    protected:
        Character* C = NULL;
        Monster* M = NULL;
        std::list<Bullet* > character_bullets = {};
        std::list<Bullet* > monster_bullets = {};
        std::list<Bullet* >::iterator it;

    private:
        int characterID;
        int level;
};

#endif // GAMEPLAY_H
