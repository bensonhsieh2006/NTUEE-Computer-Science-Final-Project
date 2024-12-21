#ifndef BASEMOVINGOBJECT_H
#define BASEMOVINGOBJECT_H

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

#include <SDL.h>
#include <SDL_bgi.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <string>


class BaseMovingObject
{
    public:
        BaseMovingObject(int, int, int);
        virtual ~BaseMovingObject();

        /*int Getcx() { return cx; }
        void Setcx(int val) { cx = val; }
        int Getcy() { return cy; }
        void Setcy(int val) { cy = val; }
        int Getvcx() { return vcx; }
        void Setvcx(int val) { vcx = val; }
        int Getvcy() { return vcy; }
        void Setvcy(int val) { vcy = val; }*/

        virtual bool loadPic(std::string c, SDL_Renderer* &r) = 0;
        void move();
        void handle( SDL_Event &e );
        void render(SDL_Renderer* &r);

    protected:

    private:
        int v;
        int posX;
        int posY;
        int vX;
        int vY;
        int objWidth;
        int objHeight;
        SDL_Texture* cTexture = NULL;
};

#endif // BASEMOVINGOBJECT_H
