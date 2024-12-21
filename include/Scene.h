#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <SDL.h>
#include <SDL_bgi.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <string>
#include <stdio.h>

class Scene
{
    public:
        Scene();
        virtual ~Scene();
        bool loadPic(std::string, int, SDL_Renderer* &);
        bool loadText( std::string textureText, SDL_Color textColor, SDL_Renderer* & );
        void setViewport(float, float, float, float);

        void loadStart(SDL_Renderer* &);
        void renderStart(SDL_Renderer* &);
        void loadStory(SDL_Renderer* &);
        void renderStory(SDL_Renderer* &, int&, bool&);
        void loadMainpage(SDL_Renderer* &);
        void renderMainpage(SDL_Renderer*&, int&, bool&);
        void loadStageOne(SDL_Renderer* &);
        void renderStageOne(SDL_Renderer* &, int &, bool &);
        void loadStageTwo(SDL_Renderer* &);
        void renderStageTwo(SDL_Renderer* &, int &, bool &);
        void loadStageThree(SDL_Renderer* &);
        void renderStageThree(SDL_Renderer* &, int &, bool &);
        void free();

    protected:

    private:
        SDL_Texture *backgroundTexture, *decorationTexture, *textTexture;
        SDL_Texture *extendedTexture1,*extendedTexture2, *extendedTexture3,*extendedTexture4,*extendedTexture5;
        SDL_FRect viewport;
        TTF_Font* gFont;

};

#endif // SCENE_H
