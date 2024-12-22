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

bool button::handle(int &controlNum, Backpack* &player)
{
    int xnow, ynow;
    SDL_GetMouseState(&xnow, &ynow);

    if (xnow < position.x) return 0;
    if (xnow > position.x + width) return 0;
    if (ynow < position.y) return 0;
    if (ynow > position.y + height) return 0;

    Mix_PlayChannel(-1,sound,0);
    SDL_Delay( 200 );

    controlNum  = destNum;
    if (controlNum == 3)
    {
        if (position.x == 70)
        {
            if (player->getlvl(0) > 0) player->changeselect(0);
        }
        if (position.x == 380)
        {
            if (player->getlvl(1) > 0) player->changeselect(1);
        }
        if (position.x == 690)
        {
            if (player->getlvl(2) > 0) player->changeselect(2);
        }
    }
    //std::cout<<controlNum<<std::endl;
    return 1;
}

void button::setDetectArea(int _x, int _y, int _w, int _h){
    position.x = _x;
    position.y = _y;
    height = _h;
    width = _w;
}
