#include "kernel.cuh"
#include "kernels_common.cuh"


__global__ void clearColorKernel(uchar4* frameBuffer, const uchar4 color, int maxIndex)
{
	int offset = blockDim.x * blockIdx.x + threadIdx.x;

	if (offset >= maxIndex)
	{
		return;
	}
	

	frameBuffer[offset] = color;
}

__global__ void drawLinesKernel(uchar4* frameBuffer, int width, const int* lines, const uchar4* colors, int count)
{
	int offset = blockDim.x * blockIdx.x + threadIdx.x;

	

	

	if (offset >= count)
	{
		return;
	}

	

	int x0 = lines[offset * 4];
	int y0 = lines[offset * 4 + 1];
	int x1 = lines[offset * 4 + 2];
	int y1 = lines[offset * 4 + 3];

	


	//int sampleColor = 0xFFCC1923;
	//frameBuffer[x0 + y0 * width] = *(uchar4*)&sampleColor;
	//frameBuffer[x1 + y1 * width] = *(uchar4*)&sampleColor;

	uchar4 color = colors[offset];

	

	char steep = abs(y1 - y0) > abs(x1 - x0) ? 1 : 0; // Проверяем рост отрезка по оси икс и по оси игрек
	// Отражаем линию по диагонали, если угол наклона слишком большой
	if (steep)
	{
		cudaSwap(x0, y0); // Перетасовка координат вынесена в отдельную функцию для красоты
		cudaSwap(x1, y1);
	}
	// Если линия растёт не слева направо, то меняем начало и конец отрезка местами
	if (x0 > x1)
	{
		cudaSwap(x0, x1);
		cudaSwap(y0, y1);
	}
	int dx = x1 - x0;
	int dy = abs(y1 - y0);
	int error = dx / 2; // Здесь используется оптимизация с умножением на dx, чтобы избавиться от лишних дробей
	int ystep = (y0 < y1) ? 1 : -1; // Выбираем направление роста координаты y
	int y = y0;

	//for (int i = 0; i < 50; i++)
	//{
	//	frameBuffer[offset * width * 2 + i + 10] = color;
	//}

	//frameBuffer[offset] = { 0xFF, 0, 0, 0xFF };

	//return;

	for (int x = x0; x <= x1; x++)
	{
		int framebufferOffset = (steep ? y : x) + width * (steep ? x : y);
		frameBuffer[framebufferOffset] = color;
		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}

	
}

void drawLinesKernel(uchar4* frameBuffer, dim3 threads, dim3 blocks, int width, const int* lines, const uchar4* colors, int count)
{
	drawLinesKernel << <blocks, threads >> >(frameBuffer, width, lines, colors, count);
}

void clearColorKernel(uchar4* frameBuffer, dim3 threads, dim3 blocks, const uchar4 color, int maxIndex)
{
	clearColorKernel << <blocks, threads >> >(frameBuffer, color, maxIndex);
}


//	TODO
//    // cudaDeviceReset must be called before exiting in order for profiling and
//    // tracing tools such as Nsight and Visual Profiler to show complete traces.
//    cudaStatus = cudaDeviceReset();
//    if (cudaStatus != cudaSuccess) {
//        fprintf(stderr, "cudaDeviceReset failed!");
//        return 1;
//    }