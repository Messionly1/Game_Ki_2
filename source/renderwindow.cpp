#include "RenderWindow.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h) {
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if (window == NULL)
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void RenderWindow::render(float p_x, float p_y, SDL_Texture* p_tex, float scale) {
    std::cout << "Rendering texture at (" << p_x << ", " << p_y << ")" << std::endl;
    if (!p_tex) {
        std::cout << "Warning: Attempting to render with nullptr texture!" << std::endl;
        return;
    }
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);

    SDL_Rect dst;
    dst.x = p_x;
    dst.y = p_y;
    dst.w = static_cast<int>(src.w * scale);
    dst.h = static_cast<int>(src.h * scale);
    SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

void RenderWindow::display() {
    std::cout << "Displaying frame" << std::endl;
    SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp() {
    SDL_DestroyWindow(window);
}

SDL_Renderer* RenderWindow::getRenderer() {
    return renderer;
}

void RenderWindow::clear() {
    std::cout << "Clearing renderer" << std::endl;
    SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);
    SDL_RenderClear(renderer);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, p_filePath);
    if (texture == NULL)
        std::cout << "Failed to load texture from path: " << p_filePath << ". Error: " << SDL_GetError() << std::endl;
    return texture;
}

void RenderWindow::renderBird(Bird &bird, int index) {
    std::cout << "Rendering bird with index " << index << std::endl;
    if (!bird.getTex(index)) {
        std::cout << "Warning: Bird texture is nullptr!" << std::endl;
        return;
    }
    SDL_Rect src;
    src.x = bird.getCurrentFrame().x;
    src.y = bird.getCurrentFrame().y;
    src.w = bird.getCurrentFrame().w;
    src.h = bird.getCurrentFrame().h;
    SDL_Rect dst;
    dst.x = bird.getX();
    dst.y = bird.getY();
    dst.w = bird.getCurrentFrame().w;
    dst.h = bird.getCurrentFrame().h;

    SDL_RenderCopyEx(renderer, bird.getTex(index), &src, &dst, static_cast<double>(bird.getAngle()), NULL, SDL_FLIP_NONE);
}

void RenderWindow::renderBackGround(Background &bg) {
    std::cout << "Rendering background at (" << bg.getX() << ", " << bg.getY() << ")" << std::endl;
    if (!bg.getTex()) {
        std::cout << "Warning: Background texture is nullptr!" << std::endl;
        return;
    }
    SDL_Rect src;
    src.x = bg.getCurrentFrame().x;
    src.y = bg.getCurrentFrame().y;
    src.w = bg.getCurrentFrame().w;
    src.h = bg.getCurrentFrame().h;
    SDL_Rect dst;
    dst.x = bg.getX();
    dst.y = bg.getY();
    dst.w = bg.getCurrentFrame().w;
    dst.h = bg.getCurrentFrame().h;
    SDL_RenderCopy(renderer, bg.getTex(), &src, &dst);
}

void RenderWindow::renderPipe(Pipe &pipe) {
    std::cout << "Rendering pipe at (" << pipe.getX() << ", " << pipe.getY() << ")" << std::endl;
    if (!pipe.getTex(0) || !pipe.getTex(1)) {
        std::cout << "Warning: Pipe texture is nullptr!" << std::endl;
        return;
    }
    SDL_Rect src;
    src.x = pipe.getCurrentFrame().x;
    src.y = pipe.getCurrentFrame().y;
    src.w = pipe.getCurrentFrame().w;
    src.h = pipe.getCurrentFrame().h;
    SDL_Rect dst;
    dst.x = pipe.getX();
    dst.y = pipe.getY();
    dst.w = pipe.getCurrentFrame().w;
    dst.h = pipe.getCurrentFrame().h;
    SDL_RenderCopy(renderer, pipe.getTex(0), &src, &dst);
    dst.x = pipe.getX();
    dst.y = pipe.getY() + static_cast<float>(pipe.getHeight()) + pipe.getPipeSpace();
    dst.w = pipe.getCurrentFrame().w;
    dst.h = pipe.getCurrentFrame().h;
    SDL_RenderCopy(renderer, pipe.getTex(1), &src, &dst);
}

void RenderWindow::renderScore(Score &sc, Bird &b) {
    std::cout << "Rendering score" << std::endl;
    sc.setScore(b.getActtualScore());
    sc.setHighScore();
    std::string s = std::to_string(sc.getScore());
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(sc.getFont(), s.c_str(), sc.getFontColor());
    if (!surfaceMessage) {
        std::cout << "Warning: Failed to render score text!" << std::endl;
        return;
    }
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = surfaceMessage->w;
    src.h = surfaceMessage->h;

    SDL_Rect dst;
    dst.x = sc.getX();
    dst.y = sc.getY();
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(renderer, message, &src, &dst);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void RenderWindow::renderHighScore(Score &sc, Bird &b) {
    std::cout << "Rendering high score" << std::endl;
    std::string s = std::to_string(sc.getHighScore());
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(sc.getFont(), s.c_str(), sc.getFontColor());
    if (!surfaceMessage) {
        std::cout << "Warning: Failed to render high score text!" << std::endl;
        return;
    }
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = surfaceMessage->w;
    src.h = surfaceMessage->h;

    SDL_Rect dst;
    dst.x = 236 - src.w;
    dst.y = 178 + 76 - 3;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(renderer, message, &src, &dst);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void RenderWindow::renderScoreWhenDie(Score &sc, Bird &b) {
    std::cout << "Rendering score when die" << std::endl;
    std::string s = std::to_string(sc.getCountingScore());
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(sc.getFont(), s.c_str(), sc.getFontColor());
    if (!surfaceMessage) {
        std::cout << "Warning: Failed to render score when die text!" << std::endl;
        return;
    }
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = surfaceMessage->w;
    src.h = surfaceMessage->h;

    SDL_Rect dst;
    dst.x = 236 - src.w;
    dst.y = 208;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(renderer, message, &src, &dst);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void RenderWindow::renderMuchPain(Anything &thing) {
    std::cout << "Rendering MuchPain" << std::endl;
    if (thing.getCount() > 4 && thing.getTexture()) {
        SDL_Rect src;
        src.x = thing.getCurrentFrame().x;
        src.y = thing.getCurrentFrame().y;
        src.w = thing.getCurrentFrame().w;
        src.h = thing.getCurrentFrame().h;
        SDL_Rect dst;
        dst.x = thing.getX();
        dst.y = thing.getY();
        dst.w = thing.getCurrentFrame().w;
        dst.h = thing.getCurrentFrame().h;
        SDL_RenderCopy(renderer, thing.getTexture(), &src, &dst);
    } else {
        std::cout << "Warning: MuchPain texture or count invalid!" << std::endl;
    }
}

void RenderWindow::renderScoreBoard(Anything &thing) {
    std::cout << "Rendering ScoreBoard" << std::endl;
    if (thing.getCount() > 11 && thing.getTexture()) {
        SDL_Rect src;
        src.x = thing.getCurrentFrame().x;
        src.y = thing.getCurrentFrame().y;
        src.w = thing.getCurrentFrame().w;
        src.h = thing.getCurrentFrame().h;
        SDL_Rect dst;
        dst.x = thing.getX();
        dst.y = thing.getY();
        dst.w = thing.getCurrentFrame().w;
        dst.h = thing.getCurrentFrame().h;
        SDL_RenderCopy(renderer, thing.getTexture(), &src, &dst);
    } else {
        std::cout << "Warning: ScoreBoard texture or count invalid!" << std::endl;
    }
}

void RenderWindow::renderMedal(Anything &thing, SDL_Texture* medalTexture, int score, int highScore) {
    std::cout << "Rendering Medal" << std::endl;
    if (score >= highScore && medalTexture) {
        SDL_Rect src;
        src.x = thing.getCurrentFrame().x;
        src.y = thing.getCurrentFrame().y;
        src.w = thing.getCurrentFrame().w;
        src.h = thing.getCurrentFrame().h;
        SDL_Rect dst;
        dst.x = thing.getX();
        dst.y = thing.getY();
        dst.w = thing.getCurrentFrame().w;
        dst.h = thing.getCurrentFrame().h;
        SDL_RenderCopy(renderer, medalTexture, &src, &dst);
    } else {
        std::cout << "Warning: Medal texture or condition invalid!" << std::endl;
    }
}

void RenderWindow::renderHearts(Anything &thing, SDL_Texture* heartTexture, int lives) {
    std::cout << "Rendering Hearts (lives: " << lives << ")" << std::endl;
    if (lives <= 0 || !heartTexture) {
        std::cout << "Warning: No lives or heart texture invalid!" << std::endl;
        return;
    }

    SDL_Rect src;
    src.x = thing.getCurrentFrame().x;
    src.y = thing.getCurrentFrame().y;
    src.w = thing.getCurrentFrame().w;
    src.h = thing.getCurrentFrame().h;

    for (int i = 0; i < lives; ++i) {
        SDL_Rect dst;
        dst.x = -15 + i * 25;
        dst.y = -5;
        dst.w = src.w;
        dst.h = src.h;
        SDL_RenderCopy(renderer, heartTexture, &src, &dst);
    }
}
