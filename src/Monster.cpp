#include "Monster.h"

Monster::Monster(int i) :BaseMovingObject(200, 200, 0, 0), monid(i)
{
    //ctor
    posX = 300;
    posY = 0;
}

Monster::~Monster()
{
    //dtor
}

bool Monster::loadPic(SDL_Renderer* &r)
{
    //Loading success flag
	bool success = true;
    SDL_Surface* loadedSurface=NULL;
    switch (monid){
    case (1):
        //Load image at specified path
        loadedSurface = IMG_Load("imgs/monster1.png");
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
