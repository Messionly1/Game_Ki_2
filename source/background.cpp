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
