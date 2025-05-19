#include "AnyThing.hpp"

Anything::Anything(float _srcX, float _srcY, float _dstX, float _dstY, SDL_Texture* _texture)
{
    x = _srcX;
    y = _srcY;
    dstX = _dstX;
    dstY = _dstY;
    texture = _texture;
    currentFrame.x = 0;
    currentFrame.y = 0;
    SDL_QueryTexture(texture, NULL, NULL, &currentFrame.w, &currentFrame.h);
    hovered = false; // Khởi tạo hovered
    count = 0;
    ScoreBoardVelocity = -24;
    MuchPainVelocity = 4;
    inDst = false;
    bgMusic = nullptr;
}

float Anything::getX() { return x; }
float Anything::getY() { return y; }
float Anything::getZ() { return z; }

void Anything::setZ(float _z) { z = _z; }
void Anything::setY(float _y) { y = _y; }
void Anything::setX(float _x) { x = _x; }

int Anything::getWidth() { return getCurrentFrame().w; }
int Anything::getHeight() { return getCurrentFrame().h; }

SDL_Rect Anything::getCurrentFrame() { return currentFrame; }
SDL_Texture* Anything::getTexture() { return texture; }
void Anything::updateScoreBoard()
{
    if (getY() > dstY && count > 11)
    {
        if (getY() < 512 - 67 * 4)
        {
            ScoreBoardVelocity -= 7;
        }
        setY(getY() + ScoreBoardVelocity);
    }
    else if (getY() <= dstY)
    {
        setY(dstY);
        ScoreBoardVelocity = 0;
    }
    count++;
}
void Anything::updateMuchPain()
{
    if (getY() < dstY && count > 4)
    {
        if (getY() > 70)
        {
            MuchPainVelocity -= 0.7;
        }
        setY(getY() + MuchPainVelocity);
    }
    else if (getY() >= dstY)
    {
        setY(dstY);
        MuchPainVelocity = 0;
    }
    count++;
}
bool Anything::isInDst() { return inDst; }

void Anything::reset()
{
    count = 0;
    ScoreBoardVelocity = -24;
    MuchPainVelocity = 4;
    if (getY() < 100)
    {
        setY(55);
    }
    else setY(512);
}

int Anything::getCount() { return count; }

void Anything::setHovered(bool _hovered) { hovered = _hovered; }
bool Anything::isHovered() { return hovered; }

void Anything::initAudio() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    bgMusic = Mix_LoadMUS("asset/music.wav");
    if (!bgMusic) {
        SDL_Log("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
    } else {
        Mix_PlayMusic(bgMusic, -1); // lặp vô hạn
        Mix_VolumeMusic(MIX_MAX_VOLUME / 2); // vừa phải
    }
}

void Anything::cleanAudio() {
    if (bgMusic) {
        Mix_HaltMusic();
        Mix_FreeMusic(bgMusic);
        bgMusic = nullptr;
    }
    Mix_CloseAudio();
}
