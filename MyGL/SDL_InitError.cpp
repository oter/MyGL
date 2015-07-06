#include "stdafx.h"
#include "SDL_InitError.h"


SDL_InitError::SDL_InitError() : exception(), message(SDL_GetError())
{}

SDL_InitError::SDL_InitError(const std::string& message) : exception(), message(message)
{}

const char* SDL_InitError::what() const throw()
{
	return message.c_str();
}

SDL_InitError::~SDL_InitError() throw()
{}
