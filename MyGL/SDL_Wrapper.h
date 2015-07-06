#pragma once
#include "SDL.h"
#include "SDL_InitError.h"


class SDL_Wrapper
{
public:
	SDL_Wrapper(Uint32 flags);
	virtual ~SDL_Wrapper();

private:
	static const size_t deviceId = 0;
};

