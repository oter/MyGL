#pragma once

#include "CUDA_Buffer.h"

struct CUDA_ObjectBuffer
{
	CUDA_Buffer vertices;
	CUDA_Buffer indices;
	CUDA_Buffer normals;
	CUDA_Buffer textCoords;
	int count; // Triangles count

	static bool loadObjects(std::string& fileName, std::vector<CUDA_ObjectBuffer>& objects);
};