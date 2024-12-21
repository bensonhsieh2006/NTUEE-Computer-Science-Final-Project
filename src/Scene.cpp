#include "Scene.h"
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

Scene::Scene()
{
    //ctor
    backgroundTexture = NULL;
    decorationTexture = NULL;
    extendedTexture1 = NULL;
    extendedTexture2 = NULL;
    extendedTexture3 = NULL;
    extendedTexture4 = NULL;
    extendedTexture5 = NULL;
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

bool Scene::loadText(std::string text, SDL_Color textColor, SDL_Renderer* &r){
    //Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, text.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        textTexture = SDL_CreateTextureFromSurface( r, textSurface );
		if( textSurface == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		/*else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}*/

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

	//Return success
	return textTexture != NULL;
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
    loadPic("imgs/start_button.png", 1, r);
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
    loadText("Skip", textColor, r);
}

void Scene::renderStory(SDL_Renderer* &r, int &controlNum, bool &loaded){
    static float textheight = SCREEN_HEIGHT*1.05;
    setViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderCopyF( r, backgroundTexture, NULL, &viewport );

    setViewport(SCREEN_HEIGHT/2.5,textheight,SCREEN_WIDTH/1.8,SCREEN_HEIGHT/1.1);
    SDL_RenderCopyF( r, decorationTexture, NULL, &viewport );

    setViewport(SCREEN_WIDTH/20*18, SCREEN_HEIGHT/20, SCREEN_WIDTH/15, SCREEN_HEIGHT/15);
    SDL_RenderCopyF( r, textTexture, NULL, &viewport );

    textheight -= SCREEN_HEIGHT/7200.0;
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

void Scene::renderMainpage(SDL_Renderer* &r, int &controlNum, bool &loaded){
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

void Scene::loadStageOne(SDL_Renderer* &r){
    free();

}

void Scene::renderStageOne(SDL_Renderer* &r, int &controlNum, bool &loaded){
    return;
}

void Scene::loadStageTwo(SDL_Renderer* &r){
    free();

}

void Scene::renderStageTwo(SDL_Renderer* &r, int &controlNum, bool &loaded){
    return;
}

void Scene::loadStageThree(SDL_Renderer* &r){
    free();
}

void Scene::renderStageThree(SDL_Renderer* &r, int &controlNum, bool &loaded){
    return;
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
    if(textTexture != NULL){
        SDL_DestroyTexture(textTexture);
        textTexture = NULL;
    }
}
