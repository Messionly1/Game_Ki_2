#include"Pipe.hpp"
const int MIN_PIPE_GAP = 100;
const int MIN_PIPE_SPACE = 50;
const int MIN_GAP = 150;
Pipe::Pipe(float _x, float _y, std::vector<SDL_Texture*> _tex, float _space)
{
    x = _x;
    y = _y;
    currentFrame.x = 0;
    currentFrame.y = 0;
    PipeSpace = _space;
    tex = _tex;
    SDL_QueryTexture(tex[0], NULL, NULL, &currentFrame.w, &currentFrame.h);

    isRandomSize = (rand() % 100) < 70;

    if(isRandomSize) {
        sizeMultiplier = 0.7f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(1.5f - 0.7f)));
        currentFrame.w = static_cast<int>(currentFrame.w * sizeMultiplier);
        currentFrame.h = static_cast<int>(currentFrame.h * sizeMultiplier);
    }
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

void Pipe::setRandomSize(bool random) {
    isRandomSize = random;
    if(isRandomSize && sizeMultiplier == 1.0f) {
        sizeMultiplier = 0.7f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(1.5f - 0.7f)));
        currentFrame.w = static_cast<int>(currentFrame.w * sizeMultiplier);
        currentFrame.h = static_cast<int>(currentFrame.h * sizeMultiplier);
    }
}

bool Pipe::getRandomSize() const {
    return isRandomSize;
}

float Pipe::getSizeMultiplier() const {
    return sizeMultiplier;
}

void Pipe::update(int index)
{
    if(getX() > -static_cast<float>(getWidth()))
    {
        setX(getX() + velocity);

        if(getMovingPipe())
        {
            const int MIN_Y = -220;
            const int MAX_Y = 512 - 90 - 30 - static_cast<int>(PipeSpace) - 320;

            setY(getY() + (0.9 * moveDirection));

            if (getY() > MAX_Y)
            {
                setY(MAX_Y);
                moveDirection = -1;
            }
            else if (getY() < MIN_Y)
            {
                setY(MIN_Y);
                moveDirection = 1;
            }
            const int MIN_GAP = 150;
            if (PipeSpace < MIN_GAP) {
                PipeSpace = MIN_GAP;
            }
        }
    }
    else
    {
        setMovingPipe(false);
        setX(340 - 52);
        int newY = static_cast<int>(Pipe::getPipeRandom(-220, 512 - 90 - 30 - static_cast<int>(PipeSpace) - 320));
        setY(static_cast<float>(newY));
        setPipeScored(false);
    }
}

float Pipe::getPipeSpace()
{
    return PipeSpace;
}

int Pipe::getPipeRandom(int min_num, int max_num)
{
    const int MIN_GAP = 150;
    if (PipeSpace < MIN_GAP) {
        PipeSpace = MIN_GAP;
    }

    srand(time(NULL));
    int result = (rand() % (max_num - min_num)) + min_num;
    int chance = rand() % 100;

    if (result > max_num - MIN_GAP) {
        result = max_num - MIN_GAP;
    }
    else if (result < min_num + MIN_GAP) {
        result = min_num + MIN_GAP;
    }

    if (chance < 65) {
        setMovingPipe(true);
        moveDirection = (rand() % 100 < 70) ? -1 : 1;
    } else {
        setMovingPipe(false);
    }
    return result;
}
void Pipe::reset(Pipe& p1, Pipe& p2)
{
    p1.setX(288);
    p2.setX(288 + MIN_PIPE_GAP + rand() % 50);

    if (p1.getPipeSpace() < MIN_PIPE_SPACE) {
        p1.PipeSpace = MIN_PIPE_SPACE;
    }
    if (p2.getPipeSpace() < MIN_PIPE_SPACE) {
        p2.PipeSpace = MIN_PIPE_SPACE;
    }
    p1.PipeScored = false;
    p2.PipeScored = false;


    bool randomSize = (rand() % 100) < 80;
    p1.setRandomSize(randomSize);
    p2.setRandomSize(randomSize);

    p1.setMoveDirection((rand() % 100 < 70) ? -1 : 1);
    p2.setMoveDirection((rand() % 100 < 70) ? -1 : 1);
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
