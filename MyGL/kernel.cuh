#pragma once
#include <SDL.h>

void clearColorKernel(uchar4* frameBuffer, dim3 threads, dim3 blocks, const uchar4 color, int maxIndex);