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
const int LIVE_CAP = 3;

class Bird
{
private:
    Mix_Chunk* hitSfx=Mix_LoadWAV("asset/die2.wav");
    Mix_Chunk* pointSfx=Mix_LoadWAV("asset/point.wav");
    float x,y,velocity=0,angle=0;
    SDL_Rect currentFrame;
    int changeImg=0,changeBirdDirectInMainScreen=0;
    int ActtualScore=0;
    std::vector<SDL_Texture*>tex;
    int playerStatus=ALIVE;
    bool SplashWhenDie=false;
    int invincibleFrame = 0;
    int width, height;
    int lives = LIVE_CAP;
    bool invincible = false;
    int invincibleFrames = 0;

public:
    Bird(float _x,float _y,std::vector<SDL_Texture*>_tex);
    float getX();
    float getY();
    int getWidth();
    int getHeight();
    void setY(float _y);
    void setX(float _x);
    void jump();
    void update(Pipe &b1,Pipe &b2,bool mainScreen);
    SDL_Texture* getTex(int index);
    int getImgIndex();
    SDL_Rect getCurrentFrame();
    bool isDead();
    void reset();
    int getActtualScore();
    float getAngle();
    void setAngle(float _angle);
    bool checkSplashWhenDie();
    void setCheckSplash(bool s);
    int state; // 0 = ALIVE, 1 = DEAD
    bool checkSplash;
    int getLives() const { return lives; }
    void setLives(int _lives) { lives = _lives; }
    void loseLife() { if (!invincible) lives--; }
    bool isInvincible() const { return invincible; }
    void setInvincible(bool _invincible) { invincible = _invincible; }

    float getTopRightX(float a);
    float getTopRightY(float a);
    float getTopLeftX(float a);
    float getTopLeftY(float a);
    float getBottomLeftX(float a);
    float getBottomLeftY(float a);
    float getBottomRightX(float a);
    float getBottomRightY(float a);

    void resetNearestPipes(Pipe& p1, Pipe& p2, float birdX);
    void respawn();
    void setStatus(int status);


};
#endif // BIRD_HPP_INCLUDED
