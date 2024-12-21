#include "BaseMovingObject.h"

BaseMovingObject::BaseMovingObject(int width, int height, int _v): v(_v), objWidth(width), objHeight(height)
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

void BaseMovingObject::move(){
    posX += vX;
    if((posX < 0) || (posX + objWidth > SCREEN_WIDTH)){
        posX -= vX;
    }
    posY += vY;
    if((posY < 0) || (posX + objHeight > SCREEN_HEIGHT)){
        posX  -= vX;
    }
}

void BaseMovingObject::handle(SDL_Event &e){
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0){
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: vY -= v; break;
            case SDLK_DOWN: vY += v; break;
            case SDLK_LEFT: vX -= v; break;
            case SDLK_RIGHT: vX += v; break;
        }
    }

    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: vY += v; break;
            case SDLK_DOWN: vY -= v; break;
            case SDLK_LEFT: vX += v; break;
            case SDLK_RIGHT: vX -= v; break;
        }
    }
}

void BaseMovingObject::render(SDL_Renderer* &r){
    SDL_Rect pos = {posX, posY, objWidth, objHeight};
    SDL_RenderCopy(r, cTexture, NULL, &pos);
}


