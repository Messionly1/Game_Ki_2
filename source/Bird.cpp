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
int Bird::getImgIndex()//nao sửa mỗi hàm này thôi
{
    if (changeImg==12)
    {
        changeImg=0;
    }
    int ans= changeImg/4;
    if (isDead()==ALIVE)
    {
        changeImg++;
    }
    return ans;
}
float Bird::getY()
{
    return y;
}
float Bird::getX()
{
    return x;
}
void Bird::setY(float _y)
{
   y=_y;
}
void Bird::setX(float _x)
{
   x=_x;
}
float Bird::getAngle()
{
    return angle;
}
void Bird::setAngle(float _angle)
{
    angle=_angle;
}
void Bird::jump()
{
    velocity=-9;
    angle=-30;
}
void Bird::update(Pipe &b1,Pipe &b2,bool mainScreen)
{
    if(mainScreen==true)
    {
        if (changeBirdDirectInMainScreen==40)
        {
            changeBirdDirectInMainScreen=0;
        }
        if (changeBirdDirectInMainScreen /10==0)
        {
            setY(getY()-1.75);
        }
        else if ( changeBirdDirectInMainScreen /10==1)
        {
            setY(getY()-1.75);
        }
        else
        {
            setY(getY()+1.75);
        }
        changeBirdDirectInMainScreen++;
    }



