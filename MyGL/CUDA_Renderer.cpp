#include "stdafx.h"
#include "CUDA_Renderer.h"

#include "kernel.cuh"

void checkCudaError(cudaError_t err) {
	if (err != cudaSuccess) 
	{
		LOG(FATAL) << "CUDA error: " << cudaGetErrorString(err) << " ";
	}
}


CUDA_Renderer::CUDA_Renderer(int w, int h) : width(w), height(h)
{
	init();

	frameBuffer.malloc(sizeof(Uint32), width * height);

	rawFrameBuffer = new Uint32[width * height];
	memset(rawFrameBuffer, 0xFFFFFFFF, sizeof(Uint32) * width * height);
	rawFrameBuffer[40] = 7777777;
	rawFrameBuffer[41] = 7777777;
	rawFrameBuffer[42] = 7777777;
	rawFrameBuffer[43] = 7777777;
	rawFrameBuffer[44] = 7777777;
	rawFrameBuffer[45] = 6626265;
	rawFrameBuffer[46] = 0x00FF00FF;
	rawFrameBuffer[47] = 0x00FF00FF;
	rawFrameBuffer[48] = 0x00FF00FF;

	frameBuffer.setData(0xFFFFFFFF);
}


CUDA_Renderer::~CUDA_Renderer()
{
	frameBuffer.free();
	delete[] rawFrameBuffer;
}

bool CUDA_Renderer::init()
{
	static bool inited = false;
	if (!inited)
	{
		int GPUsCount = 0;
		cudaGetDeviceCount(&GPUsCount);
		if (GPUsCount < 1)
		{
			LOG(FATAL) << "No CUDA compatible devices in system were detected!";
		}
		LOG(INFO) << "Number of CUDA devices: " << GPUsCount;
		for (int i = 0; i < GPUsCount; i++)
		{
			cudaDeviceProp prop;
			cudaGetDeviceProperties(&prop, i);
			LOG(INFO) << "   " << i << ": " << prop.name;
		}
		LOG(INFO) << "Number of CPUs: " << omp_get_num_procs();

		if (cudaSetDevice(0) != cudaSuccess) {
			LOG(FATAL) << "cudaSetDevice failed!";
		}
	}

	return true;
}

void CUDA_Renderer::clearColor(SDL_Color color)
{
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	dim3 threads(1024);
	dim3 blocks((getWidth() * getHeight()) / threads.x);
	cudaEventRecord(start);
	clearColorKernel(frameBuffer.getMemPointer(), threads, blocks, *((uchar4*)&color), getWidth() * getHeight());
	cudaEventRecord(stop);
	cudaEventSynchronize(stop);
	cudaDeviceSynchronize(); 
	checkCudaError(cudaGetLastError());
	float milliseconds = 0;
	cudaEventElapsedTime(&milliseconds, start, stop);
	LOG(INFO) << "CUDA time simple (ms): " << milliseconds << std::endl;

}

void CUDA_Renderer::swapBuffers()
{
	frameBuffer.getData((void**)&rawFrameBuffer, sizeof(Uint32), height * width);
}
