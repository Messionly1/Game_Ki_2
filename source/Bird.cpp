#include "Bird.hpp"

Bird::Bird(float _x, float _y, std::vector<SDL_Texture*> _tex)
{
    x = _x;
    y = _y;
    tex = _tex;
    currentFrame.x = 0;
    currentFrame.y = 0;
    SDL_QueryTexture(_tex[0], NULL, NULL, &currentFrame.w, &currentFrame.h);
    lives = LIVE_CAP;
}

int Bird::getHeight() { return currentFrame.h; }
int Bird::getWidth() { return currentFrame.w; }
SDL_Texture* Bird::getTex(int index) { return tex[index]; }

int Bird::getImgIndex()
{
    if (changeImg == 12) changeImg = 0;
    int ans = changeImg / 4;
    if (isDead() == ALIVE) changeImg++;
    return ans;
}

float Bird::getY() { return y; }
float Bird::getX() { return x; }
void Bird::setY(float _y) { y = _y; }
void Bird::setX(float _x) { x = _x; }
float Bird::getAngle() { return angle; }
void Bird::setAngle(float _angle) { angle = _angle; }

void Bird::jump()
{
    velocity = -9;
    angle = -30;
}

void Bird::update(Pipe &b1, Pipe &b2, bool mainScreen)
{
    if (invincible) {
        invincibleFrames++;
        if (invincibleFrames > 60) {
            invincible = false;
            invincibleFrames = 0;
        }
    }

    if (mainScreen)
    {
        if (changeBirdDirectInMainScreen == 40)
            changeBirdDirectInMainScreen = 0;

        if (changeBirdDirectInMainScreen / 10 == 0 || changeBirdDirectInMainScreen / 10 == 1)
            setY(getY() - 1.75);
        else
            setY(getY() + 1.75);

        changeBirdDirectInMainScreen++;
    }
    else
    {
        if (velocity >= 0)
        {
            if (getAngle() < 90)
            {
                if (getAngle() >= -30 && getAngle() < -27)
                    setAngle(getAngle() + 0.55);
                else
                    setAngle(getAngle() + 8.35);
            }
            else
            {
                setAngle(90);
            }
        }

        if (getTopRightY(angle) < 512 - 90 - 1 && getBottomRightY(angle) < 512 - 90 - 1)
        {
            setY(getY() + velocity);
            velocity += GRAVITY;
        }

        if (getY() >= 512 - 90 - (float)getWidth() + 6)
        {
            setY(512 - 90 - (float)getWidth() + 6);
            playerStatus = DEAD;
        }
        auto checkPipeCollision = [this](Pipe& pipe) {
    bool collisionX = (getTopRightX(angle) > pipe.getX() + 3 || getBottomRightX(angle) > pipe.getX() + 5) &&
                     (getBottomLeftX(angle) < pipe.getX() + (float)pipe.getWidth() - 5 ||
                      getTopLeftX(angle) < pipe.getX() + (float)pipe.getWidth() + 5);

    if (collisionX)
    {
        bool collisionY = (getTopRightY(angle) < pipe.getY() + (float)pipe.getHeight() + 10 ||
                         getTopRightY(angle) > pipe.getY() + (float)pipe.getHeight() + (float)pipe.getPipeSpace()) ||
                         (getBottomRightY(angle) < pipe.getY() + (float)pipe.getHeight() ||
                         getBottomRightY(angle) > pipe.getY() + (float)pipe.getHeight() + (float)pipe.getPipeSpace() - 1);

        if (collisionY)
        {
            if (lives > 1 && !invincible)
            {
                lives--;
                std::cout << "Lives remaining: " << lives << std::endl; // Debug output
                invincible = true;
                Mix_PlayChannel(-1, hitSfx, 0);
                pipe.setX(-1000);
                pipe.setPipeScored(true);
            }
            else if (!invincible)
            {
                playerStatus = DEAD;
                std::cout << "Bird is dead!" << std::endl; // Debug output
            }
            return true;
        }
        else if (playerStatus != DEAD && !pipe.isScored())
        {
            Mix_PlayChannel(-1, pointSfx, 0);
            ActtualScore += 1;
            pipe.setPipeScored(true);
        }
    }
    return false;
};


        checkPipeCollision(b1);
        checkPipeCollision(b2);
    }
}

SDL_Rect Bird::getCurrentFrame() { return currentFrame; }
bool Bird::isDead() { return playerStatus == DEAD; }

void Bird::reset()
{
    velocity = GRAVITY;
    playerStatus = ALIVE;
    ActtualScore = 0;
    SplashWhenDie = false;
    angle = 0;
    lives = LIVE_CAP;
    invincible = false;
    invincibleFrames = 0;
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




