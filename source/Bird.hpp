#ifndef BIRD_HPP_INCLUDED
#define BIRD_HPP_INCLUDED
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include"Pipe.hpp"
#include<math.h>
#include<vector>
#include<SDL_mixer.h>
const float GRAVITY=0.8;
const int DEAD=1,ALIVE=0,PLAYING=2;
const bool TRUE=true;
const float PI= 3.14159265;
class Bird
{
private:
    Mix_Chunk* hitSfx=Mix_LoadWAV("asset/die2.wav");
       Mix_Chunk* pointSfx=Mix_LoadWAV("asset/point.wav");
    float x,y,velocity=0,angle=0;
    SDL_Rect currentFrame;
    int changeImg=0,changeBirdDirectInMainScreen=0;
    int ActtualScore=0;
    std::    vector<SDL_Texture*>tex;
    int playerStatus=ALIVE;
    bool SplashWhenDie=false;


