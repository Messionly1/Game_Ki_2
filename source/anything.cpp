#include"AnyThing.hpp"

Anything::Anything(float _srcX,float _srcY,float _dstX,float _dstY, SDL_Texture *_texture)
{
    x=_srcX;
    y=_srcY;
    dstX=_dstX;
    dstY=_dstY;
    texture=_texture;
    currentFrame.x=0;
    currentFrame.y=0;
    SDL_QueryTexture(texture,NULL,NULL,&currentFrame.w,&currentFrame.h);
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
SDL_Texture* Anything::getTex() { return texture; }
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

