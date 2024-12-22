#include "Monster.h"
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

Monster::Monster(int i) :BaseMovingObject(200, 200, 0, 0), monid(i)
{
    //ctor
    posX = SCREEN_WIDTH/2-100;
    posY = SCREEN_HEIGHT/2-100;
    switch(monid){
    case(0): maxHp = 300; break;
    case(1): maxHp = 1000; break;
    case(2): maxHp = 4000; break;
    }
    hp = maxHp;
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
    case (0):
        //Load image at specified path
        loadedSurface = IMG_Load("imgs/monster1.png");
        break;
    case (1):
        loadedSurface = IMG_Load("imgs/monster2.png");
        break;
    case (2):
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


void Monster::update_pos(int &count_mon_move){
    if (count_mon_move > 70){
        srand(time(0));

        switch (monid){
        case(0):
            vX = rand()%9-4;
            vY = rand()%9-4;
            break;
        case(1):
            vX = rand()%19-9;
            vY = rand()%19-9;
            break;
        case(2):
            vX = rand()%29-14;
            vY = rand()%29-14;
            break;
        }
        count_mon_move = 0;
    }

    if(move()){
        vX = -vX;
        vY = -vY;
    }
}

void Monster::gotAttacked(int damage){
    hp -= damage;
}
