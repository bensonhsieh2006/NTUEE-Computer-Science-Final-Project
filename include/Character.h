#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL.h>
#include <SDL_bgi.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <string>

class Character: public BaseMovingObject
{
    public:
        Character();
        virtual ~Character();
        void loadPic(string c, SDL_Renderer* &r);

    protected:

    private:
        SDL_Texture* cTexture = NULL;

};

#endif // CHARACTER_H
