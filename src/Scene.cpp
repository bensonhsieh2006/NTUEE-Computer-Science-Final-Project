#include "Scene.h"
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

Scene::Scene(): poll(CharacterPoll(100)), player(Backpack())
{
    //ctor
    backgroundTexture = NULL;
    decorationTexture = NULL;
    extendedTexture1 = NULL;
    extendedTexture2 = NULL;
    extendedTexture3 = NULL;
    extendedTexture4 = NULL;
    extendedTexture5 = NULL;
    textTexture1 = NULL;
    textTexture2 = NULL;
    textTexture3 = NULL;
    textTexture4 = NULL;
    gFont = TTF_OpenFont( "fonts/Pixel Game.otf", 40 );
	if( gFont == NULL )
	{
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
	}
    viewport.x = 0;
    viewport.y = 0;
    viewport.w = 0;
    viewport.h = 0;
}

Scene::~Scene()
{
    free();
    TTF_CloseFont(gFont);
    gFont = NULL;
}


bool Scene::loadPic(std::string c,int textureID, SDL_Renderer* &gRenderer)
{
    //Loading success flag
	bool success = true;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( c.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", c.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
		switch(textureID){
            case(0):
                backgroundTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
                if( backgroundTexture == NULL )
                {
                    printf( "Unable to create texture from %s! SDL Error: %s\n", c.c_str(), SDL_GetError() );
                    success = false;
                }
                break;
            case(1):
                decorationTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
                if( decorationTexture == NULL )
                {
                    printf( "Unable to create texture from %s! SDL Error: %s\n", c.c_str(), SDL_GetError() );
                    success = false;
                }
                break;
            case(2):
                extendedTexture1 = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
                if( extendedTexture1 == NULL )
                {
                    printf( "Unable to create texture from %s! SDL Error: %s\n", c.c_str(), SDL_GetError() );
                    success = false;
                }
                break;
            case(3):
                extendedTexture2 = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
                if( extendedTexture2 == NULL )
                {
                    printf( "Unable to create texture from %s! SDL Error: %s\n", c.c_str(), SDL_GetError() );
                    success = false;
                }
                break;
            case(4):
                extendedTexture3 = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
                if( extendedTexture3 == NULL )
                {
                    printf( "Unable to create texture from %s! SDL Error: %s\n", c.c_str(), SDL_GetError() );
                    success = false;
                }
                break;
            case(5):
                extendedTexture4 = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
                if( extendedTexture4 == NULL )
                {
                    printf( "Unable to create texture from %s! SDL Error: %s\n", c.c_str(), SDL_GetError() );
                    success = false;
                }
                break;
            case(6):
                extendedTexture5 = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
                if( extendedTexture5 == NULL )
                {
                    printf( "Unable to create texture from %s! SDL Error: %s\n", c.c_str(), SDL_GetError() );
                    success = false;
                }
                break;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}


	return success;
}

bool Scene::loadText(std::string text, int textID, SDL_Color textColor, SDL_Renderer* &r){
    //Render text surface
    bool success = true;
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, text.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
		switch (textID){
        case(0):
            textTexture1 = SDL_CreateTextureFromSurface( r, textSurface );
            if( textTexture1 == NULL )
            {
                printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            break;

        case(1):
            textTexture2 = SDL_CreateTextureFromSurface( r, textSurface );
            if( textTexture2 == NULL )
            {
                printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            break;

        case(2):
            textTexture3 = SDL_CreateTextureFromSurface( r, textSurface );
            if( textTexture3 == NULL )
            {
                printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            break;
        case(3):
            textTexture4 = SDL_CreateTextureFromSurface( r, textSurface );
            if( textTexture4 == NULL )
            {
                printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            break;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

	//Return success
	return success;
}

void Scene::setViewport(float _x, float _y, float _w, float _h){
    viewport.x = _x;
    viewport.y = _y;
    viewport.w = _w;
    viewport.h = _h;
}

//t1: Texture for opening background; t2: for start button
void Scene::loadStart(SDL_Renderer* &r)
{
    loadPic("imgs/opening_background.jpg", 0, r);
    loadPic("imgs/play.png", 1, r);
}

void Scene::renderStart(SDL_Renderer* &r){

    setViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderCopyF( r, backgroundTexture, NULL, &viewport );

    setViewport(SCREEN_WIDTH*0.3, SCREEN_WIDTH*0.4, SCREEN_WIDTH/2.5, SCREEN_HEIGHT/4);
    SDL_RenderCopyF( r, decorationTexture, NULL, &viewport );

}

void Scene::loadStory(SDL_Renderer* &r){
    free();
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
    setViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    loadPic("imgs/opening_background.jpg",0,r);
    loadPic("imgs/story_script.png", 1, r);
    loadText("Skip", 0, textColor, r);
}

void Scene::renderStory(SDL_Renderer* &r, int &controlNum, bool &loaded){
    static float textheight = SCREEN_HEIGHT*1.05;
    setViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderCopyF( r, backgroundTexture, NULL, &viewport );

    setViewport(SCREEN_HEIGHT/2.5,textheight,SCREEN_WIDTH/1.8,SCREEN_HEIGHT/1.1);
    SDL_RenderCopyF( r, decorationTexture, NULL, &viewport );

    setViewport(SCREEN_WIDTH/20*18, SCREEN_HEIGHT/20, SCREEN_WIDTH/15, SCREEN_HEIGHT/15);
    SDL_RenderCopyF( r, textTexture1, NULL, &viewport );

    textheight -= SCREEN_HEIGHT/1000.0;
//    std::cout<<textheight<<std::endl;
    if (textheight < -900)
    {
        controlNum = 2;
        loaded = !loaded;
    }
}

void Scene::loadMainpage(SDL_Renderer* &r){
    free();
    loadPic("imgs/mainpage.png",0,r);
    loadPic("imgs/homebutton.png",1,r);
    loadPic("imgs/gachabutton1.png",2,r);
    loadPic("imgs/stage01.png",3,r);
    loadPic("imgs/stage02.png",4,r);
    loadPic("imgs/stage03.png",5,r);
}

void Scene::renderMainpage(SDL_Renderer* &r){
    setViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderCopyF( r, backgroundTexture, NULL, &viewport );

    setViewport(0, 0, SCREEN_WIDTH/10, SCREEN_WIDTH/10);
    SDL_RenderCopyF( r, decorationTexture, NULL, &viewport );

    setViewport(SCREEN_WIDTH/10, 0, SCREEN_WIDTH/10, SCREEN_WIDTH/10);
    SDL_RenderCopyF( r, extendedTexture1, NULL, &viewport );

    setViewport(SCREEN_WIDTH/5, SCREEN_HEIGHT/2.5, SCREEN_WIDTH/5, SCREEN_WIDTH/5);
    SDL_RenderCopyF( r, extendedTexture2, NULL, &viewport );

    setViewport(SCREEN_WIDTH*2/5, SCREEN_HEIGHT/2.5, SCREEN_WIDTH/5, SCREEN_WIDTH/5);
    SDL_RenderCopyF( r, extendedTexture3, NULL, &viewport );

    setViewport(SCREEN_WIDTH*3/5, SCREEN_HEIGHT/2.5, SCREEN_WIDTH/5, SCREEN_WIDTH/5);
    SDL_RenderCopyF( r, extendedTexture4, NULL, &viewport );
}

void Scene::loadTeampage(SDL_Renderer* &r)
{
    free();
    loadPic("imgs/teambackground.png",0,r);
    loadPic("imgs/character1.png", 1, r);
    loadPic("imgs/character1.png", 2, r);
    loadPic("imgs/character1.png", 3, r);
    loadPic("imgs/return.png", 4, r);
    loadPic("imgs/black_star.png", 5, r);
    loadPic("imgs/gold_star.png", 6, r);
}

void Scene::renderTeampage(SDL_Renderer* &r)
{
    setViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderCopyF( r, backgroundTexture, NULL, &viewport );

    setViewport(70, SCREEN_HEIGHT/5, 260, 400);
    SDL_RenderCopyF(r, decorationTexture, NULL, &viewport);
    for (int i=0;i<5;i++)
    {
        setViewport(70+55*i, SCREEN_HEIGHT/5*4-40, 50, 50);
        SDL_RenderCopyF(r, extendedTexture4, NULL, &viewport);
    }

    setViewport(380, SCREEN_HEIGHT/5, 260, 400);
    SDL_RenderCopyF(r, extendedTexture1, NULL, &viewport);
    for (int i=0;i<5;i++)
    {
        setViewport(380+55*i, SCREEN_HEIGHT/5*4-40, 50, 50);
        SDL_RenderCopyF(r, extendedTexture4, NULL, &viewport);
    }

    setViewport(690, SCREEN_HEIGHT/5, 260, 400);
    SDL_RenderCopyF(r, extendedTexture2, NULL, &viewport);
    for (int i=0;i<5;i++)
    {
        setViewport(690+55*i, SCREEN_HEIGHT/5*4-40, 50, 50);
        SDL_RenderCopyF(r, extendedTexture4, NULL, &viewport);
    }

    setViewport(0, 0, SCREEN_WIDTH/10, SCREEN_WIDTH/10);
    SDL_RenderCopyF(r, extendedTexture3, NULL, &viewport);


}

void Scene::loadStageOne(SDL_Renderer* &r){
    free();
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
    loadPic("imgs/stage1background.png",0,r);
    loadPic("imgs/pause.png", 1, r);
    loadPic("imgs/play.png", 2, r);
    loadText("PAUSED", 0, textColor, r);
    loadText("YOU WON!", 1, textColor, r);
    loadText("YOU LOST!", 2, textColor, r);
}


void Scene::renderStageOne(SDL_Renderer* &r){
    setViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderCopyF( r, backgroundTexture, NULL, &viewport );
    setViewport(SCREEN_WIDTH*2/5, SCREEN_HEIGHT/70, SCREEN_WIDTH*1/5, SCREEN_HEIGHT/20);
    SDL_RenderCopyF( r, decorationTexture, NULL, &viewport );

    return;
}

void Scene::loadStageTwo(SDL_Renderer* &r){
    free();
    loadPic("imgs/stage2background.png",0,r);
}

void Scene::renderStageTwo(SDL_Renderer* &r){
    setViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderCopyF( r, backgroundTexture, NULL, &viewport );
    return;
}

void Scene::loadStageThree(SDL_Renderer* &r){
    free();
    loadPic("imgs/stage3background.png",0,r);
}

void Scene::renderStageThree(SDL_Renderer* &r){
    setViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderCopyF( r, backgroundTexture, NULL, &viewport );
    return;
}

void Scene::loadGacha(SDL_Renderer* &r, int Dnum)
{
    free();
    SDL_Color textColor = { 0, 0, 0 };
    loadPic("imgs/mainpage.png", 0, r);
    loadPic("imgs/diamondnum.png", 1, r);
    loadPic("imgs/x1button.png", 2, r);
    loadPic("imgs/x11button.png", 3, r);
    loadPic("imgs/return.png", 4, r);
    loadText(std::to_string(Dnum), 0, textColor, r);
}

void Scene::renderGacha(SDL_Renderer* &r, int Dnum)
{
    setViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderCopyF(r, backgroundTexture, NULL, &viewport);

    setViewport(SCREEN_WIDTH/5*3, 0, SCREEN_WIDTH/5*2, SCREEN_HEIGHT/8);
    SDL_RenderCopyF(r, decorationTexture, NULL, &viewport);

    setViewport(SCREEN_WIDTH/4, SCREEN_HEIGHT/5*3.2, SCREEN_WIDTH/4, SCREEN_WIDTH/5);
    SDL_RenderCopyF(r, extendedTexture1, NULL, &viewport);

    setViewport(SCREEN_WIDTH/4*2, SCREEN_HEIGHT/5*3.2, SCREEN_WIDTH/4, SCREEN_WIDTH/5);
    SDL_RenderCopyF(r, extendedTexture2, NULL, &viewport);

    setViewport(0, 0, SCREEN_WIDTH/10, SCREEN_WIDTH/10);
    SDL_RenderCopyF(r, extendedTexture3, NULL, &viewport);

    setViewport(SCREEN_WIDTH/20*15, 5, 25*std::floor(log10(Dnum)+1), SCREEN_HEIGHT/9);
    SDL_RenderCopyF(r, textTexture1, NULL, &viewport);
}

void Scene::loadGachaX1(SDL_Renderer* &r)
{
    free();
    SDL_Color textColor = { 0xFF, 0, 0 };
    loadPic("imgs/mainpage.png", 0, r);
    loadPic("imgs/no money.png", 1, r);
    loadPic("imgs/character1.png", 2, r);
    loadPic("imgs/character1.png", 3, r);
    loadPic("imgs/character1.png", 4, r);
    loadText("You got:", 0, textColor, r);
    loadText("X1", 1, textColor, r);
}

void Scene::renderGachaX1(SDL_Renderer* &r, int &Dnum, bool &hasgacha)
{
    setViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderCopyF(r, backgroundTexture, NULL, &viewport);

    if (Dnum < 100 )
    {
        setViewport(SCREEN_WIDTH/6, SCREEN_HEIGHT/6, SCREEN_WIDTH/3*2, SCREEN_HEIGHT/3*2);
        SDL_RenderCopyF(r, decorationTexture, NULL, &viewport);
        return;
    }
    else if (!hasgacha)
    {
        poll.getone();
        Dnum -= 100;
        hasgacha = true;
    }
    setViewport(SCREEN_WIDTH/2.5-40, SCREEN_HEIGHT/5+10, 260, 400);
    //std::cout<<got<<std::endl;
    switch (poll.onegot)
    {
    case (0):
        SDL_RenderCopyF(r, extendedTexture1, NULL, &viewport); break;
    case (1):
        SDL_RenderCopyF(r, extendedTexture2, NULL, &viewport); break;
    case (2):
        SDL_RenderCopyF(r, extendedTexture3, NULL, &viewport); break;
    }
    setViewport(SCREEN_WIDTH/2.5-10, SCREEN_HEIGHT/12, 160, 120);
    SDL_RenderCopyF(r, textTexture1, NULL, &viewport);

    setViewport(SCREEN_WIDTH/2.4, SCREEN_HEIGHT/4*3+20, 130, 100);
    SDL_RenderCopyF(r, textTexture2, NULL, &viewport);

}

void Scene::loadGachaX11(SDL_Renderer* &r, int &Dnum, bool &hasgacha)
{
    free();
    SDL_Color textColor = { 0xFF, 0, 0 };
    loadPic("imgs/mainpage.png", 0, r);
    loadPic("imgs/no money.png", 1, r);
    loadPic("imgs/character1.png", 2, r);
    loadPic("imgs/character1.png", 3, r);
    loadPic("imgs/character1.png", 4, r);
    loadText("You got:", 0, textColor, r);
    if (!hasgacha && Dnum >= 1000)
    {
        poll.get11();
        Dnum -= 1000;
        hasgacha = true;
        loadText("X"+std::to_string(poll.elevengot[0]), 1, textColor, r);
        loadText("X"+std::to_string(poll.elevengot[1]), 2, textColor, r);
        loadText("X"+std::to_string(poll.elevengot[2]), 3, textColor, r);
    }
}

void Scene::renderGachaX11(SDL_Renderer* &r, int &Dnum, bool &hasgacha)
{
    setViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderCopyF(r, backgroundTexture, NULL, &viewport);
    SDL_Color textColor = { 0xFF, 0, 0 };
    if (Dnum < 1000)
    {
        setViewport(SCREEN_WIDTH/6, SCREEN_HEIGHT/6, SCREEN_WIDTH/3*2, SCREEN_HEIGHT/3*2);
        SDL_RenderCopyF(r, decorationTexture, NULL, &viewport);
        return;
    }
    setViewport(SCREEN_WIDTH/2.5-10, SCREEN_HEIGHT/12, 160, 120);
    SDL_RenderCopyF(r, textTexture1, NULL, &viewport);

    setViewport(SCREEN_WIDTH/8, SCREEN_HEIGHT/5+10, 260, 400);
    SDL_RenderCopyF(r, extendedTexture1, NULL, &viewport);
    setViewport(SCREEN_WIDTH/2.4-250, SCREEN_HEIGHT/4*3+20, 130, 100);
    SDL_RenderCopyF(r, textTexture2, NULL, &viewport);

    setViewport(SCREEN_WIDTH/2.5-40, SCREEN_HEIGHT/5+10, 260, 400);
    SDL_RenderCopyF(r, extendedTexture2, NULL, &viewport);
    setViewport(SCREEN_WIDTH/2.4, SCREEN_HEIGHT/4*3+20, 130, 100);
    SDL_RenderCopyF(r, textTexture3, NULL, &viewport);

    setViewport(SCREEN_WIDTH/5*3, SCREEN_HEIGHT/5+10, 260, 400);
    SDL_RenderCopyF(r, extendedTexture3, NULL, &viewport);
    setViewport(SCREEN_WIDTH/2.4+250, SCREEN_HEIGHT/4*3+20, 130, 100);
    SDL_RenderCopyF(r, textTexture4, NULL, &viewport);

}

void Scene::free(){
    if(backgroundTexture != NULL){
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = NULL;
    }
    if(decorationTexture != NULL){
        SDL_DestroyTexture(decorationTexture);
        decorationTexture = NULL;
    }
    if(extendedTexture1 != NULL){
        SDL_DestroyTexture(extendedTexture1);
        extendedTexture1 = NULL;
    }
    if(extendedTexture2 != NULL){
        SDL_DestroyTexture(extendedTexture2);
        extendedTexture2 = NULL;
    }
    if(extendedTexture3 != NULL){
        SDL_DestroyTexture(extendedTexture3);
        extendedTexture3 = NULL;
    }
    if(extendedTexture4 != NULL){
        SDL_DestroyTexture(extendedTexture4);
        extendedTexture4 = NULL;
    }
    if(extendedTexture5 != NULL){
        SDL_DestroyTexture(extendedTexture5);
        extendedTexture5 = NULL;
    }
    if(textTexture1 != NULL){
        SDL_DestroyTexture(textTexture1);
        textTexture1 = NULL;
    }
    if(textTexture2 != NULL){
        SDL_DestroyTexture(textTexture2);
        textTexture2 = NULL;
    }
    if(textTexture3 != NULL){
        SDL_DestroyTexture(textTexture3);
        textTexture3 = NULL;
    }
    if(textTexture4 != NULL){
        SDL_DestroyTexture(textTexture3);
        textTexture4 = NULL;
    }
}
