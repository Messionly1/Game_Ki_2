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
