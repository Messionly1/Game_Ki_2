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

