#ifndef BIRD_HPP_INCLUDED
#define BIRD_HPP_INCLUDED
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include "Pipe.hpp"

#define PI 3.14159265359
#define GRAVITY 0.5
#define DEAD 1
#define ALIVE 0
#define LIVE_CAP 3

extern Mix_Chunk *hitSfx;
extern Mix_Chunk *pointSfx;
enum PipeType {
    SINGLE_PIPE,
    STACKED_PIPE,
    SPECIAL_PIPE
};
class Bird {
private:
    float x, y, velocity = GRAVITY, angle = 0;
    int playerStatus = ALIVE;
    int changeImg = 0;
    int changeBirdDirectInMainScreen = 0;
    int ActtualScore = 0;
    bool SplashWhenDie = false;
    std::vector<SDL_Texture*> tex;
    SDL_Rect currentFrame;
    int lives;
    bool invincible = false;
    int invincibleFrames = 0;
    int colorIndex;
    PipeType type;

public:
    Bird(float _x, float _y, std::vector<SDL_Texture*> _tex, int _colorIndex);
    void jump();
    void update(Pipe& b1, Pipe& b2, bool mainScreen);
    int getHeight();
    int getWidth();
    float getY();
    float getX();
    void setY(float _y);
    void setX(float _x);
    float getAngle();
    void setAngle(float _angle);
    SDL_Texture* getTex(int index);
    SDL_Rect getCurrentFrame();
    bool isDead();
    void reset();
    int getActtualScore();
    bool checkSplashWhenDie();
    void setCheckSplash(bool s);
    float getTopRightX(float a);
    float getTopRightY(float a);
    float getBottomRightX(float a);
    float getBottomRightY(float a);
    float getBottomLeftX(float a);
    float getBottomLeftY(float a);
    float getTopLeftX(float a);
    float getTopLeftY(float a);
    int getImgIndex();
    int getLives() { return lives; }
    void setColorIndex(int index) { colorIndex = index; }
    int getColorIndex() { return colorIndex; }

};

#endif
