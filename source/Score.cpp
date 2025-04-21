#include"Score.hpp"

Score::Score(float _x, float  _y,TTF_Font* _font,SDL_Color _fontColor)
{
    x=_x;
    y=_y;
    font=_font;
    fontColor=_fontColor;
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
