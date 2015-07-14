#include "stdafx.h"

#include "CUDA_ObjectBuffer.h"
#include "tiny_obj_loader.h"

bool CUDA_ObjectBuffer::loadObjects(std::string& fileName, std::vector<CUDA_ObjectBuffer>& objects)
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err = tinyobj::LoadObj(shapes, materials, fileName.c_str());

	if (!err.empty())
	{
		LOG(ERROR) << "Object loading error: " << err;
	}

	std::stringstream logStr;
	logStr << std::endl;
	logStr << "# of shapes    : " << shapes.size() << std::endl;
	logStr << "# of materials : " << materials.size() << std::endl;

	for (size_t i = 0; i < shapes.size(); i++) 
	{
		logStr << "shape[" << i << "].name = " << shapes[i].name << std::endl;
		logStr << "Size of shape[" << i << "].indices: " << shapes[i].mesh.indices.size() << std::endl;
		logStr << "Size of shape[" << i << "].material_ids: " << shapes[i].mesh.material_ids.size() << std::endl;
		CHECK((shapes[i].mesh.indices.size() % 3) == 0) << "indices.size() % 3 != 0";
		for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) 
		{
			logStr << "  idx[" << f << "] = (" << shapes[i].mesh.indices[3 * f + 0] << ", " << shapes[i].mesh.indices[3 * f + 1] <<
				", " << shapes[i].mesh.indices[3 * f + 2] << ")" << ". mat_id = " << shapes[i].mesh.material_ids[f] << std::endl;
		}

		logStr << "shape[" << i << "].vertices: " << shapes[i].mesh.positions.size() << std::endl;
		CHECK((shapes[i].mesh.positions.size() % 3) == 0) << "positions.size() % 3 != 0";
		for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
			logStr << "  v[" << v << "] = (" << shapes[i].mesh.positions[3 * v + 0] << ", " <<
				shapes[i].mesh.positions[3 * v + 1] << ", " << shapes[i].mesh.positions[3 * v + 2] << ")" << std::endl;
		}
	}

	for (size_t i = 0; i < materials.size(); i++) 
	{
		logStr << "material[" << i << "].name = " << materials[i].name << std::endl;
		logStr << "  material.Ka = (" << materials[i].ambient[0] << ", " << materials[i].ambient[1] << ", " << materials[i].ambient[2] << ")" << std::endl;
		logStr << "  material.Kd = (" << materials[i].diffuse[0] << ", " << materials[i].diffuse[1] << ", " << materials[i].diffuse[2] << ")" << std::endl;
		logStr << "  material.Ks = (" << materials[i].specular[0] << ", " << materials[i].specular[1] << ", " << materials[i].specular[2] << ")" << std::endl;
		logStr << "  material.Tr = (" << materials[i].transmittance[0] << ", " << materials[i].transmittance[1] << ", " << materials[i].transmittance[2] << std::endl;
		logStr << "  material.Ke = (" << materials[i].emission[0] << ", " << materials[i].emission[1] << ", " << materials[i].emission[2] << std::endl;
		logStr << "  material.Ns = " << materials[i].shininess << std::endl;
		logStr << "  material.Ni = " << materials[i].ior << std::endl;
		logStr << "  material.dissolve = " << materials[i].dissolve << std::endl;
		logStr << "  material.illum = " << materials[i].illum << std::endl;
		logStr << "  material.map_Ka = " << materials[i].ambient_texname << std::endl;
		logStr << "  material.map_Kd = " << materials[i].diffuse_texname << std::endl;
		logStr << "  material.map_Ks = " << materials[i].specular_texname << std::endl;
		logStr << "  material.map_Ns = " << materials[i].normal_texname << std::endl;
		std::map<std::string, std::string>::const_iterator it(materials[i].unknown_parameter.begin());
		std::map<std::string, std::string>::const_iterator itEnd(materials[i].unknown_parameter.end());
		for (; it != itEnd; it++) {
			logStr << "  material." << it->first << " = " << it->second << std::endl;
		}
		logStr << std::endl;
	}
	LOG(INFO) << logStr.str();

	return true;
}
