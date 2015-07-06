#pragma once
#include <exception>
#include <string>


class SDL_InitError : public std::exception
{
public:
	SDL_InitError();
	SDL_InitError(const std::string&);

	virtual ~SDL_InitError() throw();
	virtual const char* what() const throw();
private:
	std::string message;
};

