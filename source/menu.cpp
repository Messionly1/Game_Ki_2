#include "Menu.hpp"
#include <iostream>

Menu::Menu(SDL_Texture* bgTex, const std::vector<SDL_Texture*>& btnTextures) {
    backgroundTex = bgTex;
    buttonTextures = btnTextures;
    selectedButton = -1;
    hoveredButton = -1;
    isActive = true;

    // Initialize background rectangle
    backgroundRect.x = 0;
    backgroundRect.y = 0;
    SDL_QueryTexture(backgroundTex, NULL, NULL, &backgroundRect.w, &backgroundRect.h);

    // Initialize button rectangles
    for (size_t i = 0; i < buttonTextures.size(); ++i) {
        SDL_Rect srcRect, dstRect;
        srcRect.x = 0;
        srcRect.y = 0;
        SDL_QueryTexture(buttonTextures[i], NULL, NULL, &srcRect.w, &srcRect.h);

        // Center buttons horizontally, stack vertically starting at y=150
        dstRect.x = 288 / 2 - srcRect.w / 2;
        dstRect.y = 150 + i * (srcRect.h + 30); // Adjust spacing for your design
        dstRect.w = srcRect.w;
        dstRect.h = srcRect.h;

        buttonSrcRects.push_back(srcRect);
        buttonRects.push_back(dstRect);
    }
}

void Menu::update(SDL_Event& e) {
    if (!isActive) return;

    // Update hover state
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
                isActive = false; // Deactivate menu on click
                break;
            }
        }
    }
}

void Menu::render(RenderWindow& window) {
    if (!isActive) return;

    // Render background
    window.render(backgroundRect.x, backgroundRect.y, backgroundTex);

    // Render buttons with hover effect
    for (size_t i = 0; i < buttonTextures.size(); ++i) {
        float scale = (static_cast<int>(i) == hoveredButton) ? 1.1f : 1.0f; // Scale up on hover
        SDL_Rect dstRect = buttonRects[i];
        dstRect.w = static_cast<int>(buttonSrcRects[i].w * scale);
        dstRect.h = static_cast<int>(buttonSrcRects[i].h * scale);
        dstRect.x = 288 / 2 - dstRect.w / 2; // Re-center after scaling
        window.render(dstRect.x, dstRect.y, buttonTextures[i], scale);
    }
}
