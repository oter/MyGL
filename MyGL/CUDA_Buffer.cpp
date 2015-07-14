#include "stdafx.h"
#include "CUDA_Buffer.h"


CUDA_Buffer::CUDA_Buffer()
{
	nullify();
}


CUDA_Buffer::~CUDA_Buffer()
{
	free();
}

void CUDA_Buffer::malloc(size_t size, size_t count)
{
	if (cudaMalloc(&pData, count * size) != cudaSuccess)
	{
		LOG(FATAL) << "cudaMalloc failed!";
		nullify();
	}
	this->_size = size;
	this->_count = count;
}

void CUDA_Buffer::free()
{
	if (pData)
	{
		cudaFree(pData);
	}
	nullify();
}

void CUDA_Buffer::getData(void* dst, size_t size, size_t count)
{
	if (pData == nullptr || dst == nullptr)
	{
		LOG(FATAL) << "pData or\\and dst is\\are null";
	}

	size_t bytesCount = size * count;

	if (bytesCount > this->_size * this->_count)
	{
		LOG(FATAL) << "Index out of bounds exception.";
	}
	
	if (cudaMemcpy(dst, pData, bytesCount, cudaMemcpyDeviceToHost) != cudaSuccess)
	{
		LOG(FATAL) << "cudaMemcpy failed in method getData!";
	}
}

void CUDA_Buffer::setData(void* src, size_t size, size_t count)
{
	free();
	if (src == nullptr)
	{
		LOG(FATAL) << "src is null";
	}

	malloc(size, count);

	size_t bytesCount = size * count;

	if (cudaMemcpy(pData, src, bytesCount, cudaMemcpyHostToDevice) != cudaSuccess)
	{
		LOG(FATAL) << "cudaMemcpy failed in method setData!";
	}
}

void CUDA_Buffer::setData(int value)
{
	if (pData == nullptr)
	{
		LOG(FATAL) << "pData == nullptr";
	}
	cudaMemset(pData, value, _size * _count);
}

void CUDA_Buffer::nullify()
{
	pData = nullptr;
	_size = 0;
	_count = 0;
}
