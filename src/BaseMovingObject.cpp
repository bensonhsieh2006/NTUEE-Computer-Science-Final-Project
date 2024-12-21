#include "BaseMovingObject.h"

BaseMovingObject::BaseMovingObject(int width, int height, int _v = 0): v(_v), objWidth(width), objHeight(height)
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
    cx += vcx;
    if((cx < 0) || (cx + objWidth > SCREEN_WIDTH)){
        cx -= vcx;
    }
    cy = cy + vcy;
    if((cx > 0) || (cy + objHeight > SCREEN_HEIGHT)){
        cy -= vcy;
    }
}

void BaseMovingObject::handle(SDL_Event &e){
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0){
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: vcy -= v; break;
            case SDLK_DOWN: vcy += v; break;
            case SDLK_LEFT: vcx -= v; break;
            case SDLK_RIGHT: vcx += v; break;
        }
    }

    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: vcy += v; break;
            case SDLK_DOWN: vcx -= v; break;
            case SDLK_LEFT: vcx += v; break;
            case SDLK_RIGHT: vcx -= v; break;
        }
    }
}

void BaseMovingObject::render(SDL_Renderer* &r){
    SDL_Rect pos = {cx, cy, objWidth, objHeight}
    SDL_RenderCopy(r, cTexture, NULL, pos);
}

