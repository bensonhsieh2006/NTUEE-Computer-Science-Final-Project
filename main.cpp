#include <iostream>
#include <SDL.h>
#include <SDL_bgi.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>

#include "Scene.h"
#include "button.h"
#include "GamePlay.h"

#define BUTTMAX 5

using namespace std;

int SCREEN_WIDTH = 1080;
int SCREEN_HEIGHT = 720;
int controlNum = 0;


enum scene_order{
    OPENING = 0,
    STORY = 1,
    MAINPAGE = 2,
    TEAM = 3,
    STAGE1 = 4,
    STAGE2 = 5,
    STAGE3 = 6,
    SCENEGACHA = 7,
    GACHAX1 = 8,
    GACHAX11 = 9
};

enum button_name{
    MAIN = 0,      //main, team
    STAGEONE = 1,
    STAGETWO = 2,
    STAGETHREE = 3,
    GACHA = 4,
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
    int buttnow = 1;
    button **buttons;
    buttons = new button* [BUTTMAX];

    buttons[MAIN] = new button(SCREEN_WIDTH*0.3, SCREEN_WIDTH*0.4, SCREEN_WIDTH/2.5, SCREEN_HEIGHT/4, 1);
    bool loaded = false;
    bool quit = false;
    bool hasgacha = false;

    GamePlay *gp = NULL;
    int diamondnum = 9999;

    //Event handler
    SDL_Event e;

    sceneTexture->loadStart(gRenderer);
    loaded = true;

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
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                for (int i=0;i<buttnow;i++)
                {
                    if(buttons[i]->handle( controlNum )){
                    loaded = !loaded;
                    }
                }
            }

            if(gp != NULL){
                gp->handle_keyboard(e);
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
                    sceneTexture->loadMainpage(gRenderer);
                    delete buttons[MAIN];
                    buttons[MAIN] = new button(0, 0, SCREEN_WIDTH/10, SCREEN_WIDTH/10, TEAM); //team
                    buttons[STAGEONE] = new button(SCREEN_WIDTH/5, SCREEN_HEIGHT/2.5, SCREEN_WIDTH/5, SCREEN_WIDTH/5, STAGE1);
                    buttons[STAGETWO] = new button(SCREEN_WIDTH/5*2, SCREEN_HEIGHT/2.5, SCREEN_WIDTH/5, SCREEN_WIDTH/5, STAGE2);
                    buttons[STAGETHREE] = new button(SCREEN_WIDTH/5*3, SCREEN_HEIGHT/2.5, SCREEN_WIDTH/5, SCREEN_WIDTH/5, STAGE3);
                    buttons[GACHA] = new button(SCREEN_WIDTH/10, 0, SCREEN_WIDTH/10, SCREEN_WIDTH/10, SCENEGACHA);
                    buttnow = 5;
                    loaded = true;
                }
                sceneTexture->renderMainpage(gRenderer);
                break;
            case(STAGE1):
                if(!loaded)
                {
                    for (int i=0;i<buttnow;i++)
                    {
                        if (buttons[i] != NULL)
                        {
                            delete buttons[i];
                            buttons[i] = NULL;
                        }
                    }
                    buttnow = 0;
                    sceneTexture->loadStageOne(gRenderer);

                    gp = new GamePlay(0, 1); //characterID, stage
                    gp->load(gRenderer);
                    loaded = true;
                }
                sceneTexture->renderStageOne(gRenderer);
                gp->render(gRenderer);
                break;

            case(STAGE2):
                if(!loaded)
                {
                    for (int i=0;i<buttnow;i++)
                    {
                        if (buttons[i] != NULL)
                        {
                            delete buttons[i];
                            buttons[i] = NULL;
                        }
                    }
                    buttnow = 0;
                    sceneTexture->loadStageTwo(gRenderer);

                    gp = new GamePlay(0, 2); //characterID, stage
                    gp->load(gRenderer);
                    loaded = true;
                }
                sceneTexture->renderStageTwo(gRenderer);
                gp->render(gRenderer);
                break;

            case(STAGE3):
                if(!loaded)
                {
                    for (int i=0;i<buttnow;i++)
                    {
                        if (buttons[i] != NULL)
                        {
                            delete buttons[i];
                            buttons[i] = NULL;
                        }
                    }
                    buttnow = 0;
                    sceneTexture->loadStageThree(gRenderer);

                    gp = new GamePlay(0, 3); //characterID, stage
                    gp->load(gRenderer);
                    loaded = true;
                }
                sceneTexture->renderStageThree(gRenderer);
                gp->render(gRenderer);
                break;

            case (SCENEGACHA):
                if(!loaded)
                {
                    for (int i=0;i<buttnow;i++)
                    {
                        if (buttons[i] != NULL)
                        {
                            delete buttons[i];
                            buttons[i] = NULL;
                        }
                    }
                    buttons[MAIN] = new button(0, 0, SCREEN_WIDTH/10, SCREEN_WIDTH/10, MAINPAGE);
                    buttons[STAGEONE] = new button(SCREEN_WIDTH/4, SCREEN_HEIGHT/5*3.2, SCREEN_WIDTH/4, SCREEN_WIDTH/5, GACHAX1);
                    buttons[STAGETWO] = new button(SCREEN_WIDTH/4*2, SCREEN_HEIGHT/5*3.2, SCREEN_WIDTH/4, SCREEN_WIDTH/5, GACHAX11);
                    buttnow = 3;
                    sceneTexture->loadGacha(gRenderer, diamondnum);
                    hasgacha = false;
                    loaded = true;
                }
                sceneTexture->renderGacha(gRenderer, diamondnum);
                break;

            case (GACHAX1):
                if(!loaded)
                {
                    for (int i=0;i<buttnow;i++)
                    {
                        if (buttons[i] != NULL)
                        {
                            delete buttons[i];
                            buttons[i] = NULL;
                        }
                    }
                    buttons[MAIN] = new button(0, 0, SCREEN_WIDTH, SCREEN_WIDTH, SCENEGACHA);
                    buttnow = 1;
                    sceneTexture->loadGachaX1(gRenderer);
                    loaded = true;
                }
                sceneTexture->renderGachaX1(gRenderer, diamondnum, hasgacha);
                if (!hasgacha) hasgacha = true;
                break;
            case (GACHAX11):
                if(!loaded)
                {
                    for (int i=0;i<buttnow;i++)
                    {
                        if (buttons[i] != NULL)
                        {
                            delete buttons[i];
                            buttons[i] = NULL;
                        }
                    }
                    buttons[MAIN] = new button(0, 0, SCREEN_WIDTH, SCREEN_WIDTH, SCENEGACHA);
                    buttnow = 1;
                    sceneTexture->loadGachaX11(gRenderer);
                    loaded = true;
                }
                sceneTexture->renderGachaX11(gRenderer, diamondnum);
                break;
        }
        //Update screen
        SDL_RenderPresent( gRenderer );
    }
    delete sceneTexture;
    for (int i=0;i<buttnow;i++)
    {
        delete buttons[i];
    }
    delete [] buttons;
    close();
    return 0;
}
