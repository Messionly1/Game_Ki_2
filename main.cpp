#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "source/RenderWindow.hpp"
#include <vector>
#include "source/Anything.hpp"

using namespace std;

// Biến toàn cục
RenderWindow window("FLAPPY BIRD", 288, 512);
SDL_Texture *city = nullptr;
SDL_Texture *ground = nullptr;
SDL_Texture *medal = nullptr;
SDL_Texture *heartTexture = nullptr;

Mix_Chunk *jumpSfx = nullptr;
Mix_Chunk *hitSfx = nullptr;
Mix_Chunk *swooshSfx = nullptr;
Mix_Chunk *pointSfx = nullptr;
Mix_Chunk *dieSfx = nullptr;
Mix_Music *bgMusic = nullptr;

vector<SDL_Texture*> things; // Các texture chung
vector<SDL_Texture*> p;      // Texture cho ống (pipes)
vector<SDL_Texture*> bird;   // Texture cho chim

int lives = 3; // Số mạng của người chơi

// Khởi tạo các đối tượng
bool mainScreen = true; // Trạng thái màn hình chính (trước khi chơi)
Anything heart(0, 0, 24, 24, nullptr); // Đối tượng hiển thị trái tim (lives)
Anything ScoreBoard(288/2 - 226/2, 512, 288/2 - 226/2, 512 - 90 - 114 - 130, nullptr);
Anything MuchPain(288/2 - 186/2, 55, 288/2 - 186/2, 80, nullptr);
Bird player(50, 512/2 - 18, bird);
Background bg1(0, 0, nullptr), bg2(288, 0, nullptr), blendBg(0, 0, nullptr);
Background base1(0, 512 - 90, nullptr), base2(288, 512 - 90, nullptr);
Pipe pipe1(288, -220, p, 112), pipe2(288 + 170, -90, p, 112);
TTF_Font *flappyFont = nullptr;
SDL_Color textColor = {255, 255, 255};
Score playerScore(144 - 9, 60, nullptr, textColor);
bool pipe1Scored = false;
bool pipe2Scored = false;
bool check = false, hitSFx = false, swooshSFx = false;
int a = 0;
bool delayAfterDeath = false; // Biến để kiểm soát delay khi chết
Uint32 delayStartTime = 0;   // Thời gian bắt đầu delay

// Hàm khởi tạo
bool init() {
    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }
    std::cout << "SDL initialized successfully." << std::endl;

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cout << "IMG_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }
    std::cout << "IMG initialized successfully." << std::endl;

    if (TTF_Init() < 0) {
        std::cout << "TTF_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }
    std::cout << "TTF initialized successfully." << std::endl;

    // Load texture cho pipes
    p.push_back(window.loadTexture("asset/FbUpperPipe.png"));
    if (!p[0]) {
        std::cout << "Failed to load FbUpperPipe.png, using fallback." << std::endl;
        p[0] = window.loadTexture("asset/WhiteTex.png");
    }
    p.push_back(window.loadTexture("asset/FbUnderPipe.png"));
    if (!p[1]) {
        std::cout << "Failed to load FbUnderPipe.png, using fallback." << std::endl;
        p[1] = window.loadTexture("asset/WhiteTex.png");
    }
    if (!p[0] || !p[1]) {
        std::cout << "Critical: Failed to load pipe textures!" << std::endl;
        return false;
    }

    // Load texture cho chim
    bird.push_back(window.loadTexture("asset/FbBlueBird1.png"));
    if (!bird[0]) bird[0] = window.loadTexture("asset/WhiteTex.png");
    bird.push_back(window.loadTexture("asset/FbBlueBird2.png"));
    if (!bird[1]) bird[1] = window.loadTexture("asset/WhiteTex.png");
    bird.push_back(window.loadTexture("asset/FbBlueBird3.png"));
    if (!bird[2]) bird[2] = window.loadTexture("asset/WhiteTex.png");
    bird.push_back(window.loadTexture("asset/FbYellowBird1.png"));
    if (!bird[3]) bird[3] = window.loadTexture("asset/WhiteTex.png");
    bird.push_back(window.loadTexture("asset/FbYellowBird2.png"));
    if (!bird[4]) bird[4] = window.loadTexture("asset/WhiteTex.png");
    bird.push_back(window.loadTexture("asset/FbYellowBird3.png"));
    if (!bird[5]) bird[5] = window.loadTexture("asset/WhiteTex.png");
    bird.push_back(window.loadTexture("asset/FbRedBird1.png"));
    if (!bird[6]) bird[6] = window.loadTexture("asset/WhiteTex.png");
    bird.push_back(window.loadTexture("asset/FbRedBird2.png"));
    if (!bird[7]) bird[7] = window.loadTexture("asset/WhiteTex.png");
    bird.push_back(window.loadTexture("asset/FbRedBird3.png"));
    if (!bird[8]) bird[8] = window.loadTexture("asset/WhiteTex.png");
    for (size_t i = 0; i < bird.size(); ++i) {
        if (!bird[i]) {
            std::cout << "Critical: Failed to load bird texture " << i << "!" << std::endl;
            return false;
        }
    }

    // Load texture chung
    things.push_back(window.loadTexture("asset/FbTapToPlay.png"));   // 0
    if (!things[0]) things[0] = window.loadTexture("asset/WhiteTex.png");
    things.push_back(window.loadTexture("asset/WhiteTex.png"));      // 1
    if (!things[1]) {
        std::cout << "Critical: WhiteTex.png failed to load!" << std::endl;
        return false; // WhiteTex là fallback, nếu không load được thì không thể tiếp tục
    }
    things.push_back(window.loadTexture("asset/ScoreBoard.png"));    // 2
    if (!things[2]) things[2] = things[1];
    things.push_back(window.loadTexture("asset/FbGetReady.png"));    // 3
    if (!things[3]) things[3] = things[1];
    things.push_back(window.loadTexture("asset/FbMuchPain.png"));    // 4
    if (!things[4]) things[4] = things[1];
    things.push_back(window.loadTexture("asset/FbPlayButton.png"));  // 5
    if (!things[5]) things[5] = things[1];
    things.push_back(window.loadTexture("asset/Fb2ndPlayButton.png"));// 6
    if (!things[6]) things[6] = things[1];
    things.push_back(window.loadTexture("asset/BlendBg.png"));       // 7
    if (!things[7]) things[7] = things[1];
    things.push_back(window.loadTexture("asset/medal.png"));         // 8
    if (!things[8]) things[8] = things[1];

    // Load các texture toàn cục
    city = window.loadTexture("asset/pinknightbg.png");
    if (!city) {
        std::cout << "Failed to load pinknightbg.png, using fallback." << std::endl;
        city = things[1];
    }
    ground = window.loadTexture("asset/pinkbase2.png");
    if (!ground) {
        std::cout << "Failed to load pinkbase2.png, using fallback." << std::endl;
        ground = things[1];
    }
    medal = window.loadTexture("asset/medal.png");
    if (!medal) {
        std::cout << "Failed to load medal.png, using fallback." << std::endl;
        medal = things[1];
    }

    // Load texture trái tim (lives)
    heartTexture = window.loadTexture("asset/heart.png");
    if (!heartTexture) {
        std::cout << "Failed to load heart.png: " << SDL_GetError() << std::endl;
        heartTexture = things[1];
    }
    heart = Anything(0, 0, 24, 24, heartTexture);

    // Khởi tạo các đối tượng với texture
    ScoreBoard = Anything(288/2 - 226/2, 512, 288/2 - 226/2, 512 - 90 - 114 - 130, things[2]);
    MuchPain = Anything(288/2 - 186/2, 55, 288/2 - 186/2, 80, things[4]);
    bg1 = Background(0, 0, city);
    bg2 = Background(288, 0, city);
    blendBg = Background(0, 0, things[7]);
    base1 = Background(0, 512 - 90, ground);
    base2 = Background(288, 512 - 90, ground);

    // Load font
    flappyFont = TTF_OpenFont("asset/fBirdFont.ttf", 28);
    if (!flappyFont) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }
    playerScore = Score(144 - 9, 60, flappyFont, textColor);
    std::cout << "Font loaded successfully." << std::endl;

    // Load âm thanh
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "Mix_OpenAudio failed: " << Mix_GetError() << std::endl;
        return false;
    }
    std::cout << "Audio initialized successfully." << std::endl;

    jumpSfx = Mix_LoadWAV("asset/wing.wav");
    if (!jumpSfx) std::cout << "Failed to load wing.wav: " << Mix_GetError() << std::endl;
    hitSfx = Mix_LoadWAV("asset/die2.wav");
    if (!hitSfx) std::cout << "Failed to load die2.wav: " << Mix_GetError() << std::endl;
    pointSfx = Mix_LoadWAV("asset/point.wav");
    if (!pointSfx) std::cout << "Failed to load point.wav: " << Mix_GetError() << std::endl;
    swooshSfx = Mix_LoadWAV("asset/swoosh.wav");
    if (!swooshSfx) std::cout << "Failed to load swoosh.wav: " << Mix_GetError() << std::endl;
    dieSfx = Mix_LoadWAV("asset/die.wav");
    if (!dieSfx) std::cout << "Failed to load die.wav: " << Mix_GetError() << std::endl;
    Mix_Volume(-1, MIX_MAX_VOLUME);
    bgMusic = Mix_LoadMUS("asset/music.wav");
    if (!bgMusic) {
        std::cout << "Failed to load music: " << Mix_GetError() << std::endl;
        return false;
    }
    std::cout << "Audio files loaded successfully." << std::endl;

    return true;
}

bool load = init();

// Hàm reset game
void reset() {
    player.reset();
    pipe1.reset(pipe1, pipe2);
    pipe1.setScored(false);
    pipe2.setScored(false);
    ScoreBoard.reset();
    MuchPain.reset();
    mainScreen = true;
    playerScore.reset();
    blendBg.reset();
    a = 0;
    check = false;
    swooshSFx = false;
    lives = 3; // Reset số mạng
    delayAfterDeath = false; // Reset trạng thái delay
}

int main(int argc, char** argv) {
    if (!load) {
        std::cout << "Initialization failed, exiting." << std::endl;
        return 1;
    }

    SDL_Texture* dummyTexture = nullptr;
    Anything any(0, 0, 0, 0, dummyTexture);
    any.initAudio();

    SDL_Event e;
    bool isRunning = true;

    while (isRunning) {
        std::cout << "Loop start" << std::endl;
        window.clear();

        // Kiểm soát delay khi chim chết
        if (delayAfterDeath) {
            if (SDL_GetTicks() - delayStartTime < (lives > 0 ? 250 : 60)) {
                window.display();
                std::cout << "Loop end (delay)" << std::endl;
                SDL_Delay(21);
                continue;
            }
            delayAfterDeath = false; // Kết thúc delay
        }

        while (SDL_PollEvent(&e)) {
            std::cout << "Handling event" << std::endl;
            if (e.type == SDL_QUIT) {
                isRunning = false;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = 0, mouseY = 0;
                SDL_GetMouseState(&mouseX, &mouseY);

                if (mainScreen && e.button.button == SDL_BUTTON_LEFT && SDL_GetTicks() > 200) {
                    mainScreen = false;
                    player.jump();
                    if (jumpSfx) Mix_PlayChannel(-1, jumpSfx, 0);
                } else {
                    if (e.button.button == SDL_BUTTON_LEFT && !player.isDead()) {
                        player.jump();
                        if (jumpSfx) Mix_PlayChannel(-1, jumpSfx, 0);
                    }
                    if (e.button.button == SDL_BUTTON_LEFT &&
                        mouseX > 288/2 - 104/2 && mouseX < 288/2 - 104/2 + 104 &&
                        mouseY > 512 - 90 - 130 + 30 && mouseY < 512 - 90 - 130 + 30 + 58 &&
                        player.isDead() && MuchPain.getCount() > 30 + playerScore.getScore() * 3) {
                        check = true;
                        a = MuchPain.getCount();
                    }
                }
            }
        }

        // Update và render
        if (mainScreen) {
            std::cout << "Rendering main screen" << std::endl;
            if (!swooshSFx) {
                swooshSFx = true;
                if (swooshSfx) Mix_PlayChannel(-1, swooshSfx, 0);
            }
            pipe1.reset(pipe1, pipe2);
            blendBg.updateBlendingLight();
            player.setX(120);
            player.setY(512/2 - 18);
            player.update(pipe1, pipe2, mainScreen);
            bg1.updateMainBg();
            bg2.updateMainBg();
            base1.updateBase();
            base2.updateBase();

            // Render main screen
            window.renderBackGround(bg1);
            window.renderBackGround(bg2);
            window.renderPipe(pipe1);
            window.renderPipe(pipe2);
            window.renderBackGround(base2);
            window.renderBackGround(base1);
            window.renderBird(player, player.getImgIndex());
            window.render(288/2 - 114/2 - 5, 290, things[0]); // "Tap to Play"
            window.render(288/2 - 184/2, 49 + 35, things[3]); // "Get Ready"
            window.renderBackGround(blendBg);
        } else {
            if (!player.isDead()) {
                std::cout << "Rendering game (alive)" << std::endl;
                pipe1.update(1, pipe2);
                pipe2.update(2, pipe1);
                bg1.updateMainBg();
                bg2.updateMainBg();
                base1.updateBase();
                base2.updateBase();

                // Kiểm tra điểm
                if (player.getX() > pipe1.getX() + pipe1.getWidth() && !pipe1.isScored()) {
                    playerScore.addPoint();
                    pipe1.setScored(true);
                    if (pointSfx) Mix_PlayChannel(-1, pointSfx, 0);
                }
                if (player.getX() > pipe2.getX() + pipe2.getWidth() && !pipe2.isScored()) {
                    playerScore.addPoint();
                    pipe2.setScored(true);
                    if (pointSfx) Mix_PlayChannel(-1, pointSfx, 0);
                }

                // Render game
                window.renderBackGround(bg1);
                window.renderBackGround(bg2);
                window.renderPipe(pipe1);
                window.renderPipe(pipe2);
                window.renderBackGround(base2);
                window.renderBackGround(base1);
                window.renderScore(playerScore, player);
                window.renderBird(player, player.getImgIndex());
                window.renderHearts(heart, heartTexture, lives);
            } else if (player.isDead()) {
                std::cout << "Rendering game (dead)" << std::endl;
                window.renderBackGround(bg1);
                window.renderBackGround(bg2);
                window.renderPipe(pipe1);
                window.renderPipe(pipe2);
                window.renderBackGround(base2);
                window.renderBackGround(base1);
                window.renderBird(player, player.getImgIndex());

                if (!player.checkSplashWhenDie()) {
                    if (hitSfx) Mix_PlayChannel(-1, hitSfx, 0);
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
                    if (lives > 0 || lives == 0) {
                        delayAfterDeath = true;
                        delayStartTime = SDL_GetTicks();
                        window.render(0, 0, things[1]);
                    }
                    continue;
                }
                if (player.getY() == 512 - 90 - (float)player.getWidth() + 6) {
                    if (MuchPain.getCount() > 30 + playerScore.getScore() * 3) {
                        window.render(288/2 - 104/2, 512 - 90 - 130 + 30, things[5]);
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
            player.update(pipe1, pipe2, mainScreen);
        }

        // Hiển thị màn hình
        window.display();
        std::cout << "Loop end" << std::endl;

        if (MuchPain.getCount() > a + 13 && check) {
            if (lives == 0) lives = 3;
            reset();
        }

        SDL_Delay(21);
    }

    any.cleanAudio();
    return 0;
}

void gameLoop() {
    // Để trống (có thể mở rộng sau)
}
