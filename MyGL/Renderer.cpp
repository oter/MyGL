#include "stdafx.h"
#include "Renderer.h"


Renderer::Renderer(int w, int h) : renderer(nullptr), CUDA_Renderer(w, h)
{}

Uint32 Renderer::exec()
{

	bool b = true;

	//SDL_Render

	
	//int rawLines[] = { 100, 100, 10, 10, 500, 500, 1, 100, 20, 20, 20, 80 };
	//SDL_Color rawColors[] = { { 255, 0, 0, 0 }, { 255, 0, 255, 0 }, { 128, 0, 128, 0 } };

	//int rawLines[] = { rand() % width, rand() % height, rand() % width, rand() % height, 500, 500, 1, 100, 20, 20, 20, 80 };
	//SDL_Color rawColors[] = { { 255, 0, 0, 0 }, { 255, 0, 255, 0 }, { 128, 0, 128, 0 } };

	//int linesCount = 5000000;

	//int* rawLines = new int[linesCount * 4];
	//SDL_Color* rawColors = new SDL_Color[linesCount];

	//for (int i = 0; i < linesCount; i++)
	//{
	//	SDL_Color color = { rand() % 256, rand() % 256, rand() % 256, 0 };
	//	rawColors[i] = color;
	//	for (int j = 0; j < 2; j++)
	//	{
	//		rawLines[i * 4 + j * 2] = rand() % width;
	//		rawLines[i * 4 + j * 2 + 1] = rand() % height;
	//	}
	//}

	//CUDA_Buffer lines;
	//CUDA_Buffer colors;

	//lines.setData(rawLines, sizeof(int), linesCount * 4);
	//colors.setData(rawColors, sizeof(SDL_Color), linesCount);

	//delete[] rawLines;
	//delete[] rawColors;

	float vertices[] = {-0.5f, -0.9f, 0.5f, -0.8f, 0.3f, 0.7f};
	int indeces[] = {0, 1, 2};

	std::vector<CUDA_ObjectBuffer> objects;

	CUDA_ObjectBuffer object;

	CUDA_ObjectBuffer::loadObjects(std::string("cube.obj"), objects);
	
	object.vertices.setData(vertices, sizeof(float), 6);
	object.indices.setData(indeces, sizeof(int), 3);
	object.count = 1;

	objects.push_back(object);



	clearColor({ 0, 255, 0, 0 });
	draw(objects, TRIANGLES_2D_STRATEGY);

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
	SDL_UpdateTexture(screenBufferTexture, nullptr, rawFrameBuffer, width * sizeof(Uint32));

	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, screenBufferTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

Renderer::~Renderer()
{
}
