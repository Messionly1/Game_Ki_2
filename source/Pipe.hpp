#ifndef PIPE_HPP_INCLUDED
#define PIPE_HPP_INCLUDED
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include<vector>
#include<ctime>
#include<stdlib.h>
#include<random>
#include"Score.hpp"
class Pipe
{
private:
    float x,y,PipeSpace,velocity=-3;
    int count =0;

    std::vector<SDL_Texture*>tex;
    SDL_Rect currentFrame;
    bool PipeScored=false;
    bool MovingPipe=true;
public:
    Pipe(float _x,float _y,std::vector<SDL_Texture*>_tex,float _space);
    void update(int index);
    float getX();
    float getPipeSpace();
    float getY();
    int getWidth();
    int getHeight();
    void setX(float _x);
    void setY(float _y);
    int getSize();

