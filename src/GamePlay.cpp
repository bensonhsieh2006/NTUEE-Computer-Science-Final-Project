#include "GamePlay.h"
#include <SDL.h>
#include <SDL_bgi.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <BaseMovingObject.h>
#include <string>
#include "Character.h"

GamePlay::GamePlay(int cid, int stg)
{
    //ctor
    characterID = cid;
    level = stg;
}

GamePlay::~GamePlay()
{
    //dtor
    if(C != NULL){
        delete C;
    }
    if(M != NULL)
    {
        delete M;
    }
}

void GamePlay::handle_keyboard(SDL_Event &e){
    C->handle(e);
}

void GamePlay::handle_collision(){
    return;
}

bool GamePlay::load(SDL_Renderer* &r){
    C = new Character(characterID);
    C->loadPic(r);
    M = new Monster(level);
    M->loadPic(r);
}

void GamePlay::render(SDL_Renderer* &r){
    M->render(r);
    C->render(r);
}
