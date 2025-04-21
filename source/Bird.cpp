#include"Bird.hpp"
Bird::Bird(float _x,float _y,std::vector<SDL_Texture*>_tex)
{
    x=_x;
    y=_y;

    tex=_tex;
    currentFrame.x=0;
    currentFrame.y=0;
    SDL_QueryTexture(_tex[0],NULL,NULL,&currentFrame.w,&currentFrame.h);
}
int Bird::getHeight()
{
    return currentFrame.h;
}
int Bird::getWidth()
{
    return currentFrame.w;
}
SDL_Texture * Bird::getTex(int index)
{
    return tex[index];
}


