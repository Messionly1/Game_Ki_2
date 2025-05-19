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
    int moveDirection;


    bool isDoublePipe = false;
    bool isRandomSize = false;
    float sizeMultiplier = 1.0f;
    int gapBetweenPipes = 0;
    bool isMergedPipe = false;
    float mergedPipeOffset = 0.0f;
    int mergedPipeWidth = 0;

public:
    Pipe(float _x,float _y,std::vector<SDL_Texture*>_tex,float _space);
    void update(int index, Pipe& otherPipe);
    float getX();
    float getPipeSpace();
    float getY();
    int getWidth();
    int getHeight();
    void setX(float _x);
    void setY(float _y);
    int getSize();
    SDL_Texture * getTex(int index);
    SDL_Rect getCurrentFrame();
    int  getPipeRandom(int  min_num, int  max_num);
    void reset(Pipe &p1,Pipe &p2);
    bool isScored();
    void setPipeScored(bool s);
    void setMovingPipe(bool s);
    bool getMovingPipe();

    void setDoublePipe(bool isDouble);
    bool getDoublePipe() const;
    void setRandomSize(bool random);
    bool getRandomSize() const;
    float getSizeMultiplier() const;
    int getGapBetweenPipes() const;

    void updateAlpha();
    int getAlpha();
    void setFading(bool f);
    void setFadeIn(bool f);
    bool isFading();
    void setMoveDirection(int dir) { moveDirection = dir; }
    int getMoveDirection() const { return moveDirection; }
    bool isScored() const { return PipeScored; }
    void setScored(bool scored) { PipeScored = scored; }

    bool isMerged() const;
    float getMergedOffset() const;
    void setMerged(bool merged, float offset = 30.0f);
};
#endif // PIPE_HPP_INCLUDED
