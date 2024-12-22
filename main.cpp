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
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720
#define SCREEN_FPS 60
#define SCREEN_TICK_PER_FRAME 1000 / SCREEN_FPS

using namespace std;


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
    bool loaded = false, pauseloaded = false, continued = false;
    bool quit = false;
    bool hasgacha = false;
    bool gameover = false, won = false, paused = false;

    GamePlay *gp = NULL;
    int diamondnum = 999;
    Uint32 cur_tick, frame_tick;
    int count_cd = 0, count_mon_shoot = 0, count_mon_move = 0;
    int controlNum = 0;

    //Event handler
    SDL_Event e;

    sceneTexture->loadStart(gRenderer);
    loaded = true;

    while( !quit )
    {
        count_cd++;
        count_mon_shoot++;
        count_mon_move++;
        cur_tick = SDL_GetTicks();
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
                if( (controlNum >= STAGE1) && (controlNum <= STAGE3) && (gameover == false)){

                    if(paused){
                        if(buttons[1]->handle(controlNum)) paused = false; continued = true; pauseloaded = false;
                    }

                    if(buttons[MAIN]->handle( controlNum )) paused = true;

                }
                else{
                    for (int i=0;i<buttnow;i++) if(buttons[i]->handle( controlNum ))loaded = !loaded;
                }
            }

            if(gp != NULL && !gameover && !paused){
                gp->handle_keyboard(e, gRenderer, count_cd);
            }
        }

        if ((gp != NULL) && (!gameover) && (!paused))
        {
            gp->handle_move(count_mon_shoot, count_mon_move, gRenderer, gameover, won);
        }


        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
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
                    buttons[MAIN] = new button(SCREEN_WIDTH*2/5, SCREEN_HEIGHT/70, SCREEN_WIDTH*1/5, SCREEN_HEIGHT/20, STAGE1);
                    buttnow = 1;
                    sceneTexture->loadStageOne(gRenderer);

                    gp = new GamePlay(0, 1); //characterID, stage
                    gp->load(gRenderer);
                    loaded = true;
                    gameover = false;
                }

                if (paused && !pauseloaded){
                    continued = false;
                    buttons[1] = new button(SCREEN_WIDTH*3/10, SCREEN_HEIGHT*3/5, SCREEN_WIDTH*2/5, SCREEN_HEIGHT/10, STAGE1);
                    buttnow = 2;
                    pauseloaded = true;
                }

                sceneTexture->renderStageOne(gRenderer, gameover);
                gp->render(gRenderer, paused);

                if (paused){
                    sceneTexture->setViewport(SCREEN_WIDTH*3/10, SCREEN_HEIGHT*3/5, SCREEN_WIDTH*2/5, SCREEN_HEIGHT/10);
                    SDL_RenderCopyF( gRenderer, sceneTexture->getExtendedTexture2(), NULL, &(sceneTexture->getViewportRect()) );
                    sceneTexture->setViewport(SCREEN_WIDTH*3/10, SCREEN_HEIGHT*2/5, SCREEN_WIDTH*2/5, SCREEN_HEIGHT/10);
                    SDL_RenderCopyF( gRenderer, sceneTexture->getTextTexture1(), NULL, &(sceneTexture->getViewportRect()) );
                }

                //cout << won << endl;
                if (gameover && won){
                    sceneTexture->setViewport(SCREEN_WIDTH*3/10, SCREEN_HEIGHT*2/5, SCREEN_WIDTH*2/5, SCREEN_HEIGHT/10);
                    SDL_RenderCopyF( gRenderer, sceneTexture->getTextTexture2(), NULL, &(sceneTexture->getViewportRect()) );
                    delete buttons[MAIN];
                    buttons[MAIN] = NULL;
                    buttons[MAIN] = new button(SCREEN_WIDTH/50, SCREEN_HEIGHT*8/9, SCREEN_WIDTH/10, SCREEN_HEIGHT/10, MAINPAGE);
                }
                else if(gameover && !won){
                    sceneTexture->setViewport(SCREEN_WIDTH*3/10, SCREEN_HEIGHT*2/5, SCREEN_WIDTH*2/5, SCREEN_HEIGHT/6);
                    SDL_RenderCopyF( gRenderer, sceneTexture->getExtendedTexture1(), NULL, &(sceneTexture->getViewportRect()) );
                    delete buttons[MAIN];
                    buttons[MAIN] = NULL;
                    buttons[MAIN] = new button(SCREEN_WIDTH/50, SCREEN_HEIGHT*8/9, SCREEN_WIDTH/10, SCREEN_HEIGHT/10, MAINPAGE);
                }


                if (continued){
                    delete buttons[1];
                    buttons[1] = NULL;
                    buttnow = 1;
                    continued = false;
                }
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
                    buttons[MAIN] = new button(SCREEN_WIDTH*2/5, SCREEN_HEIGHT/70, SCREEN_WIDTH*1/5, SCREEN_HEIGHT/20, STAGE1);
                    buttnow = 1;
                    sceneTexture->loadStageTwo(gRenderer);

                    gp = new GamePlay(0, 2); //characterID, stage
                    gp->load(gRenderer);
                    loaded = true;
                    gameover = false;
                }

                if (paused && !pauseloaded){
                    continued = false;
                    buttons[1] = new button(SCREEN_WIDTH*3/10, SCREEN_HEIGHT*3/5, SCREEN_WIDTH*2/5, SCREEN_HEIGHT/10, STAGE1);
                    buttnow = 2;
                    pauseloaded = true;
                }

                sceneTexture->renderStageTwo(gRenderer, gameover);
                gp->render(gRenderer, paused);

                if (paused){
                    sceneTexture->setViewport(SCREEN_WIDTH*3/10, SCREEN_HEIGHT*3/5, SCREEN_WIDTH*2/5, SCREEN_HEIGHT/10);
                    SDL_RenderCopyF( gRenderer, sceneTexture->getExtendedTexture2(), NULL, &(sceneTexture->getViewportRect()) );
                    sceneTexture->setViewport(SCREEN_WIDTH*3/10, SCREEN_HEIGHT*2/5, SCREEN_WIDTH*2/5, SCREEN_HEIGHT/10);
                    SDL_RenderCopyF( gRenderer, sceneTexture->getTextTexture1(), NULL, &(sceneTexture->getViewportRect()) );
                }

                //cout << won << endl;
                if (gameover && won){
                    sceneTexture->setViewport(SCREEN_WIDTH*3/10, SCREEN_HEIGHT*2/5, SCREEN_WIDTH*2/5, SCREEN_HEIGHT/10);
                    SDL_RenderCopyF( gRenderer, sceneTexture->getTextTexture2(), NULL, &(sceneTexture->getViewportRect()) );
                    delete buttons[MAIN];
                    buttons[MAIN] = NULL;
                    buttons[MAIN] = new button(SCREEN_WIDTH/50, SCREEN_HEIGHT*8/9, SCREEN_WIDTH/10, SCREEN_HEIGHT/10, MAINPAGE);
                }
                else if(gameover && !won){
                    sceneTexture->setViewport(SCREEN_WIDTH*3/10, SCREEN_HEIGHT*2/5, SCREEN_WIDTH*2/5, SCREEN_HEIGHT/6);
                    SDL_RenderCopyF( gRenderer, sceneTexture->getExtendedTexture1(), NULL, &(sceneTexture->getViewportRect()) );
                    delete buttons[MAIN];
                    buttons[MAIN] = NULL;
                    buttons[MAIN] = new button(SCREEN_WIDTH/50, SCREEN_HEIGHT*8/9, SCREEN_WIDTH/10, SCREEN_HEIGHT/10, MAINPAGE);
                }


                if (continued){
                    delete buttons[1];
                    buttons[1] = NULL;
                    buttnow = 1;
                    continued = false;
                }
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
                    buttons[MAIN] = new button(SCREEN_WIDTH*2/5, SCREEN_HEIGHT/70, SCREEN_WIDTH*1/5, SCREEN_HEIGHT/20, STAGE1);
                    buttnow = 1;
                    sceneTexture->loadStageThree(gRenderer);

                    gp = new GamePlay(1, 3); //characterID, stage
                    gp->load(gRenderer);
                    loaded = true;
                    gameover = false;
                }

                if (paused && !pauseloaded){
                    continued = false;
                    buttons[1] = new button(SCREEN_WIDTH*3/10, SCREEN_HEIGHT*3/5, SCREEN_WIDTH*2/5, SCREEN_HEIGHT/10, STAGE1);
                    buttnow = 2;
                    pauseloaded = true;
                }

                sceneTexture->renderStageThree(gRenderer, gameover);
                gp->render(gRenderer, paused);

                if (paused){
                    sceneTexture->setViewport(SCREEN_WIDTH*3/10, SCREEN_HEIGHT*3/5, SCREEN_WIDTH*2/5, SCREEN_HEIGHT/10);
                    SDL_RenderCopyF( gRenderer, sceneTexture->getExtendedTexture2(), NULL, &(sceneTexture->getViewportRect()) );
                    sceneTexture->setViewport(SCREEN_WIDTH*3/10, SCREEN_HEIGHT*2/5, SCREEN_WIDTH*2/5, SCREEN_HEIGHT/10);
                    SDL_RenderCopyF( gRenderer, sceneTexture->getTextTexture1(), NULL, &(sceneTexture->getViewportRect()) );
                }

                //cout << won << endl;
                if (gameover && won){
                    sceneTexture->setViewport(SCREEN_WIDTH*3/10, SCREEN_HEIGHT*2/5, SCREEN_WIDTH*2/5, SCREEN_HEIGHT/10);
                    SDL_RenderCopyF( gRenderer, sceneTexture->getTextTexture2(), NULL, &(sceneTexture->getViewportRect()) );
                    delete buttons[MAIN];
                    buttons[MAIN] = NULL;
                    buttons[MAIN] = new button(SCREEN_WIDTH/50, SCREEN_HEIGHT*8/9, SCREEN_WIDTH/10, SCREEN_HEIGHT/10, MAINPAGE);
                }
                else if(gameover && !won){
                    sceneTexture->setViewport(SCREEN_WIDTH*3/10, SCREEN_HEIGHT*2/5, SCREEN_WIDTH*2/5, SCREEN_HEIGHT/6);
                    SDL_RenderCopyF( gRenderer, sceneTexture->getExtendedTexture1(), NULL, &(sceneTexture->getViewportRect()) );
                    delete buttons[MAIN];
                    buttons[MAIN] = NULL;
                    buttons[MAIN] = new button(SCREEN_WIDTH/50, SCREEN_HEIGHT*8/9, SCREEN_WIDTH/10, SCREEN_HEIGHT/10, MAINPAGE);
                }


                if (continued){
                    delete buttons[1];
                    buttons[1] = NULL;
                    buttnow = 1;
                    continued = false;
                }
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
        frame_tick = SDL_GetTicks() - cur_tick;
        if( frame_tick < SCREEN_TICK_PER_FRAME){
            SDL_Delay(SCREEN_TICK_PER_FRAME - frame_tick);
        }
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
