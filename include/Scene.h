#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <SDL.h>
#include <SDL_bgi.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include"CharacterPoll.h"

#include <string>
#include <stdio.h>
#include <cmath>

class Scene
{
    public:
        Scene();
        virtual ~Scene();
        bool loadPic(std::string, int, SDL_Renderer* &);
        bool loadText( std::string textureText, int textID, SDL_Color textColor, SDL_Renderer* & );
        void setViewport(float, float, float, float);

        void loadStart(SDL_Renderer* &);
        void renderStart(SDL_Renderer* &);
        void loadStory(SDL_Renderer* &);
        void renderStory(SDL_Renderer* &, int&, bool&);
        void loadMainpage(SDL_Renderer* &);
        void renderMainpage(SDL_Renderer*&);
        void loadStageOne(SDL_Renderer* &);
        void renderStageOne(SDL_Renderer* &, bool&);
        void loadStageTwo(SDL_Renderer* &);
        void renderStageTwo(SDL_Renderer* &, bool &);
        void loadStageThree(SDL_Renderer* &);
        void renderStageThree(SDL_Renderer* &, bool &);
        void loadGacha(SDL_Renderer* &, int);
        void renderGacha(SDL_Renderer* &, int);
        void loadGachaX1(SDL_Renderer* &);
        void renderGachaX1(SDL_Renderer* &, int &, bool &);
        void loadGachaX11(SDL_Renderer* &);
        void renderGachaX11(SDL_Renderer* &, int &);

        SDL_Texture *& getExtendedTexture1() {return extendedTexture1;}
        SDL_Texture *& getExtendedTexture2() {return extendedTexture2;}
        SDL_Texture *& getTextTexture1 () {return textTexture1;}
        SDL_Texture *& getTextTexture2 () {return textTexture2;}
        SDL_FRect & getViewportRect() {return viewport;}

        void free();

    protected:

    private:
        SDL_Texture *backgroundTexture, *decorationTexture, *textTexture1, *textTexture2, *textTexture3;
        SDL_Texture *extendedTexture1,*extendedTexture2, *extendedTexture3,*extendedTexture4,*extendedTexture5;
        SDL_FRect viewport;
        TTF_Font* gFont;
        CharacterPoll poll;
};

#endif // SCENE_H
