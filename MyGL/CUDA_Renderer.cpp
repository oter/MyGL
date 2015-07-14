#include "stdafx.h"
#include "CUDA_Renderer.h"
#include "common.h"

#include "kernel.cuh"
#include "TrianglesRaster.cuh"

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
	dim3 blocks((getWidth() * getHeight()) / threads.x + 1);
	cudaEventRecord(start);
	clearColorKernel(frameBuffer.getMemPointer(), threads, blocks, *((uchar4*)&color), getWidth() * getHeight());
	cudaEventRecord(stop);
	cudaEventSynchronize(stop);
	cudaDeviceSynchronize(); 
	checkCudaError(cudaGetLastError());
	float milliseconds = 0;
	cudaEventElapsedTime(&milliseconds, start, stop);
	static bool firstTime = false;
	if (!firstTime)
	{
		firstTime = true;
		LOG(INFO) << "First time CUDA clear color (ms): " << milliseconds;
	}
}

void CUDA_Renderer::draw(std::vector<CUDA_ObjectBuffer>& objects, RenderStrategy strategy)
{
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	dim3 threads(1024);
	dim3 blocks(objects.size() / threads.x + 1);
	cudaEventRecord(start);
		
	switch (strategy)
	{
	case LINES_2D_STRATEGY:
		break;
	case TRIANGLES_2D_STRATEGY:
		trianglesRaster2DKernel(objects, blocks, threads, frameBuffer.getMemPointer(), width, height);
		break;
	case LINES_3D_STRATEGY:
		break;
	case TRIANGLES_3D_STRATEGY:
		break;
	default:
		break;
	}

	//drawLinesKernel(frameBuffer.getMemPointer(), threads, blocks, width, (int*)objects.getMemPointer(), colors.getMemPointer(), count);

	cudaEventRecord(stop);
	cudaEventSynchronize(stop);
	cudaDeviceSynchronize();
	checkCudaError(cudaGetLastError());
	float milliseconds = 0;
	cudaEventElapsedTime(&milliseconds, start, stop);



	
	static bool firstTime = false;
	if (!firstTime)
	{
		firstTime = true;
		LOG(INFO) << "First time draw time (ms): " << milliseconds;
	}
}

void CUDA_Renderer::swapBuffers()
{
	frameBuffer.getData(rawFrameBuffer, sizeof(Uint32), height * width);
}
