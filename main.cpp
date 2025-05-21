#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "source/RenderWindow.hpp"
#include "source/Anything.hpp"
#include "source/Menu.hpp"
#include <vector>
#include <random>
#include <algorithm>

using namespace std;
int lives = 3;
std::vector<int> highScores = {0, 0, 0};

enum GameState { MAIN_MENU, SETTINGS_MENU, GAME, RANKING };
GameState state = MAIN_MENU;

void gameLoop();
RenderWindow window("FLAPPY BIRD", 288, 512);
SDL_Texture *city = window.loadTexture("asset/pinknightbg.png");
SDL_Texture *ground = window.loadTexture("asset/pinkbase2.png");
SDL_Texture *medal = window.loadTexture("asset/medal.png");
SDL_Texture *heartTexture;
SDL_Texture *musicOnTexture;
SDL_Texture *musicOffTexture;

Mix_Chunk *jumpSfx;
Mix_Chunk *hitSfx;
Mix_Chunk *swooshSfx;
Mix_Chunk *pointSfx;
Mix_Chunk *dieSfx;
Mix_Music *bgMusic1;
Mix_Music *bgMusic2;
Mix_Music *bgMusic3;
Mix_Music *currentMusic;

vector<SDL_Texture*> things;
vector<SDL_Texture*> p;
vector<SDL_Texture*> bird;
vector<SDL_Texture*> menuButtons;
vector<SDL_Texture*> settingsButtons;
Anything heart(0, 0, 24, 24, nullptr);
Anything musicToggle(225, 0, 254, 10, nullptr);
Anything restartButton(288/2 - 104/2, 512 - 90 - 130 + 30, 288/2 - 104/2, 512 - 90 - 130 + 30, nullptr);
bool isMusicOn = true;
bool isRestartHovered = false;

vector<SDL_Texture*> getBirdTextures(int colorIndex) {
    vector<SDL_Texture*> selectedTextures;
    int startIndex = colorIndex * 3;
    for (int i = 0; i < 3; ++i) {
        selectedTextures.push_back(bird[startIndex + i]);
    }
    return selectedTextures;
}

bool init() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    p.push_back(window.loadTexture("asset/FbUpperPipe.png"));
    p.push_back(window.loadTexture("asset/FbUnderPipe.png"));
    bird.push_back(window.loadTexture("asset/FbBlueBird1.png"));
    bird.push_back(window.loadTexture("asset/FbBlueBird2.png"));
    bird.push_back(window.loadTexture("asset/FbBlueBird3.png"));
    bird.push_back(window.loadTexture("asset/FbYellowBird1.png"));
    bird.push_back(window.loadTexture("asset/FbYellowBird2.png"));
    bird.push_back(window.loadTexture("asset/FbYellowBird3.png"));
    bird.push_back(window.loadTexture("asset/FbRedBird1.png"));
    bird.push_back(window.loadTexture("asset/FbRedBird2.png"));
    bird.push_back(window.loadTexture("asset/FbRedBird3.png"));
    things.push_back(window.loadTexture("asset/FbTapToPlay.png"));
    things.push_back(window.loadTexture("asset/WhiteTex.png"));
    things.push_back(window.loadTexture("asset/ScoreBoard.png"));
    things.push_back(window.loadTexture("asset/FbGetReady.png"));
    things.push_back(window.loadTexture("asset/FbMuchPain.png"));
    things.push_back(window.loadTexture("asset/FbPlayButton.png"));
    things.push_back(window.loadTexture("asset/Fb2ndPlayButton.png"));
    things.push_back(window.loadTexture("asset/BlendBg.png"));
    things.push_back(window.loadTexture("asset/medal.png"));
    things.push_back(window.loadTexture("asset/FbRankButton.png"));
    things.push_back(window.loadTexture("asset/FbRank2ndButton.png"));
    SDL_Texture* rankingTexture = window.loadTexture("asset/ranking.png");
    if (!rankingTexture) {
        std::cout << "Failed to load ranking.png: " << SDL_GetError() << std::endl;
        rankingTexture = things[0];
    }
    things.push_back(rankingTexture);

    menuButtons.push_back(window.loadTexture("asset/buttonPlay.png"));
    menuButtons.push_back(window.loadTexture("asset/buttonSetting.png"));
    menuButtons.push_back(window.loadTexture("asset/buttonQuit.png"));
    menuButtons.push_back(window.loadTexture("asset/FbRankButton.png"));

    settingsButtons.push_back(window.loadTexture("asset/level1.png"));
    settingsButtons.push_back(window.loadTexture("asset/level2.png"));
    settingsButtons.push_back(window.loadTexture("asset/level3.png"));

    heartTexture = window.loadTexture("asset/heart.png");
    if (!heartTexture) {
        std::cout << "Failed to load heart.png: " << SDL_GetError() << std::endl;
        heartTexture = things[0];
    }
    heart = Anything(0, 0, 24, 24, heartTexture);

    restartButton = Anything(288/2 - 104/2, 512 - 90 - 130 + 30, 288/2 - 104/2, 512 - 90 - 130 + 30, things[5]);

    musicOnTexture = window.loadTexture("asset/on.png");
    musicOffTexture = window.loadTexture("asset/off.png");
    if (!musicOnTexture || !musicOffTexture) {
        std::cout << "Failed to load music toggle textures: " << SDL_GetError() << std::endl;
        musicOnTexture = things[0];
        musicOffTexture = things[0];
    }
    musicToggle = Anything(225, 0, 254, 10, musicOffTexture);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    jumpSfx = Mix_LoadWAV("asset/wing.wav");
    hitSfx = Mix_LoadWAV("asset/die2.wav");
    pointSfx = Mix_LoadWAV("asset/point.wav");
    swooshSfx = Mix_LoadWAV("asset/swoosh.wav");
    dieSfx = Mix_LoadWAV("asset/die.wav");
    Mix_Volume(-1, MIX_MAX_VOLUME);
    bgMusic1 = Mix_LoadMUS("asset/music.wav");
    bgMusic2 = Mix_LoadMUS("asset/music2.wav");
    bgMusic3 = Mix_LoadMUS("asset/music3.wav");
    currentMusic = bgMusic1;
    Mix_PlayMusic(currentMusic, -1);

    return true;
}

bool load = init();
bool mainScreen = false;
Anything ScoreBoard(288/2-226/2, 512, 288/2-226/2, 512-90-114-130, things[2]);
Anything MuchPain(288/2-186/2, 55, 288/2-186/2, 80, things[4]);

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 2);
int initialColorIndex = dis(gen);
Bird player(50, 512/2-18, getBirdTextures(initialColorIndex), initialColorIndex);

Background bg1(0, 0, city), bg2(288, 0, city), blendBg(0, 0, things[7]);
Background base1(0, 512-90, ground), base2(288, 512-90, ground);
Pipe pipe1(288, -220, p, 112), pipe2(288+170, -90, p, 112);
TTF_Font* flappyFont = TTF_OpenFont("asset/fBirdFont.ttf", 28);
SDL_Color textColor = {255, 255, 255};
int a;
bool check = false, hitSFx = false, swooshSFx = false;
Score playerScore(144-9, 60, flappyFont, textColor);
Menu mainMenu(window.loadTexture("asset/menu.png"), menuButtons);
Menu settingsMenu(window.loadTexture("asset/menu.png"), settingsButtons);
bool pipe1Scored = false;
bool pipe2Scored = false;

void reset() {
    highScores.push_back(playerScore.getCountingScore());
    std::sort(highScores.begin(), highScores.end(), std::greater<int>());
    if (highScores.size() > 3) {
        highScores.resize(3);
    }

    int newColorIndex = dis(gen);
    player = Bird(50, 512/2-18, getBirdTextures(newColorIndex), newColorIndex);
    pipe1.reset(pipe1, pipe2);
    pipe1.setScored(false);
    pipe2.setScored(false);
    ScoreBoard.reset();
    MuchPain.reset();
    mainScreen = false;
    mainMenu.setMenuActive(true);
    settingsMenu.setMenuActive(false);
    state = MAIN_MENU;
    playerScore.reset();
    blendBg.reset();
    a = 0;
    check = false;
    swooshSFx = false;
    lives = 3;
    isMusicOn = true;
    isRestartHovered = false;
    Mix_ResumeMusic();
}

int main(int argv, char** args) {
    SDL_Texture* dummyTexture = nullptr;
    Anything any(0, 0, 0, 0, dummyTexture);
    any.initAudio();

    SDL_Event e;
    bool isRunning = true;
    while (isRunning) {
        window.clear();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            }
            if (state == MAIN_MENU) {
                mainMenu.update(e);
                if (!mainMenu.isMenuActive()) {
                    int selected = mainMenu.getSelectedButton();
                    if (selected == 0) {
                        mainScreen = true;
                        state = GAME;
                        player.jump();
                        Mix_PlayChannel(-1, jumpSfx, 0);
                    } else if (selected == 1) {
                        state = SETTINGS_MENU;
                        mainMenu.setMenuActive(true);
                        settingsMenu.setMenuActive(true);
                    } else if (selected == 2) {
                        isRunning = false;
                    } else if (selected == 3) {
                        state = RANKING;
                        mainMenu.setMenuActive(true);
                    }
                }
            } else if (state == SETTINGS_MENU) {
                settingsMenu.update(e);
                if (!settingsMenu.isMenuActive()) {
                    int selected = settingsMenu.getSelectedButton();
                    if (selected == 0) { // Play
                        Mix_HaltMusic();
                        currentMusic = bgMusic1;
                        if (isMusicOn) Mix_PlayMusic(currentMusic, -1);
                    } else if (selected == 1) {
                        Mix_HaltMusic();
                        currentMusic = bgMusic2;
                        if (isMusicOn) Mix_PlayMusic(currentMusic, -1);
                    } else if (selected == 2) {
                        Mix_HaltMusic();
                        currentMusic = bgMusic3;
                        if (isMusicOn) Mix_PlayMusic(currentMusic, -1);
                    }
                    state = MAIN_MENU;
                    settingsMenu.setMenuActive(true);
                    mainMenu.setMenuActive(true);
                }
            } else if (state == RANKING) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                bool isRankButtonHovered = false;
                SDL_Rect rankButtonRect = {288/2 - 104/2, 512 - 90 - 130 + 90, 104, 40};
                if (mouseX >= rankButtonRect.x && mouseX <= rankButtonRect.x + rankButtonRect.w &&
                    mouseY >= rankButtonRect.y && mouseY <= rankButtonRect.y + rankButtonRect.h) {
                    isRankButtonHovered = true;
                    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                        state = MAIN_MENU;
                        mainMenu.setMenuActive(true);
                    }
                }
                window.render(0, 0, things[11]); //ranking
                for (int i = 0; i < highScores.size(); ++i) {
                    std::string scoreText = std::to_string(highScores[i]);
                    SDL_Surface* textSurface = TTF_RenderText_Solid(flappyFont, scoreText.c_str(), textColor);
                    if (textSurface) {
                        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(window.getRenderer(), textSurface);
                        if (textTexture) {
                            int textW, textH;
                            SDL_QueryTexture(textTexture, nullptr, nullptr, &textW, &textH);
                            int x, y;
                            if (i == 0) {
                                x = 144 - textW / 2;
                                y = 170;
                            } else if (i == 1) {
                                x = 55 - textW / 2;
                                y = 200;
                            } else {
                                x = 225 - textW / 2;
                                y = 230;
                            }
                            window.render(x, y, textTexture);
                            SDL_DestroyTexture(textTexture);
                        }
                        SDL_FreeSurface(textSurface);
                    }
                }
                window.render(rankButtonRect.x, rankButtonRect.y, isRankButtonHovered ? things[10] : things[9]);
            } else {
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX = 0, mouseY = 0;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if (mainScreen && e.button.button == SDL_BUTTON_LEFT && SDL_GetTicks() > 200) {
                        mainScreen = false;
                        player.jump();
                        Mix_PlayChannel(-1, jumpSfx, 0);
                    } else {
                        if (e.button.button == SDL_BUTTON_LEFT && player.isDead() != DEAD) {
                            SDL_Rect musicRect = {static_cast<int>(musicToggle.getX()), static_cast<int>(musicToggle.getY()), musicToggle.getWidth(), musicToggle.getHeight()};
                            if (mouseX >= musicRect.x && mouseX <= musicRect.x + musicRect.w &&
                                mouseY >= musicRect.y && mouseY <= musicRect.y + musicRect.h) {
                                isMusicOn = !isMusicOn;
                                if (isMusicOn) {
                                    Mix_ResumeMusic();
                                } else {
                                    Mix_PauseMusic();
                                }
                            } else {
                                player.jump();
                                Mix_PlayChannel(-1, jumpSfx, 0);
                            }
                        }
                        if (e.button.button == SDL_BUTTON_LEFT &&
                            player.isDead() == DEAD && MuchPain.getCount() > 30 + playerScore.getScore() * 3) {
                            SDL_Rect restartRect = {static_cast<int>(restartButton.getX()), static_cast<int>(restartButton.getY()), restartButton.getWidth(), restartButton.getHeight()};
                            if (mouseX >= restartRect.x && mouseX <= restartRect.x + restartRect.w &&
                                mouseY >= restartRect.y && mouseY <= restartRect.y + restartRect.h) {
                                check = true;
                                a = MuchPain.getCount();
                            }
                        }
                    }
                }
                if (e.type == SDL_MOUSEMOTION && player.isDead() == DEAD && MuchPain.getCount() > 30 + playerScore.getScore() * 3) {
                    int mouseX = 0, mouseY = 0;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    SDL_Rect restartRect = {static_cast<int>(restartButton.getX()), static_cast<int>(restartButton.getY()), restartButton.getWidth(), restartButton.getHeight()};
                    if (mouseX >= restartRect.x && mouseX <= restartRect.x + restartRect.w &&
                        mouseY >= restartRect.y && mouseY <= restartRect.y + restartRect.h) {
                        isRestartHovered = true;
                    } else {
                        isRestartHovered = false;
                    }
                }
            }
        }

        if (state == MAIN_MENU) {
            mainMenu.render(window);
        } else if (state == SETTINGS_MENU) {
            settingsMenu.render(window);
        } else if (state == RANKING) {
            window.render(0, 0, things[11]);

            for (int i = 0; i < highScores.size(); ++i) {
                std::string scoreText = std::to_string(highScores[i]);
                SDL_Surface* textSurface = TTF_RenderText_Solid(flappyFont, scoreText.c_str(), textColor);
                if (textSurface) {
                    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(window.getRenderer(), textSurface);
                    if (textTexture) {
                        int textW, textH;
                        SDL_QueryTexture(textTexture, nullptr, nullptr, &textW, &textH);
                        int x, y;
                        if (i == 0) {
                            x = 144 - textW / 2;
                            y = 170;
                        } else if (i == 1) {
                            x = 55 - textW / 2;
                            y = 200;
                        } else {
                            x = 225 - textW / 2;
                            y = 230;
                        }
                        window.render(x, y, textTexture);
                        SDL_DestroyTexture(textTexture);
                    }
                    SDL_FreeSurface(textSurface);
                }
            }
            SDL_Rect rankButtonRect = {288/2 - 104/2, 512 - 90 - 130 + 90, 104, 40};
            bool isRankButtonHovered = false;
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if (mouseX >= rankButtonRect.x && mouseX <= rankButtonRect.x + rankButtonRect.w &&
                mouseY >= rankButtonRect.y && mouseY <= rankButtonRect.y + rankButtonRect.h) {
                isRankButtonHovered = true;
            }
            window.render(rankButtonRect.x, rankButtonRect.y, isRankButtonHovered ? things[10] : things[9]);
        } else {
            if (mainScreen) {
                if (!swooshSFx) {
                    swooshSFx = true;
                    Mix_PlayChannel(-1, swooshSfx, 0);
                }
                pipe1.reset(pipe1, pipe2);
                blendBg.updateBlendingLight();
                player.setX(120);
                player.setY(512/2-18);
                player.update(pipe1, pipe2, mainScreen);
                bg1.updateMainBg();
                bg2.updateMainBg();
                base1.updateBase();
                base2.updateBase();
                window.renderBackGround(bg1);
                window.renderBackGround(bg2);
                window.renderPipe(pipe1);
                window.renderPipe(pipe2);
                window.renderBackGround(base2);
                window.renderBackGround(base1);
                window.renderBird(player, player.getImgIndex());
                window.render(288/2-114/2-5, 290, things[0]);
                window.render(288/2-184/2, 49+35, things[3]);
                window.renderBackGround(blendBg);
            } else {
                if (player.isDead() != DEAD) {
                    pipe1.update(1, pipe2);
                    pipe2.update(2, pipe1);
                    bg1.updateMainBg();
                    bg2.updateMainBg();
                    base1.updateBase();
                    base2.updateBase();

                    if (player.getX() > pipe1.getX() + pipe1.getWidth() && !pipe1.isScored()) {
                        playerScore.addPoint();
                        pipe1.setScored(true);
                        Mix_PlayChannel(-1, pointSfx, 0);
                    }
                    if (player.getX() > pipe2.getX() + pipe2.getWidth() && !pipe2.isScored()) {
                        playerScore.addPoint();
                        pipe2.setScored(true);
                        Mix_PlayChannel(-1, pointSfx, 0);
                    }
                } else if (player.getY() == 512 - 90 - (float)player.getWidth() + 6) {
                    int mouseX = 0, mouseY = 0;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    ScoreBoard.updateScoreBoard();
                    MuchPain.updateMuchPain();
                    if (MuchPain.getCount() > 30 && MuchPain.getCount() % 3 == 1) {
                        playerScore.update();
                    }
                    if (check == true) {
                        blendBg.updateBlendingDark();
                    }
                }
                player.update(pipe1, pipe2, mainScreen);
                window.renderBackGround(bg1);
                window.renderBackGround(bg2);
                window.renderPipe(pipe1);
                window.renderPipe(pipe2);
                window.renderBackGround(base2);
                window.renderBackGround(base1);
                window.renderScore(playerScore, player);
                window.renderBird(player, player.getImgIndex());
                window.renderHearts(heart, heartTexture, player.getLives());
                window.renderMusicToggle(musicToggle, musicOnTexture, musicOffTexture, isMusicOn);

                if (player.isDead() == DEAD) {
                    if (!player.checkSplashWhenDie()) {
                        Mix_PlayChannel(-1, hitSfx, 0);
                        player.setCheckSplash(true);
                        if (player.getY() >= 512 - 90 - player.getWidth() + 6) {
                            lives = 0;
                        } else {
                            lives--;
                            if (player.getX() + player.getWidth() > pipe1.getX() && player.getX() < pipe1.getX() + pipe1.getWidth()) {
                                pipe1.reset(pipe1, pipe2);
                            } else if (player.getX() + player.getWidth() > pipe2.getX() && player.getX() < pipe2.getX() + pipe2.getWidth()) {
                                pipe2.reset(pipe1, pipe2);
                            }
                        }
                        if (lives > 0) {
                            SDL_Delay(40);
                            continue;
                        }
                        window.render(0, 0, things[1]);
                        window.display();
                        SDL_Delay(50);
                        continue;
                    }
                    if (player.getY() == 512 - 90 - (float)player.getWidth() + 6) {
                        if (MuchPain.getCount() > 30 + playerScore.getScore() * 3) {
                            window.render(restartButton.getX(), restartButton.getY(), isRestartHovered ? things[6] : things[5]);
                        }
                        window.renderScoreBoard(ScoreBoard);
                        window.renderMuchPain(MuchPain);
                        if (MuchPain.getCount() > 30) {
                            window.renderScoreWhenDie(playerScore, player);
                            window.renderHighScore(playerScore, player);
                            window.renderMedal(ScoreBoard, things[8], playerScore.getCountingScore(), playerScore.getHighScore());
                        }
                        window.renderBackGround(blendBg);
                    }
                }
            }
        }

        window.display();
        if (MuchPain.getCount() > a + 13 && check == true) {
            if (lives == 0) lives = 3;
            reset();
        }
        SDL_Delay(16.5);
    }
    any.cleanAudio();
    Mix_FreeMusic(bgMusic1);
    Mix_FreeMusic(bgMusic2);
    Mix_FreeMusic(bgMusic3);
    return 0;
}

void gameLoop() {}
