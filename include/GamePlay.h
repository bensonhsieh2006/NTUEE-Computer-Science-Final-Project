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
#include "Backpack.h"

class GamePlay
{
    public:
        GamePlay(int cid, int stg);
        virtual ~GamePlay();

        void handle_keyboard(SDL_Event &, SDL_Renderer* &, int &cd_count, Backpack*);
        void handle_move(SDL_Renderer* &, bool&, bool&, Backpack*);
        bool load(SDL_Renderer* &, Backpack*);
        void render(SDL_Renderer* &, bool &);

    protected:


    private:
        const int characterID;
        const int level;
        static int count_mon_shoot;
        static int cd_count;
        Character* C = NULL;
        Monster* M = NULL;
        std::list<Bullet* > character_bullets = {};
        std::list<Bullet* > monster_bullets = {};
        std::list<Bullet* >::iterator it;
};

#endif // GAMEPLAY_H
