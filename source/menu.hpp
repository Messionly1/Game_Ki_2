#ifndef MENU_HPP
#define MENU_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "RenderWindow.hpp"

class Menu {
private:
    SDL_Texture* backgroundTex;
    std::vector<SDL_Texture*> buttonTextures;
    SDL_Rect backgroundRect;
    std::vector<SDL_Rect> buttonRects;
    std::vector<SDL_Rect> buttonSrcRects;
    int selectedButton;
    int hoveredButton;
    bool isActive;

public:
    Menu(SDL_Texture* bgTex, const std::vector<SDL_Texture*>& btnTextures);
    void update(SDL_Event& e);
    void render(RenderWindow& window);
    bool isMenuActive() const { return isActive; }
    void setMenuActive(bool active) { isActive = active; }
    int getSelectedButton() const { return selectedButton; }
};

#endif
