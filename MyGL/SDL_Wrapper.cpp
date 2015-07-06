#include "stdafx.h"
#include "SDL_Wrapper.h"

SDL_Wrapper::SDL_Wrapper(Uint32 flags)
{
	if (SDL_Init(flags) != 0)
	{
		throw SDL_InitError();
	}
}


SDL_Wrapper::~SDL_Wrapper()
{
	SDL_Quit();
}
