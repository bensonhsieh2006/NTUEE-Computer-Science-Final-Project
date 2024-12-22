#include "GamePlay.h"
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

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

void GamePlay::handle_keyboard(SDL_Event &e, SDL_Renderer* &r, int &cd_count){
    C->handle(e);
    if (e.type == SDL_MOUSEBUTTONDOWN && cd_count > 20){
        int xnow, ynow, shoot_dir;
        SDL_GetMouseState(&xnow, &ynow);

        if ((xnow - C->getPosX()) > 0) shoot_dir = 1;
        else shoot_dir = -1;
        Bullet* new_bullet = NULL;
        new_bullet = new Bullet(characterID, C->getPosX() + C->getObjWidth() / 4, C->getPosY() + C->getObjHeight() / 10, shoot_dir);
        new_bullet->loadPic(r);
        character_bullets.push_back(new_bullet);
        cd_count = 0;
    }

}

void GamePlay::handle_move(int &count_mon_shoot, int &count_mon_move, SDL_Renderer* &r, bool &gameover, bool &won){
    M->update_pos(count_mon_move);

    if (count_mon_shoot > 70/level){
        Bullet* new_bullet = NULL;
        int shoot_dir, rel_X;
        rel_X = C->getPosX() - M->getPosX();
        if (rel_X == 0) shoot_dir = 1;
        else shoot_dir = rel_X/abs(rel_X);

        new_bullet = new Bullet(2+level, M->getPosX() + M->getObjWidth() / 4, M->getPosY() + M->getObjHeight() / 4, shoot_dir);
        new_bullet->loadPic(r);
        monster_bullets.push_back(new_bullet);
        count_mon_shoot = 0;
    }

    it = character_bullets.begin();
    for (Bullet* eb: character_bullets){
        if(eb->move()){
            delete eb;
            it = character_bullets.erase(it);
            --it;
        }
        else if(M->checkCollision(eb->collisionRect)){
            M->gotAttacked(eb->getDamage());
            delete eb;
            it = character_bullets.erase(it);
            --it;
        }
        ++it;
    }

    it = monster_bullets.begin();
    for (Bullet* eb: monster_bullets){
        if(eb->move()){
            delete eb;
            it = monster_bullets.erase(it);
            --it;
        }
        else if(C->checkCollision(eb->collisionRect)){
            C->gotAttacked(eb->getDamage());
            delete eb;
            it = character_bullets.erase(it);
            --it;
        }
        ++it;
    }

    if (C->getHp()<=0){ gameover = true; won = false;}
    if (M->getHp()<=0){ gameover = true; won = true;}
    return;
}

bool GamePlay::load(SDL_Renderer* &r){
    C = new Character(characterID);
    C->loadPic(r);
    M = new Monster(level-1);
    M->loadPic(r);
}

void GamePlay::render(SDL_Renderer* &r, bool &paused){
    M->render(r);
    C->render(r);
    for (Bullet* eb: character_bullets){
        eb->render(r);
    }
    for (Bullet* eb: monster_bullets){
        eb->render(r);
    }
    SDL_SetRenderDrawColor( r, 0xFF, 0x00, 0x00, 0xFF );
    SDL_Rect fillRect = {SCREEN_WIDTH/100, SCREEN_HEIGHT/70, SCREEN_WIDTH/3*C->getHp()/C->getMaxHp(), SCREEN_HEIGHT/20};
    SDL_RenderFillRect( r, &fillRect );
    fillRect = {SCREEN_WIDTH*99/100 - SCREEN_WIDTH/3*M->getHp()/M->getMaxHp(), SCREEN_HEIGHT/70, SCREEN_WIDTH/3*M->getHp()/M->getMaxHp(), SCREEN_HEIGHT/20};
    SDL_RenderFillRect( r, &fillRect );

    if(paused){
        SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor( r, 0x00, 0x00, 0x00, 0xA0 );
        SDL_Rect fillRect = {SCREEN_WIDTH/8, SCREEN_HEIGHT/8, SCREEN_WIDTH*3/4, SCREEN_HEIGHT*3/4};
        SDL_RenderFillRect( r, &fillRect );
    }
}
