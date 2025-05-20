#include "Menu.hpp"
#include <iostream>

Menu::Menu(SDL_Texture* bgTex, const std::vector<SDL_Texture*>& btnTextures) {
    backgroundTex = bgTex;
    buttonTextures = btnTextures;
    selectedButton = -1;
    hoveredButton = -1;
    isActive = true;

    backgroundRect.x = 0;
    backgroundRect.y = 0;
    SDL_QueryTexture(backgroundTex, NULL, NULL, &backgroundRect.w, &backgroundRect.h);

    for (size_t i = 0; i < buttonTextures.size(); ++i) {
        SDL_Rect srcRect, dstRect;
        srcRect.x = 0;
        srcRect.y = 0;
        SDL_QueryTexture(buttonTextures[i], NULL, NULL, &srcRect.w, &srcRect.h);
        dstRect.x = 288 / 2 - srcRect.w / 2;
        dstRect.y = 150 + i * (srcRect.h + 20);
        dstRect.w = srcRect.w;
        dstRect.h = srcRect.h;

        buttonSrcRects.push_back(srcRect);
        buttonRects.push_back(dstRect);
    }
}

void Menu::update(SDL_Event& e) {
    if (!isActive) return;

    //HOVER
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    hoveredButton = -1;
    for (size_t i = 0; i < buttonRects.size(); ++i) {
        SDL_Rect& btn = buttonRects[i];
        if (mouseX >= btn.x && mouseX <= btn.x + btn.w &&
            mouseY >= btn.y && mouseY <= btn.y + btn.h) {
            hoveredButton = static_cast<int>(i);
            break;
        }
    }

    // Handle clicks
    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        for (size_t i = 0; i < buttonRects.size(); ++i) {
            SDL_Rect& btn = buttonRects[i];
            if (mouseX >= btn.x && mouseX <= btn.x + btn.w &&
                mouseY >= btn.y && mouseY <= btn.y + btn.h) {
                selectedButton = static_cast<int>(i);
                isActive = false;
                break;
            }
        }
    }
}

void Menu::render(RenderWindow& window) {
    if (!isActive) return;
    window.render(backgroundRect.x, backgroundRect.y, backgroundTex);
    for (size_t i = 0; i < buttonTextures.size(); ++i) {
        float scale = (static_cast<int>(i) == hoveredButton) ? 1.1f : 1.0f;
        SDL_Rect dstRect = buttonRects[i];
        dstRect.w = static_cast<int>(buttonSrcRects[i].w * scale);
        dstRect.h = static_cast<int>(buttonSrcRects[i].h * scale);
        dstRect.x = 288 / 2 - dstRect.w / 2;
        window.render(dstRect.x, dstRect.y, buttonTextures[i], scale);
    }
}
