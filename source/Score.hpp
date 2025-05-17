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
public:
    Score(float _x, float  _y,TTF_Font* _font,SDL_Color _fontColor);
    float getX();
    float getY();
    int getWidth();
    int getHeight();
    void setHighScore();
    int getHighScore();
    int getScore();
    void setScore(int _score);
    void update();

    TTF_Font* getFont();
    SDL_Color getFontColor();
    int getCountingScore();
    void setCountingScore(int x);
    void reset();
    void addPoint();

};

#endif // SCORE_HPP_INCLUDED

