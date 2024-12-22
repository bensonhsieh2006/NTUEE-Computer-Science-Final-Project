#include "Monster.h"
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

Monster::Monster(int i) :BaseMovingObject(200, 200, 0, 0), monid(i)
{
    //ctor
    posX = SCREEN_WIDTH/2-100;
    posY = SCREEN_HEIGHT/2-100;
    hp = 100;
    maxHp = 100;
    collisionRect = {posX, posY, 200, 200};
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
    case (2):
        loadedSurface = IMG_Load("imgs/monster2.png");
        break;
    case (3):
        loadedSurface = IMG_Load("imgs/monster3.png");
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


void Monster::update_pos(){
    srand(time(0));
    vX = rand()%5-2;
    vY = rand()%5-2;
    move();
}

void Monster::gotAttacked(int damage){
    hp -= damage;
}
