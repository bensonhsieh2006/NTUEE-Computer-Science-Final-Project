#include "button.h"

button::button(int x, int y, int w, int h, int dest): width(w), height(h), destNum(dest)
{
    position.x = x;
    position.y = y;
    sound = Mix_LoadWAV("soundeffects/bottle_pop.wav");
    if (sound == NULL) std::cout << "Music Not Loaded! Error: " << Mix_GetError() << std::endl;
    //ctor
}

button::~button()
{
    Mix_FreeChunk(sound);
    sound = NULL;
}

bool button::handle(SDL_Event* e, int &controlNum)
{
    if (e->type == SDL_MOUSEBUTTONDOWN)
    {
        int xnow, ynow;
        SDL_GetMouseState(&xnow, &ynow);

        bool inside = true;
        if (xnow < position.x || (xnow > position.x + width) || (ynow < position.y) || (ynow > position.y + height)) inside = false;

        if (inside) {
            controlNum  = destNum;
            Mix_PlayChannel(-1,sound,0);
            return 1;
        }
    }
}

void button::setDetectArea(int _x, int _y, int _w, int _h){
    position.x = _x;
    position.y = _y;
    height = _h;
    width = _w;
}
