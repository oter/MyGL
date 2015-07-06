#include "stdafx.h"
#include "SDL_Wrapper.h"
#include "SDL_InitError.h"
#include "Window.h"

std::string windowTitle = "Basic Graphic Library";
int windowW = 1024;
int windowH = 1024;

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char *argv[])
{
	LOG(INFO) << "----START----";

	int retCode = 0;

	try
	{
		LOG(INFO) << "SDL initialization";
		SDL_Wrapper sdl(SDL_INIT_VIDEO | SDL_INIT_TIMER);

		Window window(windowTitle, windowW, windowH);

		retCode = window.exec();
	}
	catch (const SDL_InitError& e)
	{
		LOG(ERROR) << "Error while initializing SDL:  " << e.what();
	}
	LOG(INFO) << "----CLOSE----";

	return retCode;
}