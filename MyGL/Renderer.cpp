#include "stdafx.h"
#include "Renderer.h"


Renderer::Renderer(int w, int h) : renderer(nullptr), CUDA_Renderer(w, h)
{}

Uint32 Renderer::exec()
{

	bool b = true;

	//SDL_Render

	clearColor({ 0, 255, 0, 0 });

	while (b)
	{
		SDL_Delay(1);

		render();

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


	return 0;
}

void Renderer::render()
{
	swapBuffers();
	SDL_UpdateTexture(screenBufferTexture, nullptr, (void*)rawFrameBuffer, width * sizeof(Uint32));



	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, screenBufferTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

Renderer::~Renderer()
{
}
