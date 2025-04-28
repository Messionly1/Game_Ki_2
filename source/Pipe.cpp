#include"Pipe.hpp"

Pipe::Pipe(float _x,float _y,std::vector<SDL_Texture*>_tex,float _space)
{
    x=_x;
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
SDL_Texture * Pipe::getTex(int index)
{
    return tex[index];
}
SDL_Rect Pipe::getCurrentFrame()
{
    return currentFrame;
}
void Pipe::update(int index)
{
   if(getX()>-static_cast<float>(getWidth()))
   {
        setX(getX()+velocity);
        if(getMovingPipe()==true&& index==1)
        {
            setY(getY()+0.9);
            if (getY()>512-90-30-(int)PipeSpace-320)
            {
                setY(512-90-30-(int)PipeSpace-320);
            }
        }
   }
   else
   {
       setMovingPipe(false);
       setX(340-52);
       setY(static_cast<float>(Pipe::getPipeRandom(-(320-30),512-90-30-(int)PipeSpace-320)));//30:dau pipe,90:base
   }
}
float Pipe::getPipeSpace()
{
    return PipeSpace;
}
int Pipe::getPipeRandom(int min_num, int max_num)
{
    srand(time(NULL));
    int result;
    PipeScored = false;

    // Không còn random thêm ±20 hay -15 nữa.
    result = (rand() % (max_num - min_num)) + min_num;

    count++;

    // <<< Luôn luôn cho phép pipe di chuyển >>>
    setMovingPipe(true);

    return result;
}


void Pipe::reset(Pipe &p1,Pipe &p2)
{
    p1.setX(288);
    p1.setY(-220);
    p2.setX(288+170);
    p2.setY(-90);
    PipeScored=false;
    MovingPipe=true;
}
bool Pipe::isScored()
{
    return PipeScored;
}
void Pipe::setPipeScored(bool s)
{
    PipeScored=s;
}
void Pipe::setMovingPipe(bool s)
{
    MovingPipe=s;
}
bool Pipe::getMovingPipe()
{
    return MovingPipe;
}
