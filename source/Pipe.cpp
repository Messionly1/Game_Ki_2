#include"Pipe.hpp"

Pipe::Pipe(float _x, float _y, std::vector<SDL_Texture*> _tex, float _space)
{
    x = _x;
    y = _y;
    currentFrame.x = 0;
    currentFrame.y = 0;
    PipeSpace = _space;
    tex = _tex;
    SDL_QueryTexture(tex[0], NULL, NULL, &currentFrame.w, &currentFrame.h);
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
    y = _y;
}

void Pipe::setX(float _x)
{
    x = _x;
}

int Pipe::getWidth()
{
    return getCurrentFrame().w;
}

int Pipe::getHeight()
{
    return getCurrentFrame().h;
}

SDL_Texture* Pipe::getTex(int index)
{
    return tex[index];
}

SDL_Rect Pipe::getCurrentFrame()
{
    return currentFrame;
}
void Pipe::update(int index)
{
    if(getX() > -static_cast<float>(getWidth()))
    {
        setX(getX() + velocity);

        if(getMovingPipe())
        {
            setY(getY() + (0.9 * moveDirection));

            if (getY() > 512 - 90 - 30 - (int)PipeSpace - 320)
            {
                setY(512 - 90 - 30 - (int)PipeSpace - 320);
                moveDirection = -1;
            }
            else if (getY() < -220)
            {
                setY(-220);
                moveDirection = 1;
            }
        }
    }
    else
    {
        setMovingPipe(false);
        setX(340 - 52);
        setY(static_cast<float>(Pipe::getPipeRandom(-(320 - 30), 512 - 90 - 30 - (int)PipeSpace - 320)));
        setPipeScored(false);
    }
}

float Pipe::getPipeSpace()
{
    return PipeSpace;
}

int Pipe::getPipeRandom(int min_num, int max_num)
{
    srand(time(NULL));
    int result = (rand() % (max_num - min_num)) + min_num;
    int chance = rand() % 100;
    if (chance < 65) {
        setMovingPipe(true);
        moveDirection = (rand() % 2) ? 1 : -1;
    } else {
        setMovingPipe(false);
    }
    return result;
}

void Pipe::reset(Pipe& p1, Pipe& p2)
{
    p1.setX(288); p1.setY(-220);
    p2.setX(288 + 170); p2.setY(-90);
    PipeScored = false;
    setMovingPipe(true);
    p1.moveDirection = (rand() % 2) ? 1 : -1;
    p2.moveDirection = (rand() % 2) ? 1 : -1;
}

bool Pipe::isScored()
{
    return PipeScored;
}

void Pipe::setPipeScored(bool s)
{
    PipeScored = s;
}

void Pipe::setMovingPipe(bool s)
{
    MovingPipe = s;
}

bool Pipe::getMovingPipe()
{
    return MovingPipe;
}

