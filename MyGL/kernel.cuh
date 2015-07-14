#pragma once
#include <SDL.h>

void clearColorKernel(uchar4* frameBuffer, dim3 threads, dim3 blocks, const uchar4 color, int maxIndex);

void drawLinesKernel(uchar4* frameBuffer, dim3 threads, dim3 blocks, int width, const int* lines, const uchar4* colors, int count);