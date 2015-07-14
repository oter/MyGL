#pragma once
#include "CUDA_Buffer.h"
#include "common.h"
#include "CUDA_ObjectBuffer.h"




class CUDA_Renderer
{
public:
	CUDA_Renderer(int w, int h);
	virtual ~CUDA_Renderer();

	static bool init();

	void clearColor(SDL_Color color);

	void draw(std::vector<CUDA_ObjectBuffer>& objects, RenderStrategy strategy);

	void swapBuffers();

protected:
	int width;
	int height;
	int getWidth() const { return width; }
	void setWidth(int val) { width = val; }

	int getHeight() const { return height; }
	void setHeight(int val) { height = val; }

	Uint32* rawFrameBuffer;

private:
	CUDA_Buffer frameBuffer;
};

