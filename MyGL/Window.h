#pragma once
#include "Renderer.h"


class Window : public Renderer
{
public:
	Window(const std::string& title, int w, int h);
	virtual ~Window();

private:
	SDL_Window* window;
};

