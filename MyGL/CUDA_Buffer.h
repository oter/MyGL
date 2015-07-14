#pragma once
class CUDA_Buffer
{
public:
	CUDA_Buffer();
	virtual ~CUDA_Buffer();

	void malloc(size_t size, size_t count);

	void free();

	uchar4* getMemPointer() { return (uchar4*)pData; }

	void getData(void* dst, size_t size, size_t count);

	void setData(void* src, size_t size, size_t count);

	void setData(int value);

private:
	void nullify();

private:
	void* pData;

	size_t _size;

	size_t _count;
};

