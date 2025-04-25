#ifndef BASE_HPP_INCLUDED
#define BASE_HPP_INCLUDED
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <iostream>

const int MUCHPAIN = 4, SCOREBOARD = 0;


class Anything
{
private:
    bool inDst;
    SDL_Texture* texture;
    SDL_Rect currentFrame;
    float x, y, z, dstX, dstY, ScoreBoardVelocity = -24, MuchPainVelocity = 4;
    int TextureFrameUp = 1, TextureFrameDown = 2;
    int count = 0;
    Mix_Music* bgMusic = NULL;
public:
    Anything(float _srcX, float _srcY, float _dstX, float _dstY, SDL_Texture* _texture);

    float getX();
    float getY();
    float getZ();
    void setX(float _x);
    void setY(float _y);
    void setZ(float _z);

    SDL_Rect getCurrentFrame();
    int getWidth();
    int getHeight();
    int getCount();
    void updateScoreBoard();
    void updateMuchPain();
        bool isInDst();
    SDL_Texture* getTex();
    void reset();

    void initAudio();
    void cleanAudio();
};
#endif // BASE_HPP_INCLUDED



