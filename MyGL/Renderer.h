#pragma once
#include "CUDA_Renderer.h"

class Renderer : public CUDA_Renderer
{
public:
	explicit Renderer(int w, int h);
	Uint32 exec();
	void render();
	virtual ~Renderer();

private:

protected:
	SDL_Renderer* renderer;
	SDL_Texture* screenBufferTexture;
};

