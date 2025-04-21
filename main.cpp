#include <iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include"source/RenderWindow.hpp"
#include<vector>
#include "source/AnyThing.hpp"


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
Mix_Music *backgroundMusic = NULL;
Mix_Music* bgMusic=NULL;

vector<SDL_Texture*> things;
vector<SDL_Texture*> p;
vector<SDL_Texture*>bird ;

