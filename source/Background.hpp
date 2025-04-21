#ifndef BACKGROUND_HPP_INCLUDED
#define BACKGROUND_HPP_INCLUDED
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include<vector>

class Background
{
private:
    SDL_Texture *texture;
    SDL_Rect currentFrame;
    int x,y;
    Uint8 a=255,b=0;
