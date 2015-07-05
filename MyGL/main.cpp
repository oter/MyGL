#include "stdafx.h"

std::string windowTitle = "Basic Graphic Library";
int windowW = 640;
int windowH = 480;

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char *argv[])
{
	LOG(INFO) << "START";

	SDL_Window *window;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowW, windowH, NULL);

	// Check that the window was successfully made
	if (window == NULL) {
		// In the event that the window could not be made...
		LOG(INFO) <<  "Could not create window:" << SDL_GetError();
		return 1;
	}

	bool b = true;

	while (b)
	{
		SDL_Delay(1);
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				break;
			case SDL_KEYUP:
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					LOG(INFO) << "escape";
					b = false;
				}
				break;
			case SDL_QUIT:
				b = false;
				break;
			case SDL_WINDOWEVENT_HIDDEN:
				b = false;
				break;
			default:
				break;
			}
		}
	}

	
	SDL_DestroyWindow(window);
	SDL_Quit();



	LOG(INFO) << "----CLOSE----";

	return 0;
}