#ifndef SCORE_HPP_INCLUDED
#define SCORE_HPP_INCLUDED
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include<string>
#include <SDL_ttf.h>
#include <iostream>
#include<vector>
class Score
{
private:
    float x,y;
    int width,height;
    int score,countingScore=0;
    int HighScore=0;
    TTF_Font* font;
    SDL_Color fontColor;
