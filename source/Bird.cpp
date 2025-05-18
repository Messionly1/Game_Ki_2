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
int Bird::getImgIndex() //animation bird
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
        if (changeBirdDirectInMainScreen==40) //0-19 fr^,20-39 fr v
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
    else
    {
        if (velocity>=0)
        {
            if (getAngle()<90)
            {
                if (getAngle()>=-30 &&getAngle()<-27)
                {
                    setAngle(getAngle()+0.55);
                }
                else{
                    setAngle(getAngle()+8.35);
                }
            }
            else
            {
                setAngle(90);
            }
        }
        if (getTopRightY(angle)<512-90-1 && getBottomRightY(angle)<512-90-1 )//chim thua 2 px o cuoi
        {
            setY(getY()+velocity);
            velocity+=GRAVITY;
        }
        if (getY()>=512-90-(float)getWidth()+6)
        {
            setY(512-90-(float)getWidth()+6);
            playerStatus=DEAD;
        }

        if ( (getTopRightX(angle)>b1.getX()+3||getBottomRightX(angle)>b1.getX()+5)
                && (getBottomLeftX(angle)<b1.getX()+(float)b1.getWidth()-5||getTopLeftX(angle)<b1.getX()+(float)b1.getWidth()+5) ) //chim dang nam trong vung chieu ngang cua ong
        {

            if (getTopRightY(angle)<b1.getY()+(float)b1.getHeight()+10|| getTopRightY(angle)>b1.getY()+(float)b1.getHeight()+(float)b1.getPipeSpace())
            {
                playerStatus=DEAD;
            }
              else if (getBottomRightY(angle)<b1.getY()+(float)b1.getHeight()|| getBottomRightY(angle)>b1.getY()+(float)b1.getHeight()+(float)b1.getPipeSpace()-1)
            {
                playerStatus=DEAD;
            }
            else if(playerStatus!=DEAD)
            {
                    playerStatus=ALIVE;

                    if(b1.isScored()==false)
                    {

                        Mix_PlayChannel(-1,pointSfx,0);
                        ActtualScore+=1;
                        b1.setPipeScored(true);
                    }
            }
        }

        else  if ( (getTopRightX(angle)>b2.getX()+3||getBottomRightX(angle)>b2.getX()+5)
                && (getBottomLeftX(angle)<b2.getX()+(float)b2.getWidth()-5||getTopLeftX(angle)<b2.getX()+(float)b2.getWidth()+5) )
        {
            if (getTopRightY(angle)<b2.getY()+(float)b2.getHeight()+10|| getTopRightY(angle)>b2.getY()+(float)b2.getHeight()+(float)b2.getPipeSpace()-1)
            {
              playerStatus=DEAD;
            }
             else  if (getBottomRightY(angle)<b2.getY()+(float)b2.getHeight()|| getBottomRightY(angle)>b2.getY()+(float)b2.getHeight()+(float)b2.getPipeSpace())
            {
                playerStatus=DEAD;
            }
            else if(playerStatus!=DEAD)
            {
                    playerStatus=ALIVE;

                    if(b2.isScored()==false)
                    {
                        Mix_PlayChannel(-1,pointSfx,0);
                        ActtualScore+=1;
                        b2.setPipeScored(true);
                    }
            }
        }
    }
}


SDL_Rect Bird::getCurrentFrame()
{
    return currentFrame;
}
bool Bird::isDead()
{
    return playerStatus==DEAD;
}
void Bird::reset()
{
    velocity=GRAVITY;
    playerStatus=ALIVE;
    ActtualScore=0;
    SplashWhenDie=false;
    angle=0;  //


}

int Bird::getActtualScore()
{
    return ActtualScore;
}
bool Bird::checkSplashWhenDie()
{
    return SplashWhenDie;
}
void Bird::setCheckSplash(bool s)
{
    SplashWhenDie=s;
}


float Bird::getTopRightX(float a)
{
    return getX()+((float)getWidth())/2*(1+cos(a*PI/180))-((float)getHeight())/2*sin(a*PI/180);
}
float Bird::getTopRightY(float a)
{
    return getY()-((float)getWidth())/2*sin(a*PI/180)+(float)getHeight()/2-((float)getHeight())/2*cos(a*PI/180);
}
float Bird::getBottomRightX(float a)
{
    return getX()+((float)getWidth())/2*(1+cos(a*PI/180))+((float)getHeight())/2*sin(a*PI/180);
}
float Bird::getBottomRightY(float a)
{
    return getY()-((float)getWidth())/2*sin(a*PI/180)+(float)getHeight()/2+((float)getHeight())/2*cos(a*PI/180);
}
float Bird::getBottomLeftX(float a)
{
    return getTopRightX(a)-((float)getWidth())*cos(a*PI/180)+((float)getHeight())*sin(a*PI/180);
}
float Bird::getBottomLeftY(float a)
{
    return getBottomRightY(a)+((float)getHeight())*sin(a*PI/180);
}
float Bird::getTopLeftX(float a)
{
    return getTopRightX(a)-((float)getWidth())*sin(a*PI/180);
}
float Bird::getTopLeftY(float a)
{
    return getBottomLeftY(a)-((float)getHeight())*cos(a*PI/180);
}




