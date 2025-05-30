#include "Bullet.h"

Bullet::Bullet(int bid, int _char_posx, int _char_posy, int _shoot_dir, Backpack* player): BaseMovingObject(30, 30, 4*(bid%3+1)*_shoot_dir, 0), id(bid), shoot_dir(_shoot_dir) // shoot_dir( +x: 1, -x: -1 )
{
    //ctor
    switch(id){
        case(0): damage = 5+5*player->getlvl(0); break;
        case(1): damage = 40+10*player->getlvl(1); break;
        case(2): damage = 80+20*player->getlvl(2); break;
        case(3): damage = 20; break;
        case(4): damage = 100; break;
        case(5): damage = 400; break;
    }
    posX = _char_posx;
    posY = _char_posy;
    collisionRect = {posX, posY, 30, 30};
}

Bullet::~Bullet()
{
    //dtor
}


bool Bullet::loadPic(SDL_Renderer* &r){
    //Loading success flag
	bool success = true;
    SDL_Surface* loadedSurface=NULL;
    switch (id){
    case (0):
        if (shoot_dir == 1) loadedSurface = IMG_Load("imgs/bullet1.png");
        else loadedSurface = IMG_Load("imgs/bullet1_rev.png");
        break;
    case (1):
        if (shoot_dir == 1) loadedSurface = IMG_Load("imgs/bullet2.png");
        else loadedSurface = IMG_Load("imgs/bullet2_rev.png");
        break;
    case (2):
        if (shoot_dir == 1) loadedSurface = IMG_Load("imgs/bullet3.png");
        else loadedSurface = IMG_Load("imgs/bullet3_rev.png");
        break;

    case (3):
        if (shoot_dir == 1) loadedSurface = IMG_Load("imgs/bullet4.png");
        else loadedSurface = IMG_Load("imgs/bullet4_rev.png");
        break;
    case (4):
        if (shoot_dir == 1) loadedSurface = IMG_Load("imgs/bullet5.png");
        else loadedSurface = IMG_Load("imgs/bullet5_rev.png");
        break;
    case (5):
        if (shoot_dir == 1) loadedSurface = IMG_Load("imgs/bullet6.png");
        else loadedSurface = IMG_Load("imgs/bullet6_rev.png");
        break;
    }


	if( loadedSurface == NULL )
	{
		printf( "Unable to load image ! SDL_image Error: %s\n", IMG_GetError() );
	}
	else{
        cTexture = SDL_CreateTextureFromSurface( r, loadedSurface );
        if( cTexture == NULL )
        {
            printf( "Unable to create texture from ! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
	}

    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );

    return success;
}
