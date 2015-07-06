#include "kernel.cuh"
#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


__global__ void addKernel(int *c, const int *a, const int *b)
{
    int i = threadIdx.x;
    c[i] = a[i] + b[i];
}

__global__ void clearColorKernel(uchar4* frameBuffer, const uchar4 color, int maxIndex)
{
	int offset = blockDim.x * blockIdx.x + threadIdx.x;

	if (offset >= maxIndex)
	{
		return;
	}

	frameBuffer[offset] = color;
}

void clearColorKernel(uchar4* frameBuffer, dim3 threads, dim3 blocks, const uchar4 color, int maxIndex)
{
	clearColorKernel << <blocks, threads >> >(frameBuffer, color, maxIndex);
}

//int main()
//{
//    const int arraySize = 5;
//    const int a[arraySize] = { 1, 2, 3, 4, 5 };
//    const int b[arraySize] = { 10, 20, 30, 40, 50 };
//    int c[arraySize] = { 0 };
//
//    // Add vectors in parallel.
//    cudaError_t cudaStatus = addWithCuda(c, a, b, arraySize);
//    if (cudaStatus != cudaSuccess) {
//        fprintf(stderr, "addWithCuda failed!");
//        return 1;
//    }
//
//    printf("{1,2,3,4,5} + {10,20,30,40,50} = {%d,%d,%d,%d,%d}\n",
//        c[0], c[1], c[2], c[3], c[4]);
//
//    // cudaDeviceReset must be called before exiting in order for profiling and
//    // tracing tools such as Nsight and Visual Profiler to show complete traces.
//    cudaStatus = cudaDeviceReset();
//    if (cudaStatus != cudaSuccess) {
//        fprintf(stderr, "cudaDeviceReset failed!");
//        return 1;
//    }
//
//    return 0;
//}
