#include "stdafx.h"
#include "Window.h"


Window::Window(const std::string& title, int w, int h) : Renderer(w, h)
{
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, NULL);
	

	if (window == nullptr) 
	{
		LOG(FATAL) << "Could not create window:" << SDL_GetError();
	}


	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr)
	{
		LOG(FATAL) << "Could not create renderer:" << SDL_GetError();
	}

	screenBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, w, h);

	if (screenBufferTexture == nullptr)
	{
		LOG(FATAL) << "Could not create screenBufferTexture:" << SDL_GetError();
	}
}


Window::~Window()
{
	SDL_DestroyWindow(window);
}
