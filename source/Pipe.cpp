#include"Pipe.hpp"
Pipe::Pipe(float _x,float _y,std::vector<SDL_Texture*>_tex,float _space)
{
    x=_y;
    y=_y;
    currentFrame.x=0;
    currentFrame.y=0;
    PipeSpace=_space;
    tex=_tex;
    SDL_QueryTexture(tex[0],NULL,NULL,&currentFrame.w,&currentFrame.h);
}
int Pipe::getSize()
{
    return tex.size();
}
float Pipe::getX()
{
    return x;
}
float Pipe::getY()
{
    return y;
}
void Pipe::setY(float _y)
{
    y=_y;
}
void Pipe::setX(float _x)
{
    x=_x;
}
int Pipe::getWidth()
{
    return getCurrentFrame().w;
}
int Pipe::getHeight()
{
    return getCurrentFrame().h;
}
