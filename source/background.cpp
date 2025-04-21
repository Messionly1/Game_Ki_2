#include"Background.hpp"
Background::Background(int _x,int _y,SDL_Texture *tex)
{
    x=_x;
    y=_y;
    texture=tex;
    currentFrame.x=0;
    currentFrame.y=0;
    SDL_QueryTexture(tex,NULL,NULL,&currentFrame.w,&currentFrame.h);
    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
}
int Background::getX()
{
    return x;
}
int Background::getY()
{
    return y;
}
int Background::getZ()
{
    return z;
}
void Background::setX(int _x)
{
    x=_x;
}
void Background::setZ(int_z)
{
    z=_z;
}

SDL_Rect Background:: getCurrentFrame()
{
    return currentFrame;
}
int Background::getW()
{
    return getCurrentFrame().w;
}
int Background::getH()
{
    return getCurrentFrame().h;
}
void Background::updateMainBg()
{
    if(Background::getX()==-512)
    {
        Background::setX(512);
    }
    Background::setX(Background::getX()-1);
}

