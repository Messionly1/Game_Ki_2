#include <iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include"source/RenderWindow.hpp"
#include<vector>

using namespace std;
void gameLoop();
RenderWindow window("Game",288,512);
SDL_Texture *city=window.loadTexture("asset/pinknightbg.png");
SDL_Texture *ground=window.loadTexture("asset/pinkbase2.png");
Mix_Chunk *jumpSfx;
Mix_Chunk* hitSfx;
Mix_Chunk * swooshSfx;
Mix_Chunk *pointSfx;
Mix_Chunk *dieSfx;
vector<SDL_Texture*> things;

vector<SDL_Texture*> p;
vector<SDL_Texture*>bird ;
bool init()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
    p.push_back(window.loadTexture("asset/FbUpperPipe.png"));
    p.push_back(window.loadTexture("asset/FbUnderPipe.png"));
    bird.push_back(window.loadTexture("asset/FbBlueBird1.png"));
    bird.push_back(window.loadTexture("asset/FbBlueBird2.png"));
    bird.push_back(window.loadTexture("asset/FbBlueBird3.png"));
    bird.push_back(window.loadTexture("asset/FbYellowBird1.png"));
    bird.push_back(window.loadTexture("asset/FbYellowBird2.png"));
    bird.push_back(window.loadTexture("asset/FbYellowBird3.png"));
    bird.push_back(window.loadTexture("asset/FbRedBird1.png"));
    bird.push_back(window.loadTexture("asset/FbRedBird2.png"));
    bird.push_back(window.loadTexture("asset/FbRedBird3.png"));
    things.push_back(window.loadTexture("asset/FbTapToPlay.png"));   //0
    things.push_back(window.loadTexture("asset/WhiteTex.png"));      //1
    things.push_back(window.loadTexture("asset/ScoreBoard.png"));    //2
    things.push_back(window.loadTexture("asset/FbGetReady.png"));    //3
    things .push_back(window.loadTexture("asset/FbMuchPain.png"));   //4
    things.push_back(window.loadTexture("asset/FbPlayButton.png"));  //5
    things .push_back(window.loadTexture("asset/Fb2ndPlayButton.png"));//6
    things.push_back(window.loadTexture("asset/BlendBg.png")); //7
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    jumpSfx=Mix_LoadWAV("asset/wing.wav");
    hitSfx=Mix_LoadWAV("asset/die2.wav");
    pointSfx=Mix_LoadWAV("asset/point.wav");
    swooshSfx=Mix_LoadWAV("asset/swoosh.wav");
    dieSfx=Mix_LoadWAV("asset/die.wav");
    Mix_Volume(-1,MIX_MAX_VOLUME);
    bgMusic = Mix_LoadMUS("asset/music.wav");

    return true;
}
bool load =init();
bool mainScreen=true;
Anything ScoreBoard(288/2-226/2,512,288/2-226/2,512-90-114-130,things[2]),MuchPain(288/2-186/2,55,288/2-186/2,80,things[4]);

Bird player(50,512/2-18,bird);
Background bg1(0,0,city),bg2(288,0,city),blendBg(0,0,things[7]);
Background base1(0,512-90,ground),base2(288,512-90,ground);
Pipe pipe1(288,-220,p,112),pipe2(288+170,-90,p,112);
TTF_Font* flappyFont =TTF_OpenFont("asset/fBirdFont.ttf",28);
SDL_Color textColor ={255,255,255};
int a;
bool check=false,hitSFx =false,swooshSFx=false;
Score playerScore(144-9,60,flappyFont,textColor);
void reset()
{
    player.reset();
    pipe1.reset(pipe1,pipe2);
    ScoreBoard.reset();
    MuchPain.reset();
    mainScreen=true;
    playerScore.reset();
    blendBg.reset();
    a=0;
    check=false;
    swooshSFx=false;

}

int main(int argv, char** args)
{
    SDL_Texture* dummyTexture = nullptr;
    Anything any(0, 0, 0, 0, dummyTexture);
    any.initAudio();

    SDL_Event e;
    bool isRunning =true;
    while(isRunning)
    {
        window.clear();
        while(SDL_PollEvent(&e))
        {
//Handle Events
            if (e.type==SDL_QUIT)
            {
                isRunning=false;
            }
            if(e.type==SDL_MOUSEBUTTONDOWN)
            {
                int mouseX=0,mouseY=0;
                SDL_GetMouseState(&mouseX,&mouseY);
                if(mainScreen==true && e.button.button==SDL_BUTTON_LEFT  && SDL_GetTicks()>200 )
                {
                    mainScreen=false;
                    player.jump();
                    Mix_PlayChannel(-1,jumpSfx,0);
                }
                else {
                        if(e.button.button==SDL_BUTTON_LEFT &&player.isDead()!=DEAD)
                        {
                            player.jump();
                            Mix_PlayChannel(-1,jumpSfx,0);

                        }
                        if (e.button.button==SDL_BUTTON_LEFT&& (mouseX>288/2-104/2 && mouseX<288/2-104/2+104)&&(mouseY>512-90-130+30 &&mouseY<512-90-130+30+58)&&player.isDead()==DEAD && MuchPain.getCount()>30+playerScore.getScore()*3)
                        {
                            check=true;
                            a =MuchPain.getCount();
                        }
                }
            }
        }
//Update Screen
if(mainScreen)
        {
            if (swooshSFx==false)
            {
                swooshSFx=true;
                Mix_PlayChannel(-1,swooshSfx,0);
            }
            pipe1.reset(pipe1,pipe2);
            blendBg.updateBlendingLight();
            player.setX(120);
            player.setY(512/2-18);
            player.update(pipe1,pipe2,mainScreen);
            bg1.updateMainBg();
            bg2.updateMainBg();
            base1.updateBase();
            base2.updateBase();
        }



