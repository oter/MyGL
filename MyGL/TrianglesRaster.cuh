#pragma once

#include "CUDA_ObjectBuffer.h"

void trianglesRaster2DKernel(std::vector<CUDA_ObjectBuffer>& objects, dim3 blocks, dim3 threads, uchar4* frameBuffer, int width, int height);