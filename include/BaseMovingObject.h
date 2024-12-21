#ifndef BASEMOVINGOBJECT_H
#define BASEMOVINGOBJECT_H



#include <SDL.h>
#include <SDL_bgi.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>


class BaseMovingObject
{
    public:
        BaseMovingObject(int, int, int, int);
        virtual ~BaseMovingObject();

        /*int Getcx() { return cx; }
        void Setcx(int val) { cx = val; }
        int Getcy() { return cy; }
        void Setcy(int val) { cy = val; }
        int Getvcx() { return vcx; }
        void Setvcx(int val) { vcx = val; }
        int Getvcy() { return vcy; }
        void Setvcy(int val) { vcy = val; }*/

        virtual bool loadPic(SDL_Renderer* &r) = 0;
        void move();
        void handle( SDL_Event &e );
        void render(SDL_Renderer* &r);

    protected:
        int v;
        int posX;
        int posY;
        SDL_Texture* cTexture = NULL;

    private:

        int vX;
        int vY;
        int objWidth;
        int objHeight;

};

#endif // BASEMOVINGOBJECT_H
