#pragma once

#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__device__ inline int2 cudaAdd(const int2& a, const int2& b)
{
	int2 result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;

	return result;
}

__device__ inline int2 cudaSub(const int2& a, const int2& b)
{
	int2 result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;

	return result;
}

__device__ inline int2 cudaMult(const int2& a, const int2& b)
{
	int2 result;
	result.x = a.x * b.x;
	result.y = a.y * b.y;

	return result;
}

__device__ inline int2 cudaMult(const int2& a, float b)
{
	int2 result;
	result.x = (float)a.x * b;
	result.y = (float)a.y * b;

	return result;
}

template <typename T>
__device__ void inline cudaSwap(T& a, T& b)
{
	T c(a);
	a = b;
	b = c;
}