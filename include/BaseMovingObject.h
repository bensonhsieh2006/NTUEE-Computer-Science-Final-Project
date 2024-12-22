#ifndef BASEMOVINGOBJECT_H
#define BASEMOVINGOBJECT_H



#include <SDL.h>
#include <SDL_bgi.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <cmath>


class BaseMovingObject
{
    public:
        BaseMovingObject(int, int, int, int);
        virtual ~BaseMovingObject();

        virtual bool loadPic(SDL_Renderer* &r) = 0;
        bool move();
        void handle( SDL_Event &e );
        void render(SDL_Renderer* &r);
        int getPosX(){return posX;}
        int getPosY(){return posY;}
        int getObjWidth() const {return objWidth;}
        int getObjHeight() const {return objHeight;}
        int getVx(){return vX;}
        bool checkCollision(SDL_Rect &);
        SDL_Rect collisionRect = {};

    protected:
        int v;
        int posX;
        int posY;
        int vX;
        int vY;
        SDL_Texture* cTexture = NULL;

    private:

        const int objWidth;
        const int objHeight;

};

#endif // BASEMOVINGOBJECT_H
