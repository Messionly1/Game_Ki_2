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

void Background::setX(int _x)
{
    x=_x;
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
    if(Background::getX()==-288)
    {
        Background::setX(288);
    }
    Background::setX(Background::getX()-1);
}
void Background::updateBase()
{
    if(Background::getX()==-288)
    {
        Background::setX(288);
    }
    Background::setX(Background::getX()-3);

}
SDL_Texture* Background::getTex()
{
   return texture;
}
void Background::updateBlendingDark()
{
    if(b+19>255)
    {
        b=255;
    }
    else b+=19;
    SDL_SetTextureAlphaMod(texture,b);

}
void Background::updateBlendingLight()
{
    if(a-19<0)
    {
        a=0;
    }
    else a-=19;
    SDL_SetTextureAlphaMod(texture,a);
}
void Background::reset()
{
    a=255;
    b=0;
}
