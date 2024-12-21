#include "BaseMovingObject.h"
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

BaseMovingObject::BaseMovingObject(int width, int height, int _vx, int _vy): vX(_vx), vY(_vy), objWidth(width), objHeight(height)
{
    //ctor
}

BaseMovingObject::~BaseMovingObject()
{
    if (cTexture != NULL){
        SDL_DestroyTexture(cTexture);
        cTexture = NULL;
    }
}

bool BaseMovingObject::move(){
    bool collided = false;
    posX += vX;
    if((posX < 0) || (posX + objWidth > SCREEN_WIDTH)){
        posX -= vX;
        collided = true;
    }
    posY += vY;
    if((posY < SCREEN_HEIGHT/20) || (posY + objHeight > SCREEN_HEIGHT)){
        posY  -= vY;
        collided = true;
    }

    collisionRect.x = posX;
    collisionRect.y = posY;
    return collided;
}

void BaseMovingObject::handle(SDL_Event &e){

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0){
        switch( e.key.keysym.sym )
        {
            case SDLK_w: vY -= v; break;
            case SDLK_s: vY += v; break;
            case SDLK_a: vX -= v; break;
            case SDLK_d: vX += v; break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_w: vY += v; break;
            case SDLK_s: vY -= v; break;
            case SDLK_a: vX += v; break;
            case SDLK_d: vX -= v; break;
        }
    }
    move();

}

void BaseMovingObject::render(SDL_Renderer* &r){
    SDL_Rect pos = {posX, posY, objWidth, objHeight};
    SDL_RenderCopy(r, cTexture, NULL, &pos);
}

bool BaseMovingObject::checkCollision(SDL_Rect &rect){
    if ((collisionRect.y + collisionRect.h) <= rect.y) return false;
    if (collisionRect.y >= (rect.y + rect.h)) return false;
    if ((collisionRect.x + collisionRect.w) <= rect.x) return false;
    if (collisionRect.x >= (rect.x + rect.w)) return false;
    return true;
}


