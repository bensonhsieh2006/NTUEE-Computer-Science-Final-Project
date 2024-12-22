#include "Character.h"

Character::Character(int i): BaseMovingObject(105, 150, 0, 0), id(i)
{
    //ctor
    v = 15;
    posX = 500;
    posY = 300;
    switch(id){
    case(0): maxHp = 200; break;
    case(1): maxHp = 500; break;
    case(2): maxHp = 1500; break;
    }
    hp = maxHp;
    collisionRect = {posX, posY, 105, 150};
}

Character::~Character()
{
    //dtor
}

bool Character::loadPic(SDL_Renderer* &r){
    //Loading success flag
	bool success = true;
    SDL_Surface* loadedSurface=NULL;
    switch (id){
    case (0):
        //Load image at specified path
        loadedSurface = IMG_Load("imgs/character1.png");
        break;
    case (1):
        loadedSurface = IMG_Load("imgs/character2.png");
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

void Character::gotAttacked(int damage){
    hp -= damage;
}
