#include "Bullet.h"

Bullet::Bullet(int bid, int _char_posx, int _char_posy, int _shoot_dir): BaseMovingObject(30, 30, 4*_shoot_dir, 0) // shoot_dir( +x: 1, -x: -1 )
{
    //ctor
    id = bid;
    damage = 10;
    posX = _char_posx;
    posY = _char_posy;
    shoot_dir = _shoot_dir;
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

    case (3):
        if (shoot_dir == 1) loadedSurface = IMG_Load("imgs/bullet2.png");
        else loadedSurface = IMG_Load("imgs/bullet2_rev.png");
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
