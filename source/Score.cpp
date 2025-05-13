#include"Score.hpp"

Score::Score(float _x, float _y, TTF_Font* _font, SDL_Color _fontColor)
{
    x = _x;
    y = _y;
    font = _font;
    fontColor = _fontColor;
    score = 0;          // Thêm dòng này để khởi tạo score
    countingScore = 0;   // Thêm dòng này để khởi tạo countingScore
    HighScore = 0;       // Thêm dòng này để khởi tạo HighScore
}

int Score::getHeight()
{
    return height;
}
int Score::getWidth()
{
    return width;
}
float Score::getX()
{
    return x;
}
float Score::getY()
{
    return y;
}
int Score::getHighScore()
{
   return HighScore;
}
void Score::setHighScore()
{
    if (score>HighScore)
    HighScore=score;
}
TTF_Font * Score::getFont()
{
    return font;
}
SDL_Color Score::getFontColor()
{
    return fontColor;
}
int Score::getScore()
{
    return score;
}
void Score::setScore(int _score)
{
    score=_score;
}
int Score::getCountingScore()
{
    return countingScore;
}
void Score::setCountingScore(int x)
{
    countingScore=x;
}
void Score::addPoint()
{
    score++;
    if (score > HighScore) {
        HighScore = score;
    }
}

void Score::update()
{
    if (countingScore < getScore())
    {
        countingScore++;
    }
}

void Score::reset()
{
    score = 0;          // Reset điểm hiện tại về 0
    countingScore = 0;   // Reset điểm đếm về 0
}
