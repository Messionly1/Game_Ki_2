#ifndef RENDERWINDOW_HPP_INCLUDED
#define RENDERWINDOW_HPP_INCLUDED
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include<vector>

#include"Bird.hpp"
#include"Background.hpp"
#include"Pipe.hpp"
#include"Score.hpp"
#include"AnyThing.hpp"

class RenderWindow
{
private:
    SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Rect rect;
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char* p_filePath);
    void clear();
    void display();
    void cleanUp();
    void render(float p_x, float p_y, SDL_Texture* p_tex);
    void renderBird(Bird &bird,int index);
    void renderBackGround(Background &bg);
    void renderPipe(Pipe &pipe);
    void renderScore(Score &sc,Bird &b);
    void renderMuchPain(Anything &thing);
    void renderScoreBoard(Anything &thing);
    void renderScoreWhenDie(Score &sc,Bird &b);
    void renderHighScore(Score &sc,Bird &b);
    SDL_Renderer *getRenderer();
};

#endif // RENDERWINDOW_HPP_INCLUDED

