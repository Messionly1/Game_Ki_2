#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Bird.hpp"
#include "Background.hpp"
#include "Pipe.hpp"
#include "Score.hpp"
#include "Anything.hpp"

class RenderWindow {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    void render(float p_x, float p_y, SDL_Texture* p_tex, float scale = 1.0f);
    void display();
    void cleanUp();
    SDL_Renderer* getRenderer();
    void clear();
    SDL_Texture* loadTexture(const char* p_filePath);
    void renderBird(Bird &bird, int index);
    void renderBackGround(Background &bg);
    void renderPipe(Pipe &pipe);
    void renderScore(Score &sc, Bird &b);
    void renderHighScore(Score &sc, Bird &b);
    void renderScoreWhenDie(Score &sc, Bird &b);
    void renderMuchPain(Anything &thing);
    void renderScoreBoard(Anything &thing);
    void renderMedal(Anything &thing, SDL_Texture* medalTexture, int score, int highScore);
    void renderHearts(Anything &thing, SDL_Texture* heartTexture, int lives);
};

#endif
