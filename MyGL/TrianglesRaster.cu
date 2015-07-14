#include "stdafx.h"

#include "kernels_common.cuh"
#include "TrianglesRaster.cuh"

#include "cuda.h"
#include "cuda_runtime.h"
#include "math_functions.h"
#include "device_launch_parameters.h"

__global__ void trianglesRaster2DKernel(uchar4* frameBuffer, float2* vertices, int* indices, float2* normals, int2* textCoords, int count, int width, int height)
{
	int i = blockDim.x * blockIdx.x + threadIdx.x;
	

	if (i >= count)
	{
		return;
	}
	frameBuffer[i] = { 0, 0, 255, 0 };
	int2 p1, p2, p3;
	const int index = i * 3;
	p1.x = ((vertices[indices[index]].x + 1.0f) / 2) * width;
	p1.y = ((vertices[indices[index]].y + 1.0f) / 2) * height;

	p2.x = ((vertices[indices[index + 1]].x + 1.0f) / 2) * width;
	p2.y = ((vertices[indices[index + 1]].y + 1.0f) / 2) * height;

	p3.x = ((vertices[indices[index + 2]].x + 1.0f) / 2) * width;
	p3.y = ((vertices[indices[index + 2]].y + 1.0f) / 2) * height;

	if ((p1.y == p2.y) && (p1.y == p3.y))
	{
		return; // Invalid triangle
	}

	// sort the vertices, (x1, y1), (x2, y2), (x3, y3)
	if (p1.y > p2.y)
	{
		cudaSwap(p1, p2);
	}
	if (p1.y > p3.y)
	{
		cudaSwap(p1, p3);
	}
	if (p2.y > p3.y)
	{
		cudaSwap(p2, p3);
	}

	int total_height = p3.y - p1.y;
	for (int i = 0; i < total_height; i++) 
	{
		bool second_half = i > p2.y - p1.y || p2.y == p1.y;
		int segment_height = second_half ? p3.y - p2.y : p2.y - p1.y;
		float alpha = (float)i / total_height;
		float beta = (float)(i - (second_half ? p2.y - p1.y : 0)) / segment_height; // be careful: with above conditions no division by zero here

		//int ax1 = x1 + ()
		int2 a = cudaAdd(p1, cudaMult(cudaSub(p3, p1), alpha));
		int2 b = second_half ? cudaAdd(p2, cudaMult(cudaSub(p3, p2), beta)) : cudaAdd(p1, cudaMult(cudaSub(p2, p1), beta));
		if (a.x > b.x)
		{
			cudaSwap(a, b);
		}
		for (int j = a.x; j <= b.x; j++) 
		{
			int offset = (p1.y + i) * width + j;
			if (offset >= width * height)
			{
				continue;
			}
			frameBuffer[offset] = {255, 0, 0, 0};
			//image.set(j, t0.y + i, color); // attention, due to int casts t0.y+i != A.y
		}
	}



	//int a = 
}

void trianglesRaster2DKernel(std::vector<CUDA_ObjectBuffer>& objects, dim3 blocks, dim3 threads, uchar4* frameBuffer, int width, int height)
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		
		trianglesRaster2DKernel << <blocks, threads >> >(frameBuffer, (float2*)objects.at(i).vertices.getMemPointer(), (int*)objects.at(i).indices.getMemPointer(),
			(float2*)objects.at(i).normals.getMemPointer(), (int2*)objects.at(i).textCoords.getMemPointer(), objects.at(i).count, width, height);
	}


}