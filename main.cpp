#include <iostream>
#include <SDL.h>
#include <SDL_bgi.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>

#include "Scene.h"
#include "button.h"

#define BUTTNUM 6

using namespace std;

int SCREEN_WIDTH = 1080;
int SCREEN_HEIGHT = 720;
int controlNum = 0;


enum scene_order{
    OPENING = 0,
    STORY = 1,
    MAINPAGE = 2
};

enum button_name{
    MAIN = 0,
    STAGEONE = 1,
    STAGETWO = 2,
    STAGETHREE = 3,
    GACHA = 4,
    TEAM = 5
};

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}
         //Initialize SDL_mixer
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

		//Create window
		gWindow = SDL_CreateWindow( "game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL)
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

                if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

void close()
{

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
	return;
}

int main( int argc, char* args[] ){
    if (!init())
    {
        cout<<"Initialization failed"<<endl;
    }
    Scene *sceneTexture = NULL;
    sceneTexture = new Scene();
    button **buttons;
    buttons = new button* [BUTTNUM];

    buttons[0] = new button(SCREEN_WIDTH*0.3, SCREEN_WIDTH*0.4, SCREEN_WIDTH/2.5, SCREEN_HEIGHT/4, 1);
    bool loaded = false;
    bool quit = false;
    //Event handler
    SDL_Event e;

    sceneTexture->loadStart(gRenderer);

    while( !quit )
    {
    //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            if(buttons[MAIN]->handle( &e, controlNum )){
                loaded = !loaded;
            }
        }
        //Clear screen
        SDL_RenderClear( gRenderer );
        //Render texture to screen
        switch (controlNum){
            case(OPENING):
                sceneTexture->renderStart(gRenderer); break;
            case(STORY):
                if(!loaded){
                    sceneTexture->loadStory(gRenderer);
                    delete buttons[MAIN];
                    buttons[MAIN] = new button(SCREEN_WIDTH/20*18, SCREEN_HEIGHT/20, SCREEN_WIDTH/15, SCREEN_HEIGHT/15, 2);
                    loaded = true;
                }
                sceneTexture->renderStory(gRenderer, controlNum, loaded);
                break;
            case(MAINPAGE):
                if(!loaded){
                    sceneTexture->loadMainpage(gRenderer);/*
                    delete buttons[MAIN];
                    buttons[STAGEONE] = new button();
                    buttons[STAGETWO] = new button();
                    buttons[STAGETHREE] = new button();
                    buttons[GACHA] = new button();
                    buttons[TEAM] = new button();*/
                    loaded = true;
                }
                sceneTexture->renderMainpage(gRenderer, controlNum, loaded);
                break;
        }
        //Update screen
        SDL_RenderPresent( gRenderer );
    }
    delete sceneTexture;
    /*for (int i=0;i<BUTTNUM;i++)
    {
        delete buttons[i];
    }*/
    delete buttons[0];
    delete [] buttons;
    close();
    return 0;
}
