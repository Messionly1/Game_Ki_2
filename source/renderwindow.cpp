#include"RenderWindow.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

 RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
{
window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
void RenderWindow::render(float p_x, float p_y, SDL_Texture* p_tex)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	dst.x = p_x;
	dst.y = p_y;
	dst.w = src.w;
	dst.h = src.h;
	SDL_RenderCopy(renderer,p_tex,&src,&dst);

}
void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}
SDL_Renderer *RenderWindow::getRenderer()
{
    return renderer;
}
void RenderWindow::clear()
{
	SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);
	SDL_RenderClear(renderer);
}
SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}
 void RenderWindow::renderBird(Bird &bird,int index)
{
    SDL_Rect src;
    src.x=bird.getCurrentFrame().x;
    src.y=bird.getCurrentFrame().y;
    src.w=bird.getCurrentFrame().w;
    src.h=bird.getCurrentFrame().h;
    SDL_Rect dst;
    dst.x=bird.getX();
    dst.y=bird.getY();
    dst.w=bird.getCurrentFrame().w;
    dst.h=bird.getCurrentFrame().h;

SDL_RenderCopyEx(RenderWindow::renderer,bird.getTex(index),&src,&dst,static_cast<double>(bird.getAngle()),NULL,SDL_FLIP_NONE);
}
void RenderWindow::renderBackGround(Background &bg)
{
    SDL_Rect src;
    src.x=bg.getCurrentFrame().x;
    src.y=bg.getCurrentFrame().y;
    src.w=bg.getCurrentFrame().w;
    src.h=bg.getCurrentFrame().h;
    SDL_Rect dst;
    dst.x=bg.getX();
    dst.y=bg.getY();
    dst.w=bg.getCurrentFrame().w;
    dst.h=bg.getCurrentFrame().h;
    SDL_RenderCopy(RenderWindow::renderer,bg.getTex(),&src,&dst);

}




